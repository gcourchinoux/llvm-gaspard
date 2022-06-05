//===-- Chiara64RegisterInfo.td - Chiara64 Register defs -----------*- tablegen -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
//  Declarations that describe the Chiara64 registers.
//===----------------------------------------------------------------------===//

let Namespace = "Chiara64" in {
  class Chiara64Reg<bits<6> Enc, string n, list<string> alt = []> : Register<n> {
    let HWEncoding{5 - 0} = Enc;
    let AltNames = alt;
  }

  class Chiara64FReg32<bits<5> Enc, string n, list<string> alt = []> : Register<n> {
    let HWEncoding{4 - 0} = Enc;
    let AltNames = alt;
  }

  // Because Chiara64FReg64 register have AsmName and AltNames that alias with their
  // 32-bit sub-register, Chiara64AsmParser will need to coerce a register number
  // from a Chiara64FReg32 to the equivalent Chiara64FReg64 when appropriate.
  def sub32_0 : SubRegIndex<32, 0>;
  def sub32_32 : SubRegIndex<32, 32>;
  def sub64_0 : SubRegIndex<64, 0>;
  def sub64_64 : SubRegIndex<64,64>;

  class Chiara64FReg64<Chiara64FReg32 subreg> : Register<""> {
    let HWEncoding{4 - 0} = subreg.HWEncoding{4 - 0};
    let SubRegs = [subreg];
    let SubRegIndices = [sub32_0];
    let AsmName = subreg.AsmName;
    let AltNames = subreg.AltNames;
  }

  class Chiara64FReg128<Chiara64FReg64 subreg> : Register<""> {
    let HWEncoding{4 - 0} = subreg.HWEncoding{4 - 0};
    let SubRegs = [subreg];
    let SubRegIndices = [sub64_0];
    let AsmName = subreg.AsmName;
    let AltNames = subreg.AltNames;
  }

  def ABIRegAltName : RegAltNameIndex;
} // Namespace = "Chiara64"

let RegAltNameIndices = [ABIRegAltName] in {
  def GPR0 : Chiara64Reg<0, "GPR0", ["GPR0"]>, DwarfRegNum<[0]>;
  def GPR1 : Chiara64Reg<1, "GPR1", ["GPR1"]>, DwarfRegNum<[1]>;
  def GPR2 : Chiara64Reg<2, "GPR2", ["GPR2"]>, DwarfRegNum<[2]>;
  def GPR3 : Chiara64Reg<3, "GPR3", ["GPR3"]>, DwarfRegNum<[3]>;
  def GPR4 : Chiara64Reg<4, "GPR4", ["GPR4"]>, DwarfRegNum<[4]>;
  def GPR5 : Chiara64Reg<5, "GPR5", ["GPR5"]>, DwarfRegNum<[5]>;
  def GPR6 : Chiara64Reg<6, "GPR6", ["GPR6"]>, DwarfRegNum<[6]>;
  def GPR7 : Chiara64Reg<7, "GPR7", ["GPR7"]>, DwarfRegNum<[7]>;
  def GPR8 : Chiara64Reg<8, "GPR8", ["GPR8"]>, DwarfRegNum<[8]>;
  def GPR9 : Chiara64Reg<9, "GPR9", ["GPR9"]>, DwarfRegNum<[9]>;
  def GPR10 : Chiara64Reg<10, "GPR10", ["GPR10"]>, DwarfRegNum<[10]>;
  def GPR11 : Chiara64Reg<11, "GPR11", ["GPR11"]>, DwarfRegNum<[11]>;
  def GPR12 : Chiara64Reg<12, "GPR12", ["GPR12"]>, DwarfRegNum<[12]>;
  def GPR13 : Chiara64Reg<13, "GPR13", ["GPR13"]>, DwarfRegNum<[13]>;
  def GPR14 : Chiara64Reg<14, "GPR14", ["GPR14"]>, DwarfRegNum<[14]>;
  def GPR15 : Chiara64Reg<15, "GPR15", ["GPR15"]>, DwarfRegNum<[15]>;
  def GPR16 : Chiara64Reg<16, "GPR16", ["GPR16"]>, DwarfRegNum<[16]>;
  def GPR17 : Chiara64Reg<17, "GPR17", ["GPR17"]>, DwarfRegNum<[17]>;
  def GPR18 : Chiara64Reg<18, "GPR18", ["GPR18"]>, DwarfRegNum<[18]>;
  def GPR19 : Chiara64Reg<19, "GPR19", ["GPR19"]>, DwarfRegNum<[19]>;
  def GPR20 : Chiara64Reg<20, "GPR20", ["GPR20"]>, DwarfRegNum<[20]>;
  def GPR21 : Chiara64Reg<21, "GPR21", ["GPR21"]>, DwarfRegNum<[21]>;
  def GPR22 : Chiara64Reg<22, "GPR22", ["GPR22"]>, DwarfRegNum<[22]>;
  def GPR23 : Chiara64Reg<23, "GPR23", ["GPR23"]>, DwarfRegNum<[23]>;
  def GPR24 : Chiara64Reg<24, "GPR24", ["GPR24"]>, DwarfRegNum<[24]>;
  def GPR25 : Chiara64Reg<25, "GPR25", ["GPR25"]>, DwarfRegNum<[25]>;
  def GPR26 : Chiara64Reg<26, "GPR26", ["GPR26"]>, DwarfRegNum<[26]>;
  def GPR27 : Chiara64Reg<27, "GPR27", ["GPR27"]>, DwarfRegNum<[27]>;
  def GPR28 : Chiara64Reg<28, "GPR28", ["GPR28"]>, DwarfRegNum<[28]>;
  def GPR29 : Chiara64Reg<29, "GPR29", ["GPR29"]>, DwarfRegNum<[29]>;
  def GPR30 : Chiara64Reg<30, "GPR30", ["GPR30"]>, DwarfRegNum<[30]>;
  def GPR31 : Chiara64Reg<31, "GPR31", ["GPR31"]>, DwarfRegNum<[31]>;
  def C : Chiara64Reg<32, "cr0", ["psr"]>;

}

