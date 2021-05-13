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

#include "Chiara64MCCodeEmitter.h"
#include "MCTargetDesc/Chiara64MCTargetDesc.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/MC/MCInstBuilder.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/Support/EndianStream.h"

using namespace llvm;

#define DEBUG_TYPE "Chiara64-mccode-emitter"

STATISTIC(MCNumEmitted, "Number of MC instructions emitted");

unsigned Chiara64MCCodeEmitter::getOImmOpValue(const MCInst &MI, unsigned Idx,
                                           SmallVectorImpl<MCFixup> &Fixups,
                                           const MCSubtargetInfo &STI) const {
  const MCOperand &MO = MI.getOperand(Idx);
  assert(MO.isImm() && "Unexpected MO type.");
  return MO.getImm() - 1;
}

void Chiara64MCCodeEmitter::encodeInstruction(const MCInst &MI, raw_ostream &OS,
                                          SmallVectorImpl<MCFixup> &Fixups,
                                          const MCSubtargetInfo &STI) const {
  const MCInstrDesc &Desc = MII.get(MI.getOpcode());
  unsigned Size = Desc.getSize();
  
  uint32_t Bin = getBinaryCodeForInstr(MI, Fixups ,STI);

  uint16_t LO16 = static_cast<uint16_t>(Bin);
  uint16_t HI16 = static_cast<uint16_t>(Bin >> 16);

  if (Size == 4)
    support::endian::write<uint16_t>(OS, HI16, support::little);

  support::endian::write<uint16_t>(OS, LO16, support::little);
  ++MCNumEmitted; // Keep track of the # of mi's emitted.
}

unsigned
Chiara64MCCodeEmitter::getMachineOpValue(const MCInst &MI, const MCOperand &MO,
                                     SmallVectorImpl<MCFixup> &Fixups,
                                     const MCSubtargetInfo &STI) const {
  if (MO.isReg())
    return Ctx.getRegisterInfo()->getEncodingValue(MO.getReg());

  if (MO.isImm())
    return static_cast<unsigned>(MO.getImm());

  llvm_unreachable("Unhandled expression!");
  return 0;
}

MCCodeEmitter *llvm::createChiara64MCCodeEmitter(const MCInstrInfo &MCII,
                                             const MCRegisterInfo &MRI,
                                             MCContext &Ctx) {
  return new Chiara64MCCodeEmitter(Ctx, MCII);
}

#include "Chiara64GenMCCodeEmitter.inc"
