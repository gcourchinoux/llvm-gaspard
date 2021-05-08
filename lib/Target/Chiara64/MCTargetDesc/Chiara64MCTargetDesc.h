//===-- Chiara64MCTargetDesc.h - Chiara64 Target Descriptions -----------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file provides Chiara64 specific target descriptions.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_Chiara64_MCTARGETDESC_Chiara64MCTARGETDESC_H
#define LLVM_LIB_TARGET_Chiara64_MCTARGETDESC_Chiara64MCTARGETDESC_H

#include "llvm/MC/MCTargetOptions.h"
#include <memory>

namespace llvm {
class MCAsmBackend;
class MCCodeEmitter;
class MCContext;
class MCInstrInfo;
class MCRegisterInfo;
class MCObjectTargetWriter;
class MCRegisterInfo;
class MCSubtargetInfo;
class Target;
class Triple;

std::unique_ptr<MCObjectTargetWriter> createChiara64ELFObjectWriter();

MCAsmBackend *createChiara64AsmBackend(const Target &T, const MCSubtargetInfo &STI,
                                   const MCRegisterInfo &MRI,
                                   const MCTargetOptions &Options);

MCCodeEmitter *createChiara64MCCodeEmitter(const MCInstrInfo &MCII,
                                       const MCRegisterInfo &MRI,
                                       MCContext &Ctx);
} // namespace llvm

#define GET_REGINFO_ENUM
#include "Chiara64GenRegisterInfo.inc"

#define GET_INSTRINFO_ENUM
#include "Chiara64GenInstrInfo.inc"

#endif // LLVM_LIB_TARGET_Chiara64_MCTARGETDESC_Chiara64MCTARGETDESC_H
