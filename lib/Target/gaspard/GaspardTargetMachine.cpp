//===-- GaspardTargetMachine.cpp - Define TargetMachine for Gaspard ---------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Implements the info about Gaspard target spec.
//
//===----------------------------------------------------------------------===//

#include "GaspardTargetMachine.h"

#include "Gaspard.h"
#include "GaspardTargetObjectFile.h"
#include "GaspardTargetTransformInfo.h"
#include "TargetInfo/GaspardTargetInfo.h"
#include "llvm/Analysis/TargetTransformInfo.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/Support/FormattedStream.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Target/TargetOptions.h"

using namespace llvm;

namespace llvm {
void initializeGaspardMemAluCombinerPass(PassRegistry &);
} // namespace llvm

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeGaspardTarget() {
  // Register the target.
  RegisterTargetMachine<GaspardTargetMachine> registered_target(
      getTheGaspardTarget());
}

static std::string computeDataLayout() {
  // Data layout (keep in sync with clang/lib/Basic/Targets.cpp)
  return "E"        // Big endian
         "-m:e"     // ELF name manging
         "-p:32:32" // 32-bit pointers, 32 bit aligned
         "-i64:64"  // 64 bit integers, 64 bit aligned
         "-a:0:32"  // 32 bit alignment of objects of aggregate type
         "-n32"     // 32 bit native integer width
         "-S64";    // 64 bit natural stack alignment
}

static Reloc::Model getEffectiveRelocModel(Optional<Reloc::Model> RM) {
  return RM.getValueOr(Reloc::PIC_);
}

GaspardTargetMachine::GaspardTargetMachine(const Target &T, const Triple &TT,
                                       StringRef Cpu, StringRef FeatureString,
                                       const TargetOptions &Options,
                                       Optional<Reloc::Model> RM,
                                       Optional<CodeModel::Model> CodeModel,
                                       CodeGenOpt::Level OptLevel, bool JIT)
    : LLVMTargetMachine(T, computeDataLayout(), TT, Cpu, FeatureString, Options,
                        getEffectiveRelocModel(RM),
                        getEffectiveCodeModel(CodeModel, CodeModel::Medium),
                        OptLevel),
      Subtarget(TT, Cpu, FeatureString, *this, Options, getCodeModel(),
                OptLevel),
      TLOF(new GaspardTargetObjectFile()) {
  initAsmInfo();
}

TargetTransformInfo
GaspardTargetMachine::getTargetTransformInfo(const Function &F) {
  return TargetTransformInfo(GaspardTTIImpl(this, F));
}

namespace {
// Gaspard Code Generator Pass Configuration Options.
class GaspardPassConfig : public TargetPassConfig {
public:
  GaspardPassConfig(GaspardTargetMachine &TM, PassManagerBase *PassManager)
      : TargetPassConfig(TM, *PassManager) {}

  GaspardTargetMachine &getGaspardTargetMachine() const {
    return getTM<GaspardTargetMachine>();
  }

  bool addInstSelector() override;
  void addPreSched2() override;
  void addPreEmitPass() override;
};
} // namespace

TargetPassConfig *
GaspardTargetMachine::createPassConfig(PassManagerBase &PassManager) {
  return new GaspardPassConfig(*this, &PassManager);
}

// Install an instruction selector pass.
bool GaspardPassConfig::addInstSelector() {
  addPass(createGaspardISelDag(getGaspardTargetMachine()));
  return false;
}

// Implemented by targets that want to run passes immediately before
// machine code is emitted.
void GaspardPassConfig::addPreEmitPass() {
  addPass(createGaspardDelaySlotFillerPass(getGaspardTargetMachine()));
}

// Run passes after prolog-epilog insertion and before the second instruction
// scheduling pass.
void GaspardPassConfig::addPreSched2() {
  addPass(createGaspardMemAluCombinerPass());
}
