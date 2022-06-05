//===-- GaspardTargetMachine.h - Define TargetMachine for Gaspard --- C++ ---===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file declares the Gaspard specific subclass of TargetMachine.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_Gaspard_GaspardTARGETMACHINE_H
#define LLVM_LIB_TARGET_Gaspard_GaspardTARGETMACHINE_H

#include "GaspardISelLowering.h"
#include "GaspardInstrInfo.h"
#include "GaspardSelectionDAGInfo.h"
#include "GaspardSubtarget.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {

class GaspardTargetMachine : public LLVMTargetMachine {
  GaspardSubtarget Subtarget;
  std::unique_ptr<TargetLoweringObjectFile> TLOF;

public:
  GaspardTargetMachine(const Target &TheTarget, const Triple &TargetTriple,
                     StringRef Cpu, StringRef FeatureString,
                     const TargetOptions &Options,
                     Optional<Reloc::Model> RelocationModel,
                     Optional<CodeModel::Model> CodeModel,
                     CodeGenOpt::Level OptLevel, bool JIT);

  const GaspardSubtarget *
  getSubtargetImpl(const llvm::Function & /*Fn*/) const override {
    return &Subtarget;
  }

  TargetTransformInfo getTargetTransformInfo(const Function &F) override;

  // Pass Pipeline Configuration
  TargetPassConfig *createPassConfig(PassManagerBase &pass_manager) override;

  TargetLoweringObjectFile *getObjFileLowering() const override {
    return TLOF.get();
  }

  bool isMachineVerifierClean() const override {
    return false;
  }
};
} // namespace llvm

#endif // LLVM_LIB_TARGET_Gaspard_GaspardTARGETMACHINE_H
