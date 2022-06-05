//===- GaspardSubtarget.cpp - Gaspard Subtarget Information -----------*- C++ -*-=//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements the Gaspard specific subclass of TargetSubtarget.
//
//===----------------------------------------------------------------------===//

#include "GaspardSubtarget.h"

#include "Gaspard.h"

#define DEBUG_TYPE "Gaspard-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "GaspardGenSubtargetInfo.inc"

using namespace llvm;

void GaspardSubtarget::initSubtargetFeatures(StringRef CPU, StringRef FS) {
  std::string CPUName = std::string(CPU);
  if (CPUName.empty())
    CPUName = "generic";

  ParseSubtargetFeatures(CPUName, /*TuneCPU*/ CPUName, FS);
}

GaspardSubtarget &GaspardSubtarget::initializeSubtargetDependencies(StringRef CPU,
                                                                StringRef FS) {
  initSubtargetFeatures(CPU, FS);
  return *this;
}

GaspardSubtarget::GaspardSubtarget(const Triple &TargetTriple, StringRef Cpu,
                               StringRef FeatureString, const TargetMachine &TM,
                               const TargetOptions & /*Options*/,
                               CodeModel::Model /*CodeModel*/,
                               CodeGenOpt::Level /*OptLevel*/)
    : GaspardGenSubtargetInfo(TargetTriple, Cpu, /*TuneCPU*/ Cpu, FeatureString),
      FrameLowering(initializeSubtargetDependencies(Cpu, FeatureString)),
      InstrInfo(), TLInfo(TM, *this), TSInfo() {}
