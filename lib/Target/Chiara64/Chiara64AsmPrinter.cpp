//===-- XCoreAsmPrinter.cpp - XCore LLVM assembly writer ------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains a printer that converts from our internal representation
// of machine-dependent LLVM code to the XAS-format XCore assembly language.
//
//===----------------------------------------------------------------------===//

#include "TargetInfo/Chiara64TargetInfo.h"
#include "llvm/CodeGen/AsmPrinter.h"
#include "llvm/ADT/SmallString.h"
#include "llvm/ADT/StringExtras.h"
#include "llvm/CodeGen/AsmPrinter.h"
#include "llvm/CodeGen/MachineConstantPool.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/CodeGen/MachineJumpTableInfo.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/DebugInfo.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Mangler.h"
#include "llvm/IR/Module.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSymbolELF.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetLoweringObjectFile.h"
#include <algorithm>
#include <cctype>
using namespace llvm;

#define DEBUG_TYPE "asm-printer"

namespace {
  class Chiara64AsmPrinter : public AsmPrinter {
      public :
      explicit Chiara64AsmPrinter(TargetMachine &TM,
                               std::unique_ptr<MCStreamer> Streamer)
                                 : AsmPrinter(TM, std::move(Streamer)) {}
                             
      bool PrintAsmOperand(const MachineInstr *MI, unsigned OpNo,const char *ExtraCode, raw_ostream &OS);
      void EmitInstruction(const MachineInstr *MI) ;
      bool runOnMachineFunction(MachineFunction &MF) ;
      void PrintOperand(const MachineInstr *MI, unsigned OpNo,
                        raw_ostream &O);
  };
}

bool Chiara64AsmPrinter::PrintAsmOperand(const MachineInstr *MI, unsigned OpNo,
                                          const char *ExtraCode, raw_ostream &OS) {
     
     OS << "on appelle une instruction " ;
     
     
 }
 void Chiara64AsmPrinter::EmitInstruction(const MachineInstr *MI) {
  
 }


bool Chiara64AsmPrinter::runOnMachineFunction(MachineFunction &MF) {
    
    
}
void Chiara64AsmPrinter::PrintOperand(const MachineInstr *MI, unsigned OpNo,
                                      raw_ostream &O) {
    
    
}
// Force static initialization.
extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeChiara64AsmPrinter() {
  RegisterAsmPrinter<Chiara64AsmPrinter> X(getTheChiara64Target());

}
