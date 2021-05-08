//===-- Chiara64.td - Describe the Chiara64 Target Machine ---------*- tablegen -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

include "llvm/Target/Target.td"

//===----------------------------------------------------------------------===//
// Registers, calling conventions, instruction descriptions.
//===----------------------------------------------------------------------===//

include "Chiara64RegisterInfo.td"
include "Chiara64InstrInfo.td"

//===----------------------------------------------------------------------===//
// Chiara64 processors supported.
//===----------------------------------------------------------------------===//

def : ProcessorModel<"generic-Chiara64", NoSchedModel, []>;

//===----------------------------------------------------------------------===//
// Define the Chiara64 target.
//===----------------------------------------------------------------------===//

def Chiara64InstrInfo : InstrInfo;

def Chiara64 : Target {
  let InstructionSet = Chiara64InstrInfo;
}
