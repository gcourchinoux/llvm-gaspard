//===-- Chiara64MCAsmInfo.cpp - Chiara64 Asm properties ---------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the declarations of the Chiara64MCAsmInfo properties.
//
//===----------------------------------------------------------------------===//

#include "Chiara64MCAsmInfo.h"
#include "llvm/BinaryFormat/Dwarf.h"
#include "llvm/MC/MCStreamer.h"

using namespace llvm;

void Chiara64MCAsmInfo::anchor() {}

Chiara64MCAsmInfo::Chiara64MCAsmInfo(const Triple &TargetTriple) {
  AlignmentIsInBytes = false;
  SupportsDebugInformation = true;
  CommentString = "#";
}
