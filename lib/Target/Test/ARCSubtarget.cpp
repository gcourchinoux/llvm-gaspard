//===- TestSubtarget.cpp - Test Subtarget Information -------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements the Test specific subclass of TargetSubtargetInfo.
//
//===----------------------------------------------------------------------===//

#include "TestSubtarget.h"
#include "Test.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

#define DEBUG_TYPE "Test-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "TestGenSubtargetInfo.inc"

void TestSubtarget::anchor() {}

TestSubtarget::TestSubtarget(const Triple &TT, const std::string &CPU,
                           const std::string &FS, const TargetMachine &TM)
    : TestGenSubtargetInfo(TT, CPU, /*TuneCPU=*/CPU, FS), FrameLowering(*this),
      TLInfo(TM, *this) {}
