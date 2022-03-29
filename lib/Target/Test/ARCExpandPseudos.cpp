//===- TestExpandPseudosPass - Test expand pseudo loads -----------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This pass expands stores with large offsets into an appropriate sequence.
//===----------------------------------------------------------------------===//

#include "Test.h"
#include "TestInstrInfo.h"
#include "TestRegisterInfo.h"
#include "TestSubtarget.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"

using namespace llvm;

#define DEBUG_TYPE "Test-expand-pseudos"

namespace {

class TestExpandPseudos : public MachineFunctionPass {
public:
  static char ID;
  TestExpandPseudos() : MachineFunctionPass(ID) {}

  bool runOnMachineFunction(MachineFunction &Fn) override;

  StringRef getPassName() const override { return "Test Expand Pseudos"; }

private:
  void ExpandStore(MachineFunction &, MachineBasicBlock::iterator);

  const TestInstrInfo *TII;
};

char TestExpandPseudos::ID = 0;

} // end anonymous namespace

static unsigned getMappedOp(unsigned PseudoOp) {
  switch (PseudoOp) {
  case Test::ST_FAR:
    return Test::ST_rs9;
  case Test::STH_FAR:
    return Test::STH_rs9;
  case Test::STB_FAR:
    return Test::STB_rs9;
  default:
    llvm_unreachable("Unhandled pseudo op.");
  }
}

void TestExpandPseudos::ExpandStore(MachineFunction &MF,
                                   MachineBasicBlock::iterator SII) {
  MachineInstr &SI = *SII;
  unsigned AddrReg = MF.getRegInfo().createVirtualRegister(&Test::GPR32RegClass);
  unsigned AddOpc =
      isUInt<6>(SI.getOperand(2).getImm()) ? Test::ADD_rru6 : Test::ADD_rrlimm;
  BuildMI(*SI.getParent(), SI, SI.getDebugLoc(), TII->get(AddOpc), AddrReg)
      .addReg(SI.getOperand(1).getReg())
      .addImm(SI.getOperand(2).getImm());
  BuildMI(*SI.getParent(), SI, SI.getDebugLoc(),
          TII->get(getMappedOp(SI.getOpcode())))
      .addReg(SI.getOperand(0).getReg())
      .addReg(AddrReg)
      .addImm(0);
  SI.eraseFromParent();
}

bool TestExpandPseudos::runOnMachineFunction(MachineFunction &MF) {
  const TestSubtarget *STI = &MF.getSubtarget<TestSubtarget>();
  TII = STI->getInstrInfo();
  bool ExpandedStore = false;
  for (auto &MBB : MF) {
    MachineBasicBlock::iterator MBBI = MBB.begin(), E = MBB.end();
    while (MBBI != E) {
      MachineBasicBlock::iterator NMBBI = std::next(MBBI);
      switch (MBBI->getOpcode()) {
      case Test::ST_FAR:
      case Test::STH_FAR:
      case Test::STB_FAR:
        ExpandStore(MF, MBBI);
        ExpandedStore = true;
        break;
      default:
        break;
      }
      MBBI = NMBBI;
    }
  }
  return ExpandedStore;
}

FunctionPass *llvm::createTestExpandPseudosPass() {
  return new TestExpandPseudos();
}
