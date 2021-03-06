//===-- GaspardInstPrinter.cpp - Convert Gaspard MCInst to asm syntax ---------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This class prints an Gaspard MCInst to a .s file.
//
//===----------------------------------------------------------------------===//

#include "GaspardInstPrinter.h"
#include "GaspardMCExpr.h"
#include "GaspardAluCode.h"
#include "GaspardCondCode.h"
#include "MCTargetDesc/GaspardMCTargetDesc.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/FormattedStream.h"

using namespace llvm;

#define DEBUG_TYPE "asm-printer"

// Include the auto-generated portion of the assembly writer.
#define PRINT_ALIAS_INSTR
#include "GaspardGenAsmWriter.inc"

void GaspardInstPrinter::printRegName(raw_ostream &OS, unsigned RegNo) const {
  OS << StringRef(getRegisterName(RegNo)).lower();
}

bool GaspardInstPrinter::printInst(const MCInst *MI, raw_ostream &OS,
                                 StringRef Alias, unsigned OpNo0,
                                 unsigned OpNo1) {
  OS << "\t" << Alias << " ";
  printOperand(MI, OpNo0, OS);
  OS << ", ";
  printOperand(MI, OpNo1, OS);
  return true;
}

static bool usesGivenOffset(const MCInst *MI, int AddOffset) {
  unsigned AluCode = MI->getOperand(3).getImm();
  return LPAC::encodeGaspardAluCode(AluCode) == LPAC::ADD &&
         (MI->getOperand(2).getImm() == AddOffset ||
          MI->getOperand(2).getImm() == -AddOffset);
}

static bool isPreIncrementForm(const MCInst *MI, int AddOffset) {
  unsigned AluCode = MI->getOperand(3).getImm();
  return LPAC::isPreOp(AluCode) && usesGivenOffset(MI, AddOffset);
}

static bool isPostIncrementForm(const MCInst *MI, int AddOffset) {
  unsigned AluCode = MI->getOperand(3).getImm();
  return LPAC::isPostOp(AluCode) && usesGivenOffset(MI, AddOffset);
}

static StringRef decIncOperator(const MCInst *MI) {
  if (MI->getOperand(2).getImm() < 0)
    return "--";
  return "++";
}

bool GaspardInstPrinter::printMemoryLoadIncrement(const MCInst *MI,
                                                raw_ostream &OS,
                                                StringRef Opcode,
                                                int AddOffset) {
  if (isPreIncrementForm(MI, AddOffset)) {
    OS << "\t" << Opcode << "\t[" << decIncOperator(MI) << " "
       << getRegisterName(MI->getOperand(1).getReg()) << "],  "
       << getRegisterName(MI->getOperand(0).getReg());
    return true;
  }
  if (isPostIncrementForm(MI, AddOffset)) {
    OS << "\t" << Opcode << "\t[ "
       << getRegisterName(MI->getOperand(1).getReg()) << decIncOperator(MI)
       << "],  " << getRegisterName(MI->getOperand(0).getReg());
    return true;
  }
  return false;
}

bool GaspardInstPrinter::printMemoryStoreIncrement(const MCInst *MI,
                                                 raw_ostream &OS,
                                                 StringRef Opcode,
                                                 int AddOffset) {
  if (isPreIncrementForm(MI, AddOffset)) {
    OS << "\t" << Opcode << "\t " << getRegisterName(MI->getOperand(0).getReg())
       << ", [" << decIncOperator(MI) << " "
       << getRegisterName(MI->getOperand(1).getReg()) << "]";
    return true;
  }
  if (isPostIncrementForm(MI, AddOffset)) {
    OS << "\t" << Opcode << "\t " << getRegisterName(MI->getOperand(0).getReg())
       << ", [ " << getRegisterName(MI->getOperand(1).getReg())
       << decIncOperator(MI) << "]";
    return true;
  }
  return false;
}

