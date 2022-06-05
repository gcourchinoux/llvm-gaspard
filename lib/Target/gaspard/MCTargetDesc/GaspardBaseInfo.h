//===-- GaspardBaseInfo.h - Top level definitions for Gaspard MC ----*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains small standalone helper functions and enum definitions for
// the Gaspard target useful for the compiler back-end and the MC libraries.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_Gaspard_MCTARGETDESC_GaspardBASEINFO_H
#define LLVM_LIB_TARGET_Gaspard_MCTARGETDESC_GaspardBASEINFO_H

#include "GaspardMCTargetDesc.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/Support/DataTypes.h"
#include "llvm/Support/ErrorHandling.h"

namespace llvm {

// GaspardII - This namespace holds all of the target specific flags that
// instruction info tracks.
namespace GaspardII {
// Target Operand Flag enum.
enum TOF {
  //===------------------------------------------------------------------===//
  // Gaspard Specific MachineOperand flags.
  MO_NO_FLAG,

  // MO_ABS_HI/LO - Represents the hi or low part of an absolute symbol
  // address.
  MO_ABS_HI,
  MO_ABS_LO,
};
} // namespace GaspardII

static inline unsigned getGaspardRegisterNumbering(unsigned Reg) {
  switch (Reg) {
  case Gaspard::R0:
    return 0;
  case Gaspard::R1:
    return 1;
  case Gaspard::R2:
  case Gaspard::PC:
    return 2;
  case Gaspard::R3:
    return 3;
  case Gaspard::R4:
  case Gaspard::SP:
    return 4;
  case Gaspard::R5:
  case Gaspard::FP:
    return 5;
  case Gaspard::R6:
    return 6;
  case Gaspard::R7:
    return 7;
  case Gaspard::R8:
  case Gaspard::RV:
    return 8;
  case Gaspard::R9:
    return 9;
  case Gaspard::R10:
  case Gaspard::RR1:
    return 10;
  case Gaspard::R11:
  case Gaspard::RR2:
    return 11;
  case Gaspard::R12:
    return 12;
  case Gaspard::R13:
    return 13;
  case Gaspard::R14:
    return 14;
  case Gaspard::R15:
  case Gaspard::RCA:
    return 15;
  case Gaspard::R16:
    return 16;
  case Gaspard::R17:
    return 17;
  case Gaspard::R18:
    return 18;
  case Gaspard::R19:
    return 19;
  case Gaspard::R20:
    return 20;
  case Gaspard::R21:
    return 21;
  case Gaspard::R22:
    return 22;
  case Gaspard::R23:
    return 23;
  case Gaspard::R24:
    return 24;
  case Gaspard::R25:
    return 25;
  case Gaspard::R26:
    return 26;
  case Gaspard::R27:
    return 27;
  case Gaspard::R28:
    return 28;
  case Gaspard::R29:
    return 29;
  case Gaspard::R30:
    return 30;
  case Gaspard::R31:
    return 31;
  default:
    llvm_unreachable("Unknown register number!");
  }
}
} // namespace llvm
#endif // LLVM_LIB_TARGET_Gaspard_MCTARGETDESC_GaspardBASEINFO_H
