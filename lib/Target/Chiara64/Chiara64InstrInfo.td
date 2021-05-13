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

class imm<int num, int shift = 0> : Operand<i64>,
  ImmLeaf<i64, "return isShiftedUInt<"#num#", "#shift#">(Imm);"> {
  let EncoderMethod = "getImmOpValue<"#shift#">";
}

class TriOpFrag<dag res> : PatFrag<(ops node: $LHS, node:$MHS, node:$RHS), res>;
class BinOpFrag<dag res> : PatFrag<(ops node:$LHS, node:$RHS), res>;
class UnOpFrag<dag res> : PatFrag<(ops node:$Src), res>;
  
  
  def imm64 : imm<64>;

  
def ADD :  NORMAL< 0b00101110, (outs GPR:$ra), (ins GPR:$rx),
  "add", [(set GPR:$ra, (not GPR:$rx))]>;
def SUB :  NORMAL< 0b00000101, (outs GPR:$ra), (ins GPR:$rx),
  "sub", [(set GPR:$ra, (not GPR:$rx))]>;
// deplacement d'un registre 
def LDrr :  NORMAL< 0b00101100, (outs GPR:$ra), (ins GPR:$rx),
  "disp", [(set GPR:$ra, (not GPR:$rx))]>;

// deplacement d'une valeur immediate dans un rezgistre 

def LDri :  NORMAL_IMMEDIATE< 0b00101100, (outs GPR:$ra), (ins imm64:$rx),
  "disp", [(set GPR:$ra, (not imm64:$rx))]>;