bool GaspardInstPrinter::printAlias(const MCInst *MI, raw_ostream &OS) {
  switch (MI->getOpcode()) {
  case Gaspard::LDW_RI:
    // ld 4[* rN],  rX => ld [++imm],  rX
    // ld -4[* rN],  rX => ld [--imm],  rX
    // ld 4[ rN*],  rX => ld [imm++],  rX
    // ld -4[ rN*],  rX => ld [imm--],  rX
    return printMemoryLoadIncrement(MI, OS, "ld", 4);
  case Gaspard::LDHs_RI:
    return printMemoryLoadIncrement(MI, OS, "ld.h", 2);
  case Gaspard::LDHz_RI:
    return printMemoryLoadIncrement(MI, OS, "uld.h", 2);
  case Gaspard::LDBs_RI:
    return printMemoryLoadIncrement(MI, OS, "ld.b", 1);
  case Gaspard::LDBz_RI:
    return printMemoryLoadIncrement(MI, OS, "uld.b", 1);
  case Gaspard::SW_RI:
    // st  rX, 4[* rN] => st  rX, [++imm]
    // st  rX, -4[* rN] => st  rX, [--imm]
    // st  rX, 4[ rN*] => st  rX, [imm++]
    // st  rX, -4[ rN*] => st  rX, [imm--]
    return printMemoryStoreIncrement(MI, OS, "st", 4);
  case Gaspard::STH_RI:
    return printMemoryStoreIncrement(MI, OS, "st.h", 2);
  case Gaspard::STB_RI:
    return printMemoryStoreIncrement(MI, OS, "st.b", 1);
  default:
    return false;
  }
}

void GaspardInstPrinter::printInst(const MCInst *MI, uint64_t Address,
                                 StringRef Annotation,
                                 const MCSubtargetInfo & /*STI*/,
                                 raw_ostream &OS) {
  if (!printAlias(MI, OS) && !printAliasInstr(MI, Address, OS))
    printInstruction(MI, Address, OS);
  printAnnotation(OS, Annotation);
}

void GaspardInstPrinter::printOperand(const MCInst *MI, unsigned OpNo,
                                    raw_ostream &OS, const char *Modifier) {
  assert((Modifier == 0 || Modifier[0] == 0) && "No modifiers supported");
  const MCOperand &Op = MI->getOperand(OpNo);
  if (Op.isReg())
    OS << " " << getRegisterName(Op.getReg());
  else if (Op.isImm())
    OS << formatHex(Op.getImm());
  else {
    assert(Op.isExpr() && "Expected an expression");
    Op.getExpr()->print(OS, &MAI);
  }
}

void GaspardInstPrinter::printMemImmOperand(const MCInst *MI, unsigned OpNo,
                                          raw_ostream &OS) {
  const MCOperand &Op = MI->getOperand(OpNo);
  if (Op.isImm()) {
    OS << '[' << formatHex(Op.getImm()) << ']';
  } else {
    // Symbolic operand will be lowered to immediate value by linker
    assert(Op.isExpr() && "Expected an expression");
    OS << '[';
    Op.getExpr()->print(OS, &MAI);
    OS << ']';
  }
}

void GaspardInstPrinter::printHi16ImmOperand(const MCInst *MI, unsigned OpNo,
                                           raw_ostream &OS) {
  const MCOperand &Op = MI->getOperand(OpNo);
  if (Op.isImm()) {
    OS << formatHex(Op.getImm() << 16);
  } else {
    // Symbolic operand will be lowered to immediate value by linker
    assert(Op.isExpr() && "Expected an expression");
    Op.getExpr()->print(OS, &MAI);
  }
}

void GaspardInstPrinter::printHi16AndImmOperand(const MCInst *MI, unsigned OpNo,
                                              raw_ostream &OS) {
  const MCOperand &Op = MI->getOperand(OpNo);
  if (Op.isImm()) {
    OS << formatHex((Op.getImm() << 16) | 0xffff);
  } else {
    // Symbolic operand will be lowered to immediate value by linker
    assert(Op.isExpr() && "Expected an expression");
    Op.getExpr()->print(OS, &MAI);
  }
}

void GaspardInstPrinter::printLo16AndImmOperand(const MCInst *MI, unsigned OpNo,
                                              raw_ostream &OS) {
  const MCOperand &Op = MI->getOperand(OpNo);
  if (Op.isImm()) {
    OS << formatHex(0xffff0000 | Op.getImm());
  } else {
    // Symbolic operand will be lowered to immediate value by linker
    assert(Op.isExpr() && "Expected an expression");
    Op.getExpr()->print(OS, &MAI);
  }
}

