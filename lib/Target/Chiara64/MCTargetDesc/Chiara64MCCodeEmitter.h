//===-- Chiara64MCCodeEmitter.cpp - Chiara64 Code Emitter interface ---------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements the Chiara64MCCodeEmitter class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_Chiara64_MCTARGETDESC_Chiara64MCCODEEMITTER_H
#define LLVM_LIB_TARGET_Chiara64_MCTARGETDESC_Chiara64MCCODEEMITTER_H

#include "llvm/MC/MCCodeEmitter.h"
#include "llvm/MC/MCContext.h"

namespace llvm {

class Chiara64MCCodeEmitter : public MCCodeEmitter {
  MCContext &Ctx;
  const MCInstrInfo &MII;

public:
  Chiara64MCCodeEmitter(MCContext &Ctx, const MCInstrInfo &MII)
      : Ctx(Ctx), MII(MII) {}

  ~Chiara64MCCodeEmitter() {}

  void encodeInstruction(const MCInst &Inst, raw_ostream &OS,
                         SmallVectorImpl<MCFixup> &Fixups,
                         const MCSubtargetInfo &STI) const override;

  // Generated by tablegen.
  uint64_t getBinaryCodeForInstr(const MCInst &MI,
                                 SmallVectorImpl<MCFixup> &Fixups,
                                 const MCSubtargetInfo &STI) const;

  // Default encoding method used by tablegen.
  unsigned getMachineOpValue(const MCInst &MI, const MCOperand &MO,
                            
                             SmallVectorImpl<MCFixup> &Fixups,
                             const MCSubtargetInfo &STI) const;

  template <int shift = 0>
  unsigned getImmOpValue(const MCInst &MI, unsigned Idx, 
                         SmallVectorImpl<MCFixup> &Fixups,
                         const MCSubtargetInfo &STI) const {
    const MCOperand &MO = MI.getOperand(Idx);
    assert(MO.isImm() && "Unexpected MO type.");
    return (MO.getImm() >> shift);
  }

  unsigned getOImmOpValue(const MCInst &MI, unsigned Idx,
                          SmallVectorImpl<MCFixup> &Fixups,
                          const MCSubtargetInfo &STI) const;
};

} // namespace llvm

#endif // LLVM_LIB_TARGET_Chiara64_MCTARGETDESC_Chiara64MCCODEEMITTER_H
