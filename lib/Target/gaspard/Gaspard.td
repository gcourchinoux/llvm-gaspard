//===- Gaspard.td - Describe the Gaspard Target Machine --------*- tablegen -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Target-independent interfaces which we are implementing
//===----------------------------------------------------------------------===//

include "llvm/Target/Target.td"

//===----------------------------------------------------------------------===//
// Register File, Calling Conv, Instruction Descriptions
//===----------------------------------------------------------------------===//

include "GaspardSchedule.td"
include "GaspardRegisterInfo.td"
include "GaspardCallingConv.td"
include "GaspardInstrInfo.td"

def GaspardInstrInfo : InstrInfo;

//===----------------------------------------------------------------------===//
// Gaspard processors supported.
//===----------------------------------------------------------------------===//

def : ProcessorModel<"generic", GaspardSchedModel, []>;
def : ProcessorModel<"v11", GaspardSchedModel, []>;

def GaspardInstPrinter : AsmWriter {
  string AsmWriterClassName  = "InstPrinter";
  bit isMCAsmWriter = 1;
}

//===----------------------------------------------------------------------===//
// Declare the target which we are implementing
//===----------------------------------------------------------------------===//

def Gaspard : Target {
  // Pull in Instruction Info:
  let InstructionSet = GaspardInstrInfo;
  let AssemblyWriters = [GaspardInstPrinter];
}
