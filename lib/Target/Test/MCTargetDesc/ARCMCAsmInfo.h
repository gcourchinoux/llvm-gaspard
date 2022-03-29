//===- TestMCAsmInfo.h - Test asm properties ----------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the declaration of the TestMCAsmInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_Test_MCTARGETDESC_TestMCASMINFO_H
#define LLVM_LIB_TARGET_Test_MCTARGETDESC_TestMCASMINFO_H

#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {

class Triple;

class TestMCAsmInfo : public MCAsmInfoELF {
  void anchor() override;

public:
  explicit TestMCAsmInfo(const Triple &TT);
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_Test_MCTARGETDESC_TestMCASMINFO_H
