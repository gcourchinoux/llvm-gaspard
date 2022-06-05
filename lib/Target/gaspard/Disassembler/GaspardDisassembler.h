//===- GaspardDisassembler.cpp - Disassembler for Gaspard -----------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file is part of the Gaspard Disassembler.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_Gaspard_DISASSEMBLER_GaspardDISASSEMBLER_H
#define LLVM_LIB_TARGET_Gaspard_DISASSEMBLER_GaspardDISASSEMBLER_H

#define DEBUG_TYPE "Gaspard-disassembler"

#include "llvm/MC/MCDisassembler/MCDisassembler.h"

namespace llvm {

class GaspardDisassembler : public MCDisassembler {
public:
  GaspardDisassembler(const MCSubtargetInfo &STI, MCContext &Ctx);

  ~GaspardDisassembler() override = default;

  // getInstruction - See MCDisassembler.
  MCDisassembler::DecodeStatus
  getInstruction(MCInst &Instr, uint64_t &Size, ArrayRef<uint8_t> Bytes,
                 uint64_t Address, raw_ostream &CStream) const override;
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_Gaspard_DISASSEMBLER_GaspardDISASSEMBLER_H
