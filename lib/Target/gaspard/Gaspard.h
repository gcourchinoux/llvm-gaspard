//===-- Gaspard.h - Top-level interface for Gaspard representation --*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the entry points for global functions defined in the LLVM
// Gaspard back-end.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_Gaspard_Gaspard_H
#define LLVM_LIB_TARGET_Gaspard_Gaspard_H

#include "llvm/Pass.h"

namespace llvm {
class FunctionPass;
class GaspardTargetMachine;

// createGaspardISelDag - This pass converts a legalized DAG into a
// Gaspard-specific DAG, ready for instruction scheduling.
FunctionPass *createGaspardISelDag(GaspardTargetMachine &TM);

// createGaspardDelaySlotFillerPass - This pass fills delay slots
// with useful instructions or nop's
FunctionPass *createGaspardDelaySlotFillerPass(const GaspardTargetMachine &TM);

// createGaspardMemAluCombinerPass - This pass combines loads/stores and
// arithmetic operations.
FunctionPass *createGaspardMemAluCombinerPass();

// createGaspardSetflagAluCombinerPass - This pass combines SET_FLAG and ALU
// operations.
FunctionPass *createGaspardSetflagAluCombinerPass();

} // namespace llvm

#endif // LLVM_LIB_TARGET_Gaspard_Gaspard_H
