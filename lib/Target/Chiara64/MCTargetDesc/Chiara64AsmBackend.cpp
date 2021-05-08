//===-- Chiara64AsmBackend.cpp - Chiara64 Assembler Backend -----------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "Chiara64AsmBackend.h"
#include "MCTargetDesc/Chiara64MCTargetDesc.h"
#include "llvm/MC/MCAsmLayout.h"
#include "llvm/MC/MCAssembler.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCFixupKindInfo.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/Support/Debug.h"

#define DEBUG_TYPE "Chiara64-asmbackend"

using namespace llvm;

std::unique_ptr<MCObjectTargetWriter>
Chiara64AsmBackend::createObjectTargetWriter() const {
  return createChiara64ELFObjectWriter();
}

unsigned int Chiara64AsmBackend::getNumFixupKinds() const { return 1; }

void Chiara64AsmBackend::applyFixup(const MCAssembler &Asm, const MCFixup &Fixup,
                                const MCValue &Target,
                                MutableArrayRef<char> Data, uint64_t Value,
                                bool IsResolved,
                                const MCSubtargetInfo *STI) const {
  return;
}

bool Chiara64AsmBackend::fixupNeedsRelaxation(const MCFixup &Fixup, uint64_t Value,
                                          const MCRelaxableFragment *DF,
                                          const MCAsmLayout &Layout) const {
  return false;
}

void Chiara64AsmBackend::relaxInstruction(MCInst &Inst,
                                      const MCSubtargetInfo &STI) const {
  llvm_unreachable("Chiara64AsmBackend::relaxInstruction() unimplemented");
}

bool Chiara64AsmBackend::writeNopData(raw_ostream &OS, uint64_t Count) const {
  if (Count % 2)
    return false;

  // MOV32 r0, r0
  while (Count >= 4) {
    OS.write("\xc4\x00\x48\x20", 4);
    Count -= 4;
  }
  // MOV16 r0, r0
  if (Count)
    OS.write("\x6c\x03", 2);

  return true;
}

MCAsmBackend *llvm::createChiara64AsmBackend(const Target &T,
                                         const MCSubtargetInfo &STI,
                                         const MCRegisterInfo &MRI,
                                         const MCTargetOptions &Options) {
  return new Chiara64AsmBackend(STI, Options);
}