def GPRTuple : RegisterTuples<
          [sub64_0, sub64_64],
          [(add (sequence "GPR%u", 0, 30)), (add (sequence "GPR%u", 1, 31))],
          [ "gpr0",  "r1",  "r2",  "r3",  "r4",  "r5",  "r6",  "r7",
            "r8",  "r9",  "r10", "r11", "r12", "r13", "r14", "r15",
            "r16", "r17", "r18", "r19", "r20", "r21", "r22", "r23",
            "r24", "r25", "r26", "r27", "r28", "r29", "r30"
          ]>;

// Floating point registers
let RegAltNameIndices = [ABIRegAltName] in {
  def F0_32 : Chiara64FReg32<0, "fr0", ["vr0"]>, DwarfRegNum<[32]>;
  def F1_32 : Chiara64FReg32<1, "fr1", ["vr1"]>, DwarfRegNum<[33]>;
  def F2_32 : Chiara64FReg32<2, "fr2", ["vr2"]>, DwarfRegNum<[34]>;
  def F3_32 : Chiara64FReg32<3, "fr3", ["vr3"]>, DwarfRegNum<[35]>;
  def F4_32 : Chiara64FReg32<4, "fr4", ["vr4"]>, DwarfRegNum<[36]>;
  def F5_32 : Chiara64FReg32<5, "fr5", ["vr5"]>, DwarfRegNum<[37]>;
  def F6_32 : Chiara64FReg32<6, "fr6", ["vr6"]>, DwarfRegNum<[38]>;
  def F7_32 : Chiara64FReg32<7, "fr7", ["vr7"]>, DwarfRegNum<[39]>;
  def F8_32 : Chiara64FReg32<8, "fr8", ["vr8"]>, DwarfRegNum<[40]>;
  def F9_32 : Chiara64FReg32<9, "fr9", ["vr9"]>, DwarfRegNum<[41]>;
  def F10_32 : Chiara64FReg32<10, "fr10", ["vr10"]>, DwarfRegNum<[42]>;
  def F11_32 : Chiara64FReg32<11, "fr11", ["vr11"]>, DwarfRegNum<[43]>;
  def F12_32 : Chiara64FReg32<12, "fr12", ["vr12"]>, DwarfRegNum<[44]>;
  def F13_32 : Chiara64FReg32<13, "fr13", ["vr13"]>, DwarfRegNum<[45]>;
  def F14_32 : Chiara64FReg32<14, "fr14", ["vr14"]>, DwarfRegNum<[46]>;
  def F15_32 : Chiara64FReg32<15, "fr15", ["vr15"]>, DwarfRegNum<[47]>;
  def F16_32 : Chiara64FReg32<16, "fr16", ["vr16"]>, DwarfRegNum<[48]>;
  def F17_32 : Chiara64FReg32<17, "fr17", ["vr17"]>, DwarfRegNum<[49]>;
  def F18_32 : Chiara64FReg32<18, "fr18", ["vr18"]>, DwarfRegNum<[50]>;
  def F19_32 : Chiara64FReg32<19, "fr19", ["vr19"]>, DwarfRegNum<[51]>;
  def F20_32 : Chiara64FReg32<20, "fr20", ["vr20"]>, DwarfRegNum<[52]>;
  def F21_32 : Chiara64FReg32<21, "fr21", ["vr21"]>, DwarfRegNum<[53]>;
  def F22_32 : Chiara64FReg32<22, "fr22", ["vr22"]>, DwarfRegNum<[54]>;
  def F23_32 : Chiara64FReg32<23, "fr23", ["vr23"]>, DwarfRegNum<[55]>;
  def F24_32 : Chiara64FReg32<24, "fr24", ["vr24"]>, DwarfRegNum<[56]>;
  def F25_32 : Chiara64FReg32<25, "fr25", ["vr25"]>, DwarfRegNum<[57]>;
  def F26_32 : Chiara64FReg32<26, "fr26", ["vr26"]>, DwarfRegNum<[58]>;
  def F27_32 : Chiara64FReg32<27, "fr27", ["vr27"]>, DwarfRegNum<[59]>;
  def F28_32 : Chiara64FReg32<28, "fr28", ["vr28"]>, DwarfRegNum<[60]>;
  def F29_32 : Chiara64FReg32<29, "fr29", ["vr29"]>, DwarfRegNum<[61]>;
  def F30_32 : Chiara64FReg32<30, "fr30", ["vr30"]>, DwarfRegNum<[62]>;
  def F31_32 : Chiara64FReg32<31, "fr31", ["vr31"]>, DwarfRegNum<[63]>;

  foreach Index = 0 - 31 in {
    def F#Index#_64 : Chiara64FReg64<!cast<Chiara64FReg32>("F"#Index#"_32")>,
                      DwarfRegNum<[!add(Index, 32)]>;

    def F#Index#_128 : Chiara64FReg128<!cast<Chiara64FReg64>("F"#Index#"_64")>,
                       DwarfRegNum<[!add(Index, 32)]>;
  }
}


