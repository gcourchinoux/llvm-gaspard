//===- TestMCTargetDesc.cpp - Test Target Descriptions ------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file provides Test specific target descriptions.
//
//===----------------------------------------------------------------------===//

#include "TestMCTargetDesc.h"
#include "TestInstPrinter.h"
#include "TestMCAsmInfo.h"
#include "TestTargetStreamer.h"
#include "TargetInfo/TestTargetInfo.h"
#include "llvm/MC/MCDwarf.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/FormattedStream.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

#define GET_INSTRINFO_MC_DESC
#include "TestGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "TestGenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "TestGenRegisterInfo.inc"

static MCInstrInfo *createTestMCInstrInfo() {
  auto *X = new MCInstrInfo();
  InitTestMCInstrInfo(X);
  return X;
}

static MCRegisterInfo *createTestMCRegisterInfo(const Triple &TT) {
  auto *X = new MCRegisterInfo();
  InitTestMCRegisterInfo(X, Test::BLINK);
  return X;
}

static MCSubtargetInfo *createTestMCSubtargetInfo(const Triple &TT,
                                                 StringRef CPU, StringRef FS) {
  return createTestMCSubtargetInfoImpl(TT, CPU, /*TuneCPU=*/CPU, FS);
}

static MCAsmInfo *createTestMCAsmInfo(const MCRegisterInfo &MRI,
                                     const Triple &TT,
                                     const MCTargetOptions &Options) {
  MCAsmInfo *MAI = new TestMCAsmInfo(TT);

  // Initial state of the frame pointer is SP.
  MCCFIInstruction Inst = MCCFIInstruction::cfiDefCfa(nullptr, Test::SP, 0);
  MAI->addInitialFrameState(Inst);

  return MAI;
}

static MCInstPrinter *createTestMCInstPrinter(const Triple &T,
                                             unsigned SyntaxVariant,
                                             const MCAsmInfo &MAI,
                                             const MCInstrInfo &MII,
                                             const MCRegisterInfo &MRI) {
  return new TestInstPrinter(MAI, MII, MRI);
}

TestTargetStreamer::TestTargetStreamer(MCStreamer &S) : MCTargetStreamer(S) {}
TestTargetStreamer::~TestTargetStreamer() = default;

static MCTargetStreamer *createTargetAsmStreamer(MCStreamer &S,
                                                 formatted_raw_ostream &OS,
                                                 MCInstPrinter *InstPrint,
                                                 bool isVerboseAsm) {
  return new TestTargetStreamer(S);
}

// Force static initialization.
extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeTestTargetMC() {
  // Register the MC asm info.
  Target &TheTestTarget = getTheTestTarget();
  RegisterMCAsmInfoFn X(TheTestTarget, createTestMCAsmInfo);

  // Register the MC instruction info.
  TargetRegistry::RegisterMCInstrInfo(TheTestTarget, createTestMCInstrInfo);

  // Register the MC register info.
  TargetRegistry::RegisterMCRegInfo(TheTestTarget, createTestMCRegisterInfo);

  // Register the MC subtarget info.
  TargetRegistry::RegisterMCSubtargetInfo(TheTestTarget,
                                          createTestMCSubtargetInfo);

  // Register the MCInstPrinter
  TargetRegistry::RegisterMCInstPrinter(TheTestTarget, createTestMCInstPrinter);

  TargetRegistry::RegisterAsmTargetStreamer(TheTestTarget,
                                            createTargetAsmStreamer);
}
