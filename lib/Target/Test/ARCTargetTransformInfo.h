//===- TestTargetTransformInfo.h - Test specific TTI --------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
// \file
// This file contains a TargetTransformInfo::Concept conforming object specific
// to the Test target machine. It uses the target's detailed information to
// provide more precise answers to certain TTI queries, while letting the
// target independent and default TTI implementations handle the rest.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_Test_TestTARGETTRANSFORMINFO_H
#define LLVM_LIB_TARGET_Test_TestTARGETTRANSFORMINFO_H

#include "Test.h"
#include "llvm/Analysis/TargetTransformInfo.h"
#include "llvm/CodeGen/BasicTTIImpl.h"

namespace llvm {

class TestSubtarget;
class TestTargetLowering;
class TestTargetMachine;

class TestTTIImpl : public BasicTTIImplBase<TestTTIImpl> {
  using BaseT = BasicTTIImplBase<TestTTIImpl>;
  friend BaseT;

  const TestSubtarget *ST;
  const TestTargetLowering *TLI;

  const TestSubtarget *getST() const { return ST; }
  const TestTargetLowering *getTLI() const { return TLI; }

public:
  explicit TestTTIImpl(const TestTargetMachine *TM, const Function &F)
      : BaseT(TM, F.getParent()->getDataLayout()), ST(TM->getSubtargetImpl()),
        TLI(ST->getTargetLowering()) {}

  // Provide value semantics. MSVC requires that we spell all of these out.
  TestTTIImpl(const TestTTIImpl &Arg)
      : BaseT(static_cast<const BaseT &>(Arg)), ST(Arg.ST), TLI(Arg.TLI) {}
  TestTTIImpl(TestTTIImpl &&Arg)
      : BaseT(std::move(static_cast<BaseT &>(Arg))), ST(std::move(Arg.ST)),
        TLI(std::move(Arg.TLI)) {}
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_Test_TestTARGETTRANSFORMINFO_H
