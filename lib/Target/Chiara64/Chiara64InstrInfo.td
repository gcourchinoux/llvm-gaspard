//===-- Chiara64InstrInfo.td - Target Description for Chiara64 -----*- tablegen -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file describes the Chiara64 instructions in TableGen format.
//
//===----------------------------------------------------------------------===//

include "Chiara64InstrFormats.td"

//===----------------------------------------------------------------------===//
// Chiara64 specific DAG Nodes.
//===----------------------------------------------------------------------===//

// TODO: Add Chiara64 specific DAG Nodes.

//===----------------------------------------------------------------------===//
// Operand and SDNode transformation definitions.
//===----------------------------------------------------------------------===//


  
def ADD :  NORMAL< 0b00101110, (outs GPR:$ra), (ins GPR:$rx),
  "add", [(set GPR:$ra, (not GPR:$rx))]>;
