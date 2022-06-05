//=====-- GaspardMCAsmInfo.h - Gaspard asm properties -----------*- C++ -*--====//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the declaration of the GaspardMCAsmInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_Gaspard_MCTARGETDESC_GaspardMCASMINFO_H
#define LLVM_LIB_TARGET_Gaspard_MCTARGETDESC_GaspardMCASMINFO_H

#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {
class Triple;

class GaspardMCAsmInfo : public MCAsmInfoELF {
  void anchor() override;

public:
  explicit GaspardMCAsmInfo(const Triple &TheTriple,
                          const MCTargetOptions &Options);
};

} // namespace llvm

#endif // LLVM_LIB_TARGET_Gaspard_MCTARGETDESC_GaspardMCASMINFO_H