//===----------------------------------------------------------------------===//
// Declarations that describe the Chiara64 register class.
//===----------------------------------------------------------------------===//

// The order of registers represents the preferred allocation sequence.
// Registers are listed in the order caller-save, callee-save, specials.
def GPR : RegisterClass<"Chiara64", [i64], 64,
                        (add (sequence "GPR%u", 0, 3), (sequence "GPR%u", 12, 13),
                             (sequence "GPR%u", 18, 25), GPR15, (sequence "GPR%u", 4, 11),
                             (sequence "GPR%u", 16, 17), (sequence "GPR%u", 26, 27), GPR28,
                             (sequence "GPR%u", 29, 30), GPR14, GPR31)> {
  let Size = 64;
}

def GPRPair : RegisterClass<"Chiara64", [untyped], 32, (add GPRTuple)> {
  let Size = 64;
}

def CARRY : RegisterClass<"Chiara64", [i32], 32, (add C)> {
  let Size = 32;
  let CopyCost = -1;
}

// The order of registers represents the preferred allocation sequence.
// Registers are listed in the order caller-save, callee-save, specials.
def FPR32 : RegisterClass<"Chiara64", [f32], 32,
                         (add (sequence "F%u_32", 0, 31))>;
def sFPR32 : RegisterClass<"Chiara64", [f32], 32,
                         (add (sequence "F%u_32", 0, 15))>;

def FPR64 : RegisterClass<"Chiara64", [f64], 64,
                         (add (sequence "F%u_64", 0, 31))>;
def sFPR64 : RegisterClass<"Chiara64", [f64], 64,
                         (add (sequence "F%u_64", 0, 15))>;

def FPR128 : RegisterClass<"Chiara64",
             [v16i8, v8i16, v4i32, v2i64, v4f32, v2f64, v8f16], 128,
             (add (sequence "F%u_128", 0, 31))>;
def sFPR128 : RegisterClass<"Chiara64",
              [v16i8, v8i16, v4i32, v2i64, v4f32, v2f64, v8f16], 128,
              (add (sequence "F%u_128", 0, 15))>;
