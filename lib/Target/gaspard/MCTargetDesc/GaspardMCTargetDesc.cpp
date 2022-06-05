//===-- GaspardMCTargetDesc.cpp - Gaspard Target Descriptions -----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file provides Gaspard specific target descriptions.
//
//===----------------------------------------------------------------------===//

#include "GaspardMCTargetDesc.h"
#include "GaspardInstPrinter.h"
#include "GaspardMCAsmInfo.h"
#include "TargetInfo/GaspardTargetInfo.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/ADT/Triple.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstrAnalysis.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/TargetRegistry.h"
#include <cstdint>
#include <string>

#define GET_INSTRINFO_MC_DESC
#include "GaspardGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "GaspardGenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "GaspardGenRegisterInfo.inc"

using namespace llvm;

static MCInstrInfo *createGaspardMCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  InitGaspardMCInstrInfo(X);
  return X;
}

static MCRegisterInfo *createGaspardMCRegisterInfo(const Triple & /*TT*/) {
  MCRegisterInfo *X = new MCRegisterInfo();
  InitGaspardMCRegisterInfo(X, Gaspard::RCA, 0, 0, Gaspard::PC);
  return X;
}

static MCSubtargetInfo *
createGaspardMCSubtargetInfo(const Triple &TT, StringRef CPU, StringRef FS) {
  std::string CPUName = std::string(CPU);
  if (CPUName.empty())
    CPUName = "generic";

  return createGaspardMCSubtargetInfoImpl(TT, CPUName, /*TuneCPU*/ CPUName, FS);
}

static MCStreamer *createMCStreamer(const Triple &T, MCContext &Context,
                                    std::unique_ptr<MCAsmBackend> &&MAB,
                                    std::unique_ptr<MCObjectWriter> &&OW,
                                    std::unique_ptr<MCCodeEmitter> &&Emitter,
                                    bool RelaxAll) {
  if (!T.isOSBinFormatELF())
    llvm_unreachable("OS not supported");

  return createELFStreamer(Context, std::move(MAB), std::move(OW),
                           std::move(Emitter), RelaxAll);
}

static MCInstPrinter *createGaspardMCInstPrinter(const Triple & /*T*/,
                                               unsigned SyntaxVariant,
                                               const MCAsmInfo &MAI,
                                               const MCInstrInfo &MII,
                                               const MCRegisterInfo &MRI) {
  if (SyntaxVariant == 0)
    return new GaspardInstPrinter(MAI, MII, MRI);
  return nullptr;
}

static MCRelocationInfo *createGaspardElfRelocation(const Triple &TheTriple,
                                                  MCContext &Ctx) {
  return createMCRelocationInfo(TheTriple, Ctx);
}

namespace {

class GaspardMCInstrAnalysis : public MCInstrAnalysis {
public:
  explicit GaspardMCInstrAnalysis(const MCInstrInfo *Info)
      : MCInstrAnalysis(Info) {}

  bool evaluateBranch(const MCInst &Inst, uint64_t Addr, uint64_t Size,
                      uint64_t &Target) const override {
    if (Inst.getNumOperands() == 0)
      return false;

    if (Info->get(Inst.getOpcode()).OpInfo[0].OperandType ==
        MCOI::OPERAND_PCREL) {
      int64_t Imm = Inst.getOperand(0).getImm();
      Target = Addr + Size + Imm;
      return true;
    } else {
      int64_t Imm = Inst.getOperand(0).getImm();

      // Skip case where immediate is 0 as that occurs in file that isn't linked
      // and the branch target inferred would be wrong.
      if (Imm == 0)
        return false;

      Target = Imm;
      return true;
    }
  }
};

} // end anonymous namespace

static MCInstrAnalysis *createGaspardInstrAnalysis(const MCInstrInfo *Info) {
  return new GaspardMCInstrAnalysis(Info);
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeGaspardTargetMC() {
  // Register the MC asm info.
  RegisterMCAsmInfo<GaspardMCAsmInfo> X(getTheGaspardTarget());

  // Register the MC instruction info.
  TargetRegistry::RegisterMCInstrInfo(getTheGaspardTarget(),
                                      createGaspardMCInstrInfo);

  // Register the MC register info.
  TargetRegistry::RegisterMCRegInfo(getTheGaspardTarget(),
                                    createGaspardMCRegisterInfo);

  // Register the MC subtarget info.
  TargetRegistry::RegisterMCSubtargetInfo(getTheGaspardTarget(),
                                          createGaspardMCSubtargetInfo);

  // Register the MC code emitter
  TargetRegistry::RegisterMCCodeEmitter(getTheGaspardTarget(),
                                        createGaspardMCCodeEmitter);

  // Register the ASM Backend
  TargetRegistry::RegisterMCAsmBackend(getTheGaspardTarget(),
                                       createGaspardAsmBackend);

  // Register the MCInstPrinter.
  TargetRegistry::RegisterMCInstPrinter(getTheGaspardTarget(),
                                        createGaspardMCInstPrinter);

  // Register the ELF streamer.
  TargetRegistry::RegisterELFStreamer(getTheGaspardTarget(), createMCStreamer);

  // Register the MC relocation info.
  TargetRegistry::RegisterMCRelocationInfo(getTheGaspardTarget(),
                                           createGaspardElfRelocation);

  // Register the MC instruction analyzer.
  TargetRegistry::RegisterMCInstrAnalysis(getTheGaspardTarget(),
                                          createGaspardInstrAnalysis);
}
