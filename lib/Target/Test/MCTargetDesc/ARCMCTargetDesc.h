//===- TestMCTargetDesc.h - Test Target Descriptions --------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file provides Test specific target descriptions.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_Test_MCTARGETDESC_TestMCTARGETDESC_H
#define LLVM_LIB_TARGET_Test_MCTARGETDESC_TestMCTARGETDESC_H

#include "llvm/Support/DataTypes.h"

namespace llvm {

class Target;

} // end namespace llvm

// Defines symbolic names for Test registers.  This defines a mapping from
// register name to register number.
#define GET_REGINFO_ENUM
#include "TestGenRegisterInfo.inc"

// Defines symbolic names for the Test instructions.
#define GET_INSTRINFO_ENUM
#include "TestGenInstrInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "TestGenSubtargetInfo.inc"

#endif // LLVM_LIB_TARGET_Test_MCTARGETDESC_TestMCTARGETDESC_H
