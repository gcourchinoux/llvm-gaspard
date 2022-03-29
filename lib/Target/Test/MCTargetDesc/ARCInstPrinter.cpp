//===- TestInstPrinter.cpp - Test MCInst to assembly syntax -------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This class prints an Test MCInst to a .s file.
//
//===----------------------------------------------------------------------===//

#include "TestInstPrinter.h"
#include "MCTargetDesc/TestInfo.h"
#include "llvm/ADT/StringExtras.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

#define DEBUG_TYPE "asm-printer"

#include "TestGenAsmWriter.inc"

template <class T>
static const char *BadConditionCode(T cc) {
  LLVM_DEBUG(dbgs() << "Unknown condition code passed: " << cc << "\n");
  return "{unknown-cc}";
}

static const char *TestBRCondCodeToString(TestCC::BRCondCode BRCC) {
  switch (BRCC) {
  case TestCC::BREQ:
    return "eq";
  case TestCC::BRNE:
    return "ne";
  case TestCC::BRLT:
    return "lt";
  case TestCC::BRGE:
    return "ge";
  case TestCC::BRLO:
    return "lo";
  case TestCC::BRHS:
    return "hs";
  }
  return BadConditionCode(BRCC);
}

static const char *TestCondCodeToString(TestCC::CondCode CC) {
  switch (CC) {
  case TestCC::EQ:
    return "eq";
  case TestCC::NE:
    return "ne";
  case TestCC::P:
    return "p";
  case TestCC::N:
    return "n";
  case TestCC::HS:
    return "hs";
  case TestCC::LO:
    return "lo";
  case TestCC::GT:
    return "gt";
  case TestCC::GE:
    return "ge";
  case TestCC::VS:
    return "vs";
  case TestCC::VC:
    return "vc";
  case TestCC::LT:
    return "lt";
  case TestCC::LE:
    return "le";
  case TestCC::HI:
    return "hi";
  case TestCC::LS:
    return "ls";
  case TestCC::PNZ:
    return "pnz";
  case TestCC::AL:
    return "al";
  case TestCC::NZ:
    return "nz";
  case TestCC::Z:
    return "z";
  }
  return BadConditionCode(CC);
}

void TestInstPrinter::printRegName(raw_ostream &OS, unsigned RegNo) const {
  OS << StringRef(getRegisterName(RegNo)).lower();
}

void TestInstPrinter::printInst(const MCInst *MI, uint64_t Address,
                               StringRef Annot, const MCSubtargetInfo &STI,
                               raw_ostream &O) {
  printInstruction(MI, Address, O);
  printAnnotation(O, Annot);
}

static void printExpr(const MCExpr *Expr, const MCAsmInfo *MAI,
                      raw_ostream &OS) {
  int Offset = 0;
  const MCSymbolRefExpr *SRE;

  if (const auto *CE = dyn_cast<MCConstantExpr>(Expr)) {
    OS << "0x";
    OS.write_hex(CE->getValue());
    return;
  }

  if (const auto *BE = dyn_cast<MCBinaryExpr>(Expr)) {
    SRE = dyn_cast<MCSymbolRefExpr>(BE->getLHS());
    const auto *CE = dyn_cast<MCConstantExpr>(BE->getRHS());
    assert(SRE && CE && "Binary expression must be sym+const.");
    Offset = CE->getValue();
  } else {
    SRE = dyn_cast<MCSymbolRefExpr>(Expr);
    assert(SRE && "Unexpected MCExpr type.");
  }
  assert(SRE->getKind() == MCSymbolRefExpr::VK_None);

  // Symbols are prefixed with '@'
  OS << '@';
  SRE->getSymbol().print(OS, MAI);

  if (Offset) {
    if (Offset > 0)
      OS << '+';
    OS << Offset;
  }
}

void TestInstPrinter::printOperand(const MCInst *MI, unsigned OpNum,
                                  raw_ostream &O) {
  const MCOperand &Op = MI->getOperand(OpNum);
  if (Op.isReg()) {
    printRegName(O, Op.getReg());
    return;
  }

  if (Op.isImm()) {
    O << Op.getImm();
    return;
  }

  assert(Op.isExpr() && "unknown operand kind in printOperand");
  printExpr(Op.getExpr(), &MAI, O);
}

void TestInstPrinter::printMemOperandRI(const MCInst *MI, unsigned OpNum,
                                       raw_ostream &O) {
  const MCOperand &base = MI->getOperand(OpNum);
  const MCOperand &offset = MI->getOperand(OpNum + 1);
  assert(base.isReg() && "Base should be register.");
  assert(offset.isImm() && "Offset should be immediate.");
  printRegName(O, base.getReg());
  O << "," << offset.getImm();
}

void TestInstPrinter::printPredicateOperand(const MCInst *MI, unsigned OpNum,
                                           raw_ostream &O) {

  const MCOperand &Op = MI->getOperand(OpNum);
  assert(Op.isImm() && "Predicate operand is immediate.");
  O << TestCondCodeToString((TestCC::CondCode)Op.getImm());
}

void TestInstPrinter::printBRCCPredicateOperand(const MCInst *MI, unsigned OpNum,
                                               raw_ostream &O) {
  const MCOperand &Op = MI->getOperand(OpNum);
  assert(Op.isImm() && "Predicate operand is immediate.");
  O << TestBRCondCodeToString((TestCC::BRCondCode)Op.getImm());
}
