//===- TestTargetInfo.cpp - Test Target Implementation ----------- *- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "TargetInfo/TestTargetInfo.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

Target &llvm::getTheTestTarget() {
  static Target TheTestTarget;
  return TheTestTarget;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeTestTargetInfo() {
  RegisterTarget<Triple::Test> X(getTheTestTarget(), "Test", "Test", "Test");
}
