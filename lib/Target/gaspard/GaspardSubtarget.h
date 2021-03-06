//=====-- GaspardSubtarget.h - Define Subtarget for the Gaspard -----*- C++ -*--==//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file declares the Gaspard specific subclass of TargetSubtarget.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_Gaspard_GaspardSUBTARGET_H
#define LLVM_LIB_TARGET_Gaspard_GaspardSUBTARGET_H

#include "GaspardFrameLowering.h"
#include "GaspardISelLowering.h"
#include "GaspardInstrInfo.h"
#include "GaspardSelectionDAGInfo.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/Target/TargetMachine.h"

#define GET_SUBTARGETINFO_HEADER
#include "GaspardGenSubtargetInfo.inc"

namespace llvm {

class GaspardSubtarget : public GaspardGenSubtargetInfo {
public:
  // This constructor initializes the data members to match that
  // of the specified triple.
  GaspardSubtarget(const Triple &TargetTriple, StringRef Cpu,
                 StringRef FeatureString, const TargetMachine &TM,
                 const TargetOptions &Options, CodeModel::Model CodeModel,
                 CodeGenOpt::Level OptLevel);

  // ParseSubtargetFeatures - Parses features string setting specified
  // subtarget options.  Definition of function is auto generated by tblgen.
  void ParseSubtargetFeatures(StringRef CPU, StringRef TuneCPU, StringRef FS);

  GaspardSubtarget &initializeSubtargetDependencies(StringRef CPU, StringRef FS);

  void initSubtargetFeatures(StringRef CPU, StringRef FS);

  bool enableMachineScheduler() const override { return true; }

  const GaspardInstrInfo *getInstrInfo() const override { return &InstrInfo; }

  const TargetFrameLowering *getFrameLowering() const override {
    return &FrameLowering;
  }

  const GaspardRegisterInfo *getRegisterInfo() const override {
    return &InstrInfo.getRegisterInfo();
  }

  const GaspardTargetLowering *getTargetLowering() const override {
    return &TLInfo;
  }

  const GaspardSelectionDAGInfo *getSelectionDAGInfo() const override {
    return &TSInfo;
  }

private:
  GaspardFrameLowering FrameLowering;
  GaspardInstrInfo InstrInfo;
  GaspardTargetLowering TLInfo;
  GaspardSelectionDAGInfo TSInfo;
};
} // namespace llvm

#endif // LLVM_LIB_TARGET_Gaspard_GaspardSUBTARGET_H
