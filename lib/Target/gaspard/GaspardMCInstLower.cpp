//=-- GaspardMCInstLower.cpp - Convert Gaspard MachineInstr to an MCInst --------=//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains code to lower Gaspard MachineInstrs to their corresponding
// MCInst records.
//
//===----------------------------------------------------------------------===//

#include "GaspardMCInstLower.h"

#include "MCTargetDesc/GaspardBaseInfo.h"
#include "MCTargetDesc/GaspardMCExpr.h"
#include "llvm/ADT/SmallString.h"
#include "llvm/CodeGen/AsmPrinter.h"
#include "llvm/CodeGen/MachineBasicBlock.h"
#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/IR/Constants.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

MCSymbol *
GaspardMCInstLower::GetGlobalAddressSymbol(const MachineOperand &MO) const {
  return Printer.getSymbol(MO.getGlobal());
}

MCSymbol *
GaspardMCInstLower::GetBlockAddressSymbol(const MachineOperand &MO) const {
  return Printer.GetBlockAddressSymbol(MO.getBlockAddress());
}

MCSymbol *
GaspardMCInstLower::GetExternalSymbolSymbol(const MachineOperand &MO) const {
  return Printer.GetExternalSymbolSymbol(MO.getSymbolName());
}

MCSymbol *GaspardMCInstLower::GetJumpTableSymbol(const MachineOperand &MO) const {
  SmallString<256> Name;
  raw_svector_ostream(Name) << Printer.MAI->getPrivateGlobalPrefix() << "JTI"
                            << Printer.getFunctionNumber() << '_'
                            << MO.getIndex();
  // Create a symbol for the name.
  return Ctx.getOrCreateSymbol(Name.str());
}

MCSymbol *
GaspardMCInstLower::GetConstantPoolIndexSymbol(const MachineOperand &MO) const {
  SmallString<256> Name;
  raw_svector_ostream(Name) << Printer.MAI->getPrivateGlobalPrefix() << "CPI"
                            << Printer.getFunctionNumber() << '_'
                            << MO.getIndex();
  // Create a symbol for the name.
  return Ctx.getOrCreateSymbol(Name.str());
}

MCOperand GaspardMCInstLower::LowerSymbolOperand(const MachineOperand &MO,
                                               MCSymbol *Sym) const {
  GaspardMCExpr::VariantKind Kind;

  switch (MO.getTargetFlags()) {
  case GaspardII::MO_NO_FLAG:
    Kind = GaspardMCExpr::VK_Gaspard_None;
    break;
  case GaspardII::MO_ABS_HI:
    Kind = GaspardMCExpr::VK_Gaspard_ABS_HI;
    break;
  case GaspardII::MO_ABS_LO:
    Kind = GaspardMCExpr::VK_Gaspard_ABS_LO;
    break;
  default:
    llvm_unreachable("Unknown target flag on GV operand");
  }

  const MCExpr *Expr =
      MCSymbolRefExpr::create(Sym, MCSymbolRefExpr::VK_None, Ctx);
  if (!MO.isJTI() && MO.getOffset())
    Expr = MCBinaryExpr::createAdd(
        Expr, MCConstantExpr::create(MO.getOffset(), Ctx), Ctx);
  Expr = GaspardMCExpr::create(Kind, Expr, Ctx);
  return MCOperand::createExpr(Expr);
}

void GaspardMCInstLower::Lower(const MachineInstr *MI, MCInst &OutMI) const {
  OutMI.setOpcode(MI->getOpcode());

  for (unsigned I = 0, E = MI->getNumOperands(); I != E; ++I) {
    const MachineOperand &MO = MI->getOperand(I);

    MCOperand MCOp;
    switch (MO.getType()) {
    case MachineOperand::MO_Register:
      // Ignore all implicit register operands.
      if (MO.isImplicit())
        continue;
      MCOp = MCOperand::createReg(MO.getReg());
      break;
    case MachineOperand::MO_Immediate:
      MCOp = MCOperand::createImm(MO.getImm());
      break;
    case MachineOperand::MO_MachineBasicBlock:
      MCOp = MCOperand::createExpr(
          MCSymbolRefExpr::create(MO.getMBB()->getSymbol(), Ctx));
      break;
    case MachineOperand::MO_RegisterMask:
      continue;
    case MachineOperand::MO_GlobalAddress:
      MCOp = LowerSymbolOperand(MO, GetGlobalAddressSymbol(MO));
      break;
    case MachineOperand::MO_BlockAddress:
      MCOp = LowerSymbolOperand(MO, GetBlockAddressSymbol(MO));
      break;
    case MachineOperand::MO_ExternalSymbol:
      MCOp = LowerSymbolOperand(MO, GetExternalSymbolSymbol(MO));
      break;
    case MachineOperand::MO_JumpTableIndex:
      MCOp = LowerSymbolOperand(MO, GetJumpTableSymbol(MO));
      break;
    case MachineOperand::MO_ConstantPoolIndex:
      MCOp = LowerSymbolOperand(MO, GetConstantPoolIndexSymbol(MO));
      break;
    default:
      MI->print(errs());
      llvm_unreachable("unknown operand type");
    }

    OutMI.addOperand(MCOp);
  }
}
