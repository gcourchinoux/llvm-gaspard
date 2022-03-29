//===- TestTargetMachine.cpp - Define TargetMachine for Test ------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
//
//===----------------------------------------------------------------------===//

#include "TestTargetMachine.h"
#include "Test.h"
#include "TestTargetTransformInfo.h"
#include "TargetInfo/TestTargetInfo.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

static Reloc::Model getRelocModel(Optional<Reloc::Model> RM) {
  return RM.getValueOr(Reloc::Static);
}

/// TestTargetMachine ctor - Create an ILP32 Testhitecture model
TestTargetMachine::TestTargetMachine(const Target &T, const Triple &TT,
                                   StringRef CPU, StringRef FS,
                                   const TargetOptions &Options,
                                   Optional<Reloc::Model> RM,
                                   Optional<CodeModel::Model> CM,
                                   CodeGenOpt::Level OL, bool JIT)
    : LLVMTargetMachine(T,
                        "e-m:e-p:32:32-i1:8:32-i8:8:32-i16:16:32-i32:32:32-"
                        "f32:32:32-i64:32-f64:32-a:0:32-n32",
                        TT, CPU, FS, Options, getRelocModel(RM),
                        getEffectiveCodeModel(CM, CodeModel::Small), OL),
      TLOF(std::make_unique<TargetLoweringObjectFileELF>()),
      Subtarget(TT, std::string(CPU), std::string(FS), *this) {
  initAsmInfo();
}

TestTargetMachine::~TestTargetMachine() = default;

namespace {

/// Test Code Generator Pass Configuration Options.
class TestPassConfig : public TargetPassConfig {
public:
  TestPassConfig(TestTargetMachine &TM, PassManagerBase &PM)
      : TargetPassConfig(TM, PM) {}

  TestTargetMachine &getTestTargetMachine() const {
    return getTM<TestTargetMachine>();
  }

  bool addInstSelector() override;
  void addPreEmitPass() override;
  void addPreRegAlloc() override;
};

} // end anonymous namespace

TargetPassConfig *TestTargetMachine::createPassConfig(PassManagerBase &PM) {
  return new TestPassConfig(*this, PM);
}

bool TestPassConfig::addInstSelector() {
  addPass(createTestISelDag(getTestTargetMachine(), getOptLevel()));
  return false;
}

void TestPassConfig::addPreEmitPass() { addPass(createTestBranchFinalizePass()); }

void TestPassConfig::addPreRegAlloc() {
    addPass(createTestExpandPseudosPass());
    addPass(createTestOptAddrMode());
}

// Force static initialization.
extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeTestTarget() {
  RegisterTargetMachine<TestTargetMachine> X(getTheTestTarget());
}

TargetTransformInfo
TestTargetMachine::getTargetTransformInfo(const Function &F) {
  return TargetTransformInfo(TestTTIImpl(this, F));
}