static void printMemoryBaseRegister(raw_ostream &OS, const unsigned AluCode,
                                    const MCOperand &RegOp) {
  assert(RegOp.isReg() && "Register operand expected");
  OS << "[";
  if (LPAC::isPreOp(AluCode))
    OS << "*";
  OS << " " << GaspardInstPrinter::getRegisterName(RegOp.getReg());
  if (LPAC::isPostOp(AluCode))
    OS << "*";
  OS << "]";
}

template <unsigned SizeInBits>
static void printMemoryImmediateOffset(const MCAsmInfo &MAI,
                                       const MCOperand &OffsetOp,
                                       raw_ostream &OS) {
  assert((OffsetOp.isImm() || OffsetOp.isExpr()) && "Immediate expected");
  if (OffsetOp.isImm()) {
    assert(isInt<SizeInBits>(OffsetOp.getImm()) && "Constant value truncated");
    OS << OffsetOp.getImm();
  } else
    OffsetOp.getExpr()->print(OS, &MAI);
}

void GaspardInstPrinter::printMemRiOperand(const MCInst *MI, int OpNo,
                                         raw_ostream &OS,
                                         const char * /*Modifier*/) {
  const MCOperand &RegOp = MI->getOperand(OpNo);
  const MCOperand &OffsetOp = MI->getOperand(OpNo + 1);
  const MCOperand &AluOp = MI->getOperand(OpNo + 2);
  const unsigned AluCode = AluOp.getImm();

  // Offset
  printMemoryImmediateOffset<16>(MAI, OffsetOp, OS);

  // Register
  printMemoryBaseRegister(OS, AluCode, RegOp);
}

void GaspardInstPrinter::printMemRrOperand(const MCInst *MI, int OpNo,
                                         raw_ostream &OS,
                                         const char * /*Modifier*/) {
  const MCOperand &RegOp = MI->getOperand(OpNo);
  const MCOperand &OffsetOp = MI->getOperand(OpNo + 1);
  const MCOperand &AluOp = MI->getOperand(OpNo + 2);
  const unsigned AluCode = AluOp.getImm();
  assert(OffsetOp.isReg() && RegOp.isReg() && "Registers expected.");

  // [ Base OP Offset ]
  OS << "[";
  if (LPAC::isPreOp(AluCode))
    OS << "*";
  OS << " " << getRegisterName(RegOp.getReg());
  if (LPAC::isPostOp(AluCode))
    OS << "*";
  OS << " " << LPAC::GaspardAluCodeToString(AluCode) << " ";
  OS << " " << getRegisterName(OffsetOp.getReg());
  OS << "]";
}

void GaspardInstPrinter::printMemSplsOperand(const MCInst *MI, int OpNo,
                                           raw_ostream &OS,
                                           const char * /*Modifier*/) {
  const MCOperand &RegOp = MI->getOperand(OpNo);
  const MCOperand &OffsetOp = MI->getOperand(OpNo + 1);
  const MCOperand &AluOp = MI->getOperand(OpNo + 2);
  const unsigned AluCode = AluOp.getImm();

  // Offset
  printMemoryImmediateOffset<10>(MAI, OffsetOp, OS);

  // Register
  printMemoryBaseRegister(OS, AluCode, RegOp);
}

void GaspardInstPrinter::printCCOperand(const MCInst *MI, int OpNo,
                                      raw_ostream &OS) {
  LPCC::CondCode CC =
      static_cast<LPCC::CondCode>(MI->getOperand(OpNo).getImm());
  // Handle the undefined value here for printing so we don't abort().
  if (CC >= LPCC::UNKNOWN)
    OS << "<und>";
  else
    OS << GaspardCondCodeToString(CC);
}

void GaspardInstPrinter::printPredicateOperand(const MCInst *MI, unsigned OpNo,
                                             raw_ostream &OS) {
  LPCC::CondCode CC =
      static_cast<LPCC::CondCode>(MI->getOperand(OpNo).getImm());
  // Handle the undefined value here for printing so we don't abort().
  if (CC >= LPCC::UNKNOWN)
    OS << "<und>";
  else if (CC != LPCC::ICC_T)
    OS << "." << GaspardCondCodeToString(CC);
}
