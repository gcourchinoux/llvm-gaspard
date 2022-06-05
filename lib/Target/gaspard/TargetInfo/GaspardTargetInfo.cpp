//===-- GaspardTargetInfo.cpp - Gaspard Target Implementation -----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "TargetInfo/GaspardTargetInfo.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

Target &llvm::getTheGaspardTarget() {
  static Target TheGaspardTarget;
  return TheGaspardTarget;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeGaspardTargetInfo() {
  RegisterTarget<Triple::Gaspard> X(getTheGaspardTarget(), "Gaspard", "Gaspard",
                                  "Gaspard");
}
