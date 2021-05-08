//===--- Chiara64TargetMachine.cpp - Define TargetMachine for Chiara64 ------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Implements the info about Chiara64 target spec.
//
//===----------------------------------------------------------------------===//

#include "Chiara64TargetMachine.h"
#include "TargetInfo/Chiara64TargetInfo.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeChiara64Target() {
  RegisterTargetMachine<Chiara64TargetMachine> X(getTheChiara64Target());
}

static std::string computeDataLayout(const Triple &TT) {
  std::string Ret;

  // Only support little endian for now.
  // TODO: Add support for big endian.
  Ret += "e";

  // Chiara64 is always 32-bit target with the Chiara64v2 ABI as prefer now.
  // It's a 4-byte aligned stack with ELF mangling only.
  Ret += "-m:e-S32-p:32:32-i32:32:32-i64:32:32-f32:32:32-f64:32:32-v64:32:32"
         "-v128:32:32-a:0:32-Fi32-n32";

  return Ret;
}

Chiara64TargetMachine::Chiara64TargetMachine(const Target &T, const Triple &TT,
                                     StringRef CPU, StringRef FS,
                                     const TargetOptions &Options,
                                     Optional<Reloc::Model> RM,
                                     Optional<CodeModel::Model> CM,
                                     CodeGenOpt::Level OL, bool JIT)
    : LLVMTargetMachine(T, computeDataLayout(TT), TT, CPU, FS, Options,
                        RM.getValueOr(Reloc::Static),
                        getEffectiveCodeModel(CM, CodeModel::Small), OL),
      TLOF(std::make_unique<TargetLoweringObjectFileELF>()) {
  initAsmInfo();
}

namespace {
class Chiara64PassConfig : public TargetPassConfig {
public:
  Chiara64PassConfig(Chiara64TargetMachine &TM, PassManagerBase &PM)
      : TargetPassConfig(TM, PM) {}

  Chiara64TargetMachine &getChiara64TargetMachine() const {
    return getTM<Chiara64TargetMachine>();
  }
};

} // namespace

TargetPassConfig *Chiara64TargetMachine::createPassConfig(PassManagerBase &PM) {
  return new Chiara64PassConfig(*this, PM);
}
