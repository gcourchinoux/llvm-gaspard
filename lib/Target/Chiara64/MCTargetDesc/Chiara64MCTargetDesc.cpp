//===-- Chiara64MCTargetDesc.cpp - Chiara64 Target Descriptions -------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
///
/// This file provides Chiara64 specific target descriptions.
///
//===----------------------------------------------------------------------===//

#include "Chiara64MCTargetDesc.h"
#include "Chiara64AsmBackend.h"
#include "Chiara64MCAsmInfo.h"
#include "Chiara64MCCodeEmitter.h"
#include "TargetInfo/Chiara64TargetInfo.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/TargetRegistry.h"

#define GET_INSTRINFO_MC_DESC
#include "Chiara64GenInstrInfo.inc"

#define GET_REGINFO_MC_DESC
#include "Chiara64GenRegisterInfo.inc"

using namespace llvm;

static MCAsmInfo *createChiara64MCAsmInfo(const MCRegisterInfo &MRI,
                                      const Triple &TT,
                                      const MCTargetOptions &Options) {
  MCAsmInfo *MAI = new Chiara64MCAsmInfo(TT);

  // Initial state of the frame pointer is SP.
  unsigned Reg = MRI.getDwarfRegNum(Chiara64::R14, true);
  MCCFIInstruction Inst = MCCFIInstruction::cfiDefCfa(nullptr, Reg, 0);
  MAI->addInitialFrameState(Inst);
  return MAI;
}

static MCInstrInfo *createChiara64MCInstrInfo() {
  MCInstrInfo *Info = new MCInstrInfo();
  InitChiara64MCInstrInfo(Info);
  return Info;
}

static MCRegisterInfo *createChiara64MCRegisterInfo(const Triple &TT) {
  MCRegisterInfo *Info = new MCRegisterInfo();
  InitChiara64MCRegisterInfo(Info, Chiara64::R15);
  return Info;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeChiara64TargetMC() {
  auto &Chiara64Target = getTheChiara64Target();
  TargetRegistry::RegisterMCAsmBackend(Chiara64Target, createChiara64AsmBackend);
  TargetRegistry::RegisterMCAsmInfo(Chiara64Target, createChiara64MCAsmInfo);
  TargetRegistry::RegisterMCInstrInfo(Chiara64Target, createChiara64MCInstrInfo);
  TargetRegistry::RegisterMCRegInfo(Chiara64Target, createChiara64MCRegisterInfo);
  TargetRegistry::RegisterMCCodeEmitter(Chiara64Target, createChiara64MCCodeEmitter);
}
