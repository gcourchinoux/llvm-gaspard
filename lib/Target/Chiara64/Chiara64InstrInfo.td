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

def uimm64      : Operand<i64> {
  let PrintMethod = "printUnsignedImm";
}

def MEMrr : Operand<i32> {
  let PrintMethod = "printMemOperand";
  let MIOperandInfo = (ops GPR, GPR);
}

class TriOpFrag<dag res> : PatFrag<(ops node: $LHS, node:$MHS, node:$RHS), res>;
class BinOpFrag<dag res> : PatFrag<(ops node:$LHS, node:$RHS), res>;
class UnOpFrag<dag res> : PatFrag<(ops node:$Src), res>;
  def ADDRrr : ComplexPattern<i32, 2, "SelectADDRrr", [], []>;
  
  def imm64 : imm<64>;

  
def ADD :  NORMAL< 0b00101110, (outs GPR:$rd), (ins GPR:$rx,GPR:$ra),
  "add", [(set GPR:$rd, (add GPR:$rx,GPR:$ra))]>;

def ADDC :  NORMAL< 0b00011010, (outs GPR:$rd), (ins GPR:$rx,GPR:$ra),
  "addc", [(set GPR:$rd, (addc GPR:$rx,GPR:$ra))]>;  

def SUB :  NORMAL< 0b00101110, (outs GPR:$rd), (ins GPR:$rx,GPR:$ra),
  "sub", [(set GPR:$rd, (sub GPR:$rx,GPR:$ra))]>;

def SUBC :  NORMAL< 0b00011011, (outs GPR:$rd), (ins GPR:$rx,GPR:$ra),
  "subc", [(set GPR:$rd, (subc GPR:$rx,GPR:$ra))]>;

  
def OR :  NORMAL< 0b00001010, (outs GPR:$rd), (ins GPR:$rx,GPR:$ra),
  "Or", [(set GPR:$rd, (or GPR:$rx,GPR:$ra))]>;

def XOR :  NORMAL< 0b00001000, (outs GPR:$rd), (ins GPR:$rx,GPR:$ra),
  "xor", [(set GPR:$rd, (xor GPR:$rx,GPR:$ra))]>;
def AND :  NORMAL< 0b00001001, (outs GPR:$rd), (ins GPR:$rx,GPR:$ra),
  "and", [(set GPR:$rd, (and GPR:$rx,GPR:$ra))]>;

def SHFL :  NORMAL< 0b00001100, (outs GPR:$rd), (ins GPR:$rx,GPR:$ra),
  "shfl", [(set GPR:$rd, (sra GPR:$rx,GPR:$ra))]>;

// shift right

def SHFR :  NORMAL< 0b00001101, (outs GPR:$rd), (ins GPR:$rx,GPR:$ra),
  "shfr", [(set GPR:$rd, (srl GPR:$rx,GPR:$ra))]>;



// incrédibilités decre,mult etc etc 

def MULT :  NORMAL< 0b00000111, (outs GPR:$rd), (ins GPR:$rx,GPR:$ra),
  "mult", [(set GPR:$rd, (mul GPR:$rx,GPR:$ra))]>;
def DIV :  NORMAL< 0b00011100, (outs GPR:$rd), (ins GPR:$rx,GPR:$ra),
  "div", [(set GPR:$rd, (udiv GPR:$rx,GPR:$ra))]>;
def DIVS :  NORMAL< 0b00011101, (outs GPR:$rd), (ins GPR:$rx,GPR:$ra),
  "divs", [(set GPR:$rd, (sdiv GPR:$rx,GPR:$ra))]>;






// deplacement d'un registre 

def LDrr :  NORMAL< 0b00101100, (outs GPR:$ra), (ins GPR:$rx),
  "disp", [(set GPR:$ra, (load GPR:$rx))]>;


// deplacement d'une valeur immediate dans un rezgistre 

def LDri :  NORMAL_IMMEDIATE< 0b00101100, (outs GPR:$ra), (ins MEMrr:$rx),
  "dispa", [(set i64:$ra, (load ADDRrr:$rx))]>;
