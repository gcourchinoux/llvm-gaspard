//===- TestAsmPrinter.cpp - Test LLVM assembly writer -------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains a printer that converts from our internal representation
// of machine-dependent LLVM code to GNU format Test assembly language.
//
//===----------------------------------------------------------------------===//

#include "Test.h"
#include "TestMCInstLower.h"
#include "TestSubtarget.h"
#include "TestTargetMachine.h"
#include "MCTargetDesc/TestInstPrinter.h"
#include "TargetInfo/TestTargetInfo.h"
#include "llvm/CodeGen/AsmPrinter.h"
#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

#define DEBUG_TYPE "asm-printer"

namespace {

class TestAsmPrinter : public AsmPrinter {
  TestMCInstLower MCInstLowering;

public:
  explicit TestAsmPrinter(TargetMachine &TM,
                         std::unique_ptr<MCStreamer> Streamer)
      : AsmPrinter(TM, std::move(Streamer)),
        MCInstLowering(&OutContext, *this) {}

  StringRef getPassName() const override { return "Test Assembly Printer"; }
  void emitInstruction(const MachineInstr *MI) override;

  bool runOnMachineFunction(MachineFunction &MF) override;
};

} // end anonymous namespace

void TestAsmPrinter::emitInstruction(const MachineInstr *MI) {
  SmallString<128> Str;
  raw_svector_ostream O(Str);

  switch (MI->getOpcode()) {
  case Test::DBG_VALUE:
    llvm_unreachable("Should be handled target independently");
    break;
  }

  MCInst TmpInst;
  MCInstLowering.Lower(MI, TmpInst);
  EmitToStreamer(*OutStreamer, TmpInst);
}

bool TestAsmPrinter::runOnMachineFunction(MachineFunction &MF) {
  // Functions are 4-byte aligned.
  MF.ensureAlignment(Align(4));
  return AsmPrinter::runOnMachineFunction(MF);
}

// Force static initialization.
extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeTestAsmPrinter() {
  RegisterAsmPrinter<TestAsmPrinter> X(getTheTestTarget());
}
