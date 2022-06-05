//===- GaspardInstrInfo.h - Gaspard Instruction Information ---------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the Gaspard implementation of the TargetInstrInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_Gaspard_GaspardINSTRINFO_H
#define LLVM_LIB_TARGET_Gaspard_GaspardINSTRINFO_H

#include "GaspardRegisterInfo.h"
#include "MCTargetDesc/GaspardMCTargetDesc.h"
#include "llvm/CodeGen/TargetInstrInfo.h"

#define GET_INSTRINFO_HEADER
#include "GaspardGenInstrInfo.inc"

namespace llvm {

class GaspardInstrInfo : public GaspardGenInstrInfo {
  const GaspardRegisterInfo RegisterInfo;

public:
  GaspardInstrInfo();

  // getRegisterInfo - TargetInstrInfo is a superset of MRegister info.  As
  // such, whenever a client has an instance of instruction info, it should
  // always be able to get register info as well (through this method).
  virtual const GaspardRegisterInfo &getRegisterInfo() const {
    return RegisterInfo;
  }

  bool areMemAccessesTriviallyDisjoint(const MachineInstr &MIa,
                                       const MachineInstr &MIb) const override;

  unsigned isLoadFromStackSlot(const MachineInstr &MI,
                               int &FrameIndex) const override;

  unsigned isLoadFromStackSlotPostFE(const MachineInstr &MI,
                                     int &FrameIndex) const override;

  unsigned isStoreToStackSlot(const MachineInstr &MI,
                              int &FrameIndex) const override;

  void copyPhysReg(MachineBasicBlock &MBB, MachineBasicBlock::iterator Position,
                   const DebugLoc &DL, MCRegister DestinationRegister,
                   MCRegister SourceRegister, bool KillSource) const override;

  void
  storeRegToStackSlot(MachineBasicBlock &MBB,
                      MachineBasicBlock::iterator Position,
                      Register SourceRegister, bool IsKill, int FrameIndex,
                      const TargetRegisterClass *RegisterClass,
                      const TargetRegisterInfo *RegisterInfo) const override;

  void
  loadRegFromStackSlot(MachineBasicBlock &MBB,
                       MachineBasicBlock::iterator Position,
                       Register DestinationRegister, int FrameIndex,
                       const TargetRegisterClass *RegisterClass,
                       const TargetRegisterInfo *RegisterInfo) const override;

  bool expandPostRAPseudo(MachineInstr &MI) const override;

  bool getMemOperandsWithOffsetWidth(
      const MachineInstr &LdSt,
      SmallVectorImpl<const MachineOperand *> &BaseOps, int64_t &Offset,
      bool &OffsetIsScalable, unsigned &Width,
      const TargetRegisterInfo *TRI) const override;

  bool getMemOperandWithOffsetWidth(const MachineInstr &LdSt,
                                    const MachineOperand *&BaseOp,
                                    int64_t &Offset, unsigned &Width,
                                    const TargetRegisterInfo *TRI) const;

  std::pair<unsigned, unsigned>
  decomposeMachineOperandsTargetFlags(unsigned TF) const override;

  ArrayRef<std::pair<unsigned, const char *>>
  getSerializableDirectMachineOperandTargetFlags() const override;

  bool analyzeBranch(MachineBasicBlock &MBB, MachineBasicBlock *&TrueBlock,
                     MachineBasicBlock *&FalseBlock,
                     SmallVectorImpl<MachineOperand> &Condition,
                     bool AllowModify) const override;

  unsigned removeBranch(MachineBasicBlock &MBB,
                        int *BytesRemoved = nullptr) const override;

  // For a comparison instruction, return the source registers in SrcReg and
  // SrcReg2 if having two register operands, and the value it compares against
  // in CmpValue. Return true if the comparison instruction can be analyzed.
  bool analyzeCompare(const MachineInstr &MI, Register &SrcReg,
                      Register &SrcReg2, int &CmpMask,
                      int &CmpValue) const override;

  // See if the comparison instruction can be converted into something more
  // efficient. E.g., on Gaspard register-register instructions can set the flag
  // register, obviating the need for a separate compare.
  bool optimizeCompareInstr(MachineInstr &CmpInstr, Register SrcReg,
                            Register SrcReg2, int CmpMask, int CmpValue,
                            const MachineRegisterInfo *MRI) const override;

  // Analyze the given select instruction, returning true if it cannot be
  // understood. It is assumed that MI->isSelect() is true.
  //
  // When successful, return the controlling condition and the operands that
  // determine the true and false result values.
  //
  //   Result = SELECT Cond, TrueOp, FalseOp
  //
  // Gaspard can optimize certain select instructions, for example by predicating
  // the instruction defining one of the operands and sets Optimizable to true.
  bool analyzeSelect(const MachineInstr &MI,
                     SmallVectorImpl<MachineOperand> &Cond, unsigned &TrueOp,
                     unsigned &FalseOp, bool &Optimizable) const override;

  // Given a select instruction that was understood by analyzeSelect and
  // returned Optimizable = true, attempt to optimize MI by merging it with one
  // of its operands. Returns NULL on failure.
  //
  // When successful, returns the new select instruction. The client is
  // responsible for deleting MI.
  //
  // If both sides of the select can be optimized, the TrueOp is modifed.
  // PreferFalse is not used.
  MachineInstr *optimizeSelect(MachineInstr &MI,
                               SmallPtrSetImpl<MachineInstr *> &SeenMIs,
                               bool PreferFalse) const override;

  bool reverseBranchCondition(
      SmallVectorImpl<MachineOperand> &Condition) const override;

  unsigned insertBranch(MachineBasicBlock &MBB, MachineBasicBlock *TrueBlock,
                        MachineBasicBlock *FalseBlock,
                        ArrayRef<MachineOperand> Condition,
                        const DebugLoc &DL,
                        int *BytesAdded = nullptr) const override;
};

static inline bool isSPLSOpcode(unsigned Opcode) {
  switch (Opcode) {
  case Gaspard::LDBs_RI:
  case Gaspard::LDBz_RI:
  case Gaspard::LDHs_RI:
  case Gaspard::LDHz_RI:
  case Gaspard::STB_RI:
  case Gaspard::STH_RI:
    return true;
  default:
    return false;
  }
}

static inline bool isRMOpcode(unsigned Opcode) {
  switch (Opcode) {
  case Gaspard::LDW_RI:
  case Gaspard::SW_RI:
    return true;
  default:
    return false;
  }
}

static inline bool isRRMOpcode(unsigned Opcode) {
  switch (Opcode) {
  case Gaspard::LDBs_RR:
  case Gaspard::LDBz_RR:
  case Gaspard::LDHs_RR:
  case Gaspard::LDHz_RR:
  case Gaspard::LDWz_RR:
  case Gaspard::LDW_RR:
  case Gaspard::STB_RR:
  case Gaspard::STH_RR:
  case Gaspard::SW_RR:
    return true;
  default:
    return false;
  }
}

} // namespace llvm

#endif // LLVM_LIB_TARGET_Gaspard_GaspardINSTRINFO_H
