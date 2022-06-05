//===-- GaspardMCTargetDesc.h - Gaspard Target Descriptions ---------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file provides Gaspard specific target descriptions.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_Gaspard_MCTARGETDESC_GaspardMCTARGETDESC_H
#define LLVM_LIB_TARGET_Gaspard_MCTARGETDESC_GaspardMCTARGETDESC_H

#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCTargetOptions.h"
#include "llvm/Support/DataTypes.h"

namespace llvm {
class MCAsmBackend;
class MCCodeEmitter;
class MCContext;
class MCInstrInfo;
class MCObjectTargetWriter;
class MCSubtargetInfo;
class Target;

MCCodeEmitter *createGaspardMCCodeEmitter(const MCInstrInfo &MCII,
                                        const MCRegisterInfo &MRI,
                                        MCContext &Ctx);

MCAsmBackend *createGaspardAsmBackend(const Target &T, const MCSubtargetInfo &STI,
                                    const MCRegisterInfo &MRI,
                                    const MCTargetOptions &Options);

std::unique_ptr<MCObjectTargetWriter> createGaspardELFObjectWriter(uint8_t OSABI);
} // namespace llvm

// Defines symbolic names for Gaspard registers.  This defines a mapping from
// register name to register number.
#define GET_REGINFO_ENUM
#include "GaspardGenRegisterInfo.inc"

// Defines symbolic names for the Gaspard instructions.
#define GET_INSTRINFO_ENUM
#include "GaspardGenInstrInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "GaspardGenSubtargetInfo.inc"

#endif // LLVM_LIB_TARGET_Gaspard_MCTARGETDESC_GaspardMCTARGETDESC_H
