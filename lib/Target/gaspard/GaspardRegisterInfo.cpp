//===-- GaspardRegisterInfo.cpp - Gaspard Register Information ------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the Gaspard implementation of the TargetRegisterInfo class.
//
//===----------------------------------------------------------------------===//

#include "GaspardRegisterInfo.h"
#include "GaspardAluCode.h"
#include "GaspardCondCode.h"
#include "GaspardFrameLowering.h"
#include "GaspardInstrInfo.h"
#include "llvm/ADT/BitVector.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/RegisterScavenging.h"
#include "llvm/CodeGen/TargetFrameLowering.h"
#include "llvm/CodeGen/TargetInstrInfo.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Type.h"
#include "llvm/Support/ErrorHandling.h"

#define GET_REGINFO_TARGET_DESC
#include "GaspardGenRegisterInfo.inc"

using namespace llvm;

GaspardRegisterInfo::GaspardRegisterInfo() : GaspardGenRegisterInfo(Gaspard::RCA) {}

const uint16_t *
GaspardRegisterInfo::getCalleeSavedRegs(const MachineFunction * /*MF*/) const {
  return CSR_SaveList;
}

BitVector GaspardRegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  BitVector Reserved(getNumRegs());

  Reserved.set(Gaspard::R0);
  Reserved.set(Gaspard::R1);
  Reserved.set(Gaspard::PC);
  Reserved.set(Gaspard::R2);
  Reserved.set(Gaspard::SP);
  Reserved.set(Gaspard::R4);
  Reserved.set(Gaspard::FP);
  Reserved.set(Gaspard::R5);
  Reserved.set(Gaspard::RR1);
  Reserved.set(Gaspard::R10);
  Reserved.set(Gaspard::RR2);
  Reserved.set(Gaspard::R11);
  Reserved.set(Gaspard::RCA);
  Reserved.set(Gaspard::R15);
  if (hasBasePointer(MF))
    Reserved.set(getBaseRegister());
  return Reserved;
}

bool GaspardRegisterInfo::requiresRegisterScavenging(
    const MachineFunction & /*MF*/) const {
  return true;
}

static bool isALUArithLoOpcode(unsigned Opcode) {
  switch (Opcode) {
  case Gaspard::ADD_I_LO:
  case Gaspard::SUB_I_LO:
  case Gaspard::ADD_F_I_LO:
  case Gaspard::SUB_F_I_LO:
  case Gaspard::ADDC_I_LO:
  case Gaspard::SUBB_I_LO:
  case Gaspard::ADDC_F_I_LO:
  case Gaspard::SUBB_F_I_LO:
    return true;
  default:
    return false;
  }
}

static unsigned getOppositeALULoOpcode(unsigned Opcode) {
  switch (Opcode) {
  case Gaspard::ADD_I_LO:
    return Gaspard::SUB_I_LO;
  case Gaspard::SUB_I_LO:
    return Gaspard::ADD_I_LO;
  case Gaspard::ADD_F_I_LO:
    return Gaspard::SUB_F_I_LO;
  case Gaspard::SUB_F_I_LO:
    return Gaspard::ADD_F_I_LO;
  case Gaspard::ADDC_I_LO:
    return Gaspard::SUBB_I_LO;
  case Gaspard::SUBB_I_LO:
    return Gaspard::ADDC_I_LO;
  case Gaspard::ADDC_F_I_LO:
    return Gaspard::SUBB_F_I_LO;
  case Gaspard::SUBB_F_I_LO:
    return Gaspard::ADDC_F_I_LO;
  default:
    llvm_unreachable("Invalid ALU lo opcode");
  }
}

static unsigned getRRMOpcodeVariant(unsigned Opcode) {
  switch (Opcode) {
  case Gaspard::LDBs_RI:
    return Gaspard::LDBs_RR;
  case Gaspard::LDBz_RI:
    return Gaspard::LDBz_RR;
  case Gaspard::LDHs_RI:
    return Gaspard::LDHs_RR;
  case Gaspard::LDHz_RI:
    return Gaspard::LDHz_RR;
  case Gaspard::LDW_RI:
    return Gaspard::LDW_RR;
  case Gaspard::STB_RI:
    return Gaspard::STB_RR;
  case Gaspard::STH_RI:
    return Gaspard::STH_RR;
  case Gaspard::SW_RI:
    return Gaspard::SW_RR;
  default:
    llvm_unreachable("Opcode has no RRM variant");
  }
}

void GaspardRegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                            int SPAdj, unsigned FIOperandNum,
                                            RegScavenger *RS) const {
  assert(SPAdj == 0 && "Unexpected");

  MachineInstr &MI = *II;
  MachineFunction &MF = *MI.getParent()->getParent();
  const TargetInstrInfo *TII = MF.getSubtarget().getInstrInfo();
  const TargetFrameLowering *TFI = MF.getSubtarget().getFrameLowering();
  bool HasFP = TFI->hasFP(MF);
  DebugLoc DL = MI.getDebugLoc();

  int FrameIndex = MI.getOperand(FIOperandNum).getIndex();

  int Offset = MF.getFrameInfo().getObjectOffset(FrameIndex) +
               MI.getOperand(FIOperandNum + 1).getImm();

  // Addressable stack objects are addressed using neg. offsets from fp
  // or pos. offsets from sp/basepointer
  if (!HasFP || (needsStackRealignment(MF) && FrameIndex >= 0))
    Offset += MF.getFrameInfo().getStackSize();

  Register FrameReg = getFrameRegister(MF);
  if (FrameIndex >= 0) {
    if (hasBasePointer(MF))
      FrameReg = getBaseRegister();
    else if (needsStackRealignment(MF))
      FrameReg = Gaspard::SP;
  }

  // Replace frame index with a frame pointer reference.
  // If the offset is small enough to fit in the immediate field, directly
  // encode it.
  // Otherwise scavenge a register and encode it into a MOVHI, OR_I_LO sequence.
  if ((isSPLSOpcode(MI.getOpcode()) && !isInt<10>(Offset)) ||
      !isInt<16>(Offset)) {
    assert(RS && "Register scavenging must be on");
    unsigned Reg = RS->FindUnusedReg(&Gaspard::GPRRegClass);
    if (!Reg)
      Reg = RS->scavengeRegister(&Gaspard::GPRRegClass, II, SPAdj);
    assert(Reg && "Register scavenger failed");

    bool HasNegOffset = false;
    // ALU ops have unsigned immediate values. If the Offset is negative, we
    // negate it here and reverse the opcode later.
    if (Offset < 0) {
      HasNegOffset = true;
      Offset = -Offset;
    }

    if (!isInt<16>(Offset)) {
      // Reg = hi(offset) | lo(offset)
      BuildMI(*MI.getParent(), II, DL, TII->get(Gaspard::MOVHI), Reg)
          .addImm(static_cast<uint32_t>(Offset) >> 16);
      BuildMI(*MI.getParent(), II, DL, TII->get(Gaspard::OR_I_LO), Reg)
          .addReg(Reg)
          .addImm(Offset & 0xffffU);
    } else {
      // Reg = mov(offset)
      BuildMI(*MI.getParent(), II, DL, TII->get(Gaspard::ADD_I_LO), Reg)
          .addImm(0)
          .addImm(Offset);
    }
    // Reg = FrameReg OP Reg
    if (MI.getOpcode() == Gaspard::ADD_I_LO) {
      BuildMI(*MI.getParent(), II, DL,
              HasNegOffset ? TII->get(Gaspard::SUB_R) : TII->get(Gaspard::ADD_R),
              MI.getOperand(0).getReg())
          .addReg(FrameReg)
          .addReg(Reg)
          .addImm(LPCC::ICC_T);
      MI.eraseFromParent();
      return;
    }
    if (isSPLSOpcode(MI.getOpcode()) || isRMOpcode(MI.getOpcode())) {
      MI.setDesc(TII->get(getRRMOpcodeVariant(MI.getOpcode())));
      if (HasNegOffset) {
        // Change the ALU op (operand 3) from LPAC::ADD (the default) to
        // LPAC::SUB with the already negated offset.
        assert((MI.getOperand(3).getImm() == LPAC::ADD) &&
               "Unexpected ALU op in RRM instruction");
        MI.getOperand(3).setImm(LPAC::SUB);
      }
    } else
      llvm_unreachable("Unexpected opcode in frame index operation");

    MI.getOperand(FIOperandNum).ChangeToRegister(FrameReg, /*isDef=*/false);
    MI.getOperand(FIOperandNum + 1)
        .ChangeToRegister(Reg, /*isDef=*/false, /*isImp=*/false,
                          /*isKill=*/true);
    return;
  }

  // ALU arithmetic ops take unsigned immediates. If the offset is negative,
  // we replace the instruction with one that inverts the opcode and negates
  // the immediate.
  if ((Offset < 0) && isALUArithLoOpcode(MI.getOpcode())) {
    unsigned NewOpcode = getOppositeALULoOpcode(MI.getOpcode());
    // We know this is an ALU op, so we know the operands are as follows:
    // 0: destination register
    // 1: source register (frame register)
    // 2: immediate
    BuildMI(*MI.getParent(), II, DL, TII->get(NewOpcode),
            MI.getOperand(0).getReg())
        .addReg(FrameReg)
        .addImm(-Offset);
    MI.eraseFromParent();
  } else {
    MI.getOperand(FIOperandNum).ChangeToRegister(FrameReg, /*isDef=*/false);
    MI.getOperand(FIOperandNum + 1).ChangeToImmediate(Offset);
  }
}

bool GaspardRegisterInfo::hasBasePointer(const MachineFunction &MF) const {
  const MachineFrameInfo &MFI = MF.getFrameInfo();
  // When we need stack realignment and there are dynamic allocas, we can't
  // reference off of the stack pointer, so we reserve a base pointer.
  if (needsStackRealignment(MF) && MFI.hasVarSizedObjects())
    return true;

  return false;
}

unsigned GaspardRegisterInfo::getRARegister() const { return Gaspard::RCA; }

Register
GaspardRegisterInfo::getFrameRegister(const MachineFunction & /*MF*/) const {
  return Gaspard::FP;
}

Register GaspardRegisterInfo::getBaseRegister() const { return Gaspard::R14; }

const uint32_t *
GaspardRegisterInfo::getCallPreservedMask(const MachineFunction & /*MF*/,
                                        CallingConv::ID /*CC*/) const {
  return CSR_RegMask;
}
