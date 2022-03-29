//===- Test.h - Top-level interface for Test representation -------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the entry points for global functions defined in the LLVM
// Test back-end.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_Test_Test_H
#define LLVM_LIB_TARGET_Test_Test_H

#include "MCTargetDesc/TestMCTargetDesc.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {

class FunctionPass;
class TestTargetMachine;

FunctionPass *createTestISelDag(TestTargetMachine &TM,
                               CodeGenOpt::Level OptLevel);
FunctionPass *createTestExpandPseudosPass();
FunctionPass *createTestOptAddrMode();
FunctionPass *createTestBranchFinalizePass();

} // end namespace llvm

#endif // LLVM_LIB_TARGET_Test_Test_H
