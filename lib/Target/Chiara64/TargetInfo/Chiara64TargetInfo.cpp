//===-- CSKYTargetInfo.cpp - CSKY Target Implementation -------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "TargetInfo/Chiara64TargetInfo.h"
#include "llvm/Support/TargetRegistry.h"
using namespace llvm;

Target &llvm::getTheChiara64Target() {
  static Target TheCHIARA64Target;
  return TheCHIARA64Target;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeChiara64TargetInfo() {
  RegisterTarget<Triple::chiara64> X(getTheChiara64Target(), "chiara64", "Chiara64", "CHIARA64");
}
