//===-- GaspardAsmBackend.cpp - Gaspard Assembler Backend ---------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "GaspardFixupKinds.h"
#include "MCTargetDesc/GaspardMCTargetDesc.h"
#include "llvm/MC/MCAsmBackend.h"
#include "llvm/MC/MCAssembler.h"
#include "llvm/MC/MCDirectives.h"
#include "llvm/MC/MCELFObjectWriter.h"
#include "llvm/MC/MCFixupKindInfo.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

// Prepare value for the target space
static unsigned adjustFixupValue(unsigned Kind, uint64_t Value) {
  switch (Kind) {
  case FK_Data_1:
  case FK_Data_2:
  case FK_Data_4:
  case FK_Data_8:
    return Value;
  case Gaspard::FIXUP_Gaspard_21:
  case Gaspard::FIXUP_Gaspard_21_F:
  case Gaspard::FIXUP_Gaspard_25:
  case Gaspard::FIXUP_Gaspard_32:
  case Gaspard::FIXUP_Gaspard_HI16:
  case Gaspard::FIXUP_Gaspard_LO16:
    return Value;
  default:
    llvm_unreachable("Unknown fixup kind!");
  }
}

namespace {
class GaspardAsmBackend : public MCAsmBackend {
  Triple::OSType OSType;

public:
  GaspardAsmBackend(const Target &T, Triple::OSType OST)
      : MCAsmBackend(support::big), OSType(OST) {}

  void applyFixup(const MCAssembler &Asm, const MCFixup &Fixup,
                  const MCValue &Target, MutableArrayRef<char> Data,
                  uint64_t Value, bool IsResolved,
                  const MCSubtargetInfo *STI) const override;

  std::unique_ptr<MCObjectTargetWriter>
  createObjectTargetWriter() const override;

  // No instruction requires relaxation
  bool fixupNeedsRelaxation(const MCFixup & /*Fixup*/, uint64_t /*Value*/,
                            const MCRelaxableFragment * /*DF*/,
                            const MCAsmLayout & /*Layout*/) const override {
    return false;
  }

  const MCFixupKindInfo &getFixupKindInfo(MCFixupKind Kind) const override;

  unsigned getNumFixupKinds() const override {
    return Gaspard::NumTargetFixupKinds;
  }

  bool writeNopData(raw_ostream &OS, uint64_t Count) const override;
};

bool GaspardAsmBackend::writeNopData(raw_ostream &OS, uint64_t Count) const {
  if ((Count % 4) != 0)
    return false;

  for (uint64_t i = 0; i < Count; i += 4)
    OS.write("\x15\0\0\0", 4);

  return true;
}

void GaspardAsmBackend::applyFixup(const MCAssembler &Asm, const MCFixup &Fixup,
                                 const MCValue &Target,
                                 MutableArrayRef<char> Data, uint64_t Value,
                                 bool /*IsResolved*/,
                                 const MCSubtargetInfo * /*STI*/) const {
  MCFixupKind Kind = Fixup.getKind();
  Value = adjustFixupValue(static_cast<unsigned>(Kind), Value);

  if (!Value)
    return; // This value doesn't change the encoding

  // Where in the object and where the number of bytes that need
  // fixing up
  unsigned Offset = Fixup.getOffset();
  unsigned NumBytes = (getFixupKindInfo(Kind).TargetSize + 7) / 8;
  unsigned FullSize = 4;

  // Grab current value, if any, from bits.
  uint64_t CurVal = 0;

  // Load instruction and apply value
  for (unsigned i = 0; i != NumBytes; ++i) {
    unsigned Idx = (FullSize - 1 - i);
    CurVal |= static_cast<uint64_t>(static_cast<uint8_t>(Data[Offset + Idx]))
              << (i * 8);
  }

  uint64_t Mask =
      (static_cast<uint64_t>(-1) >> (64 - getFixupKindInfo(Kind).TargetSize));
  CurVal |= Value & Mask;

  // Write out the fixed up bytes back to the code/data bits.
  for (unsigned i = 0; i != NumBytes; ++i) {
    unsigned Idx = (FullSize - 1 - i);
    Data[Offset + Idx] = static_cast<uint8_t>((CurVal >> (i * 8)) & 0xff);
  }
}

std::unique_ptr<MCObjectTargetWriter>
GaspardAsmBackend::createObjectTargetWriter() const {
  return createGaspardELFObjectWriter(MCELFObjectTargetWriter::getOSABI(OSType));
}

const MCFixupKindInfo &
GaspardAsmBackend::getFixupKindInfo(MCFixupKind Kind) const {
  static const MCFixupKindInfo Infos[Gaspard::NumTargetFixupKinds] = {
      // This table *must* be in same the order of fixup_* kinds in
      // GaspardFixupKinds.h.
      // Note: The number of bits indicated here are assumed to be contiguous.
      //   This does not hold true for Gaspard_21 and Gaspard_21_F which are applied
      //   to bits 0x7cffff and 0x7cfffc, respectively. Since the 'bits' counts
      //   here are used only for cosmetic purposes, we set the size to 16 bits
      //   for these 21-bit relocation as llvm/lib/MC/MCAsmStreamer.cpp checks
      //   no bits are set in the fixup range.
      //
      // name          offset bits flags
      {"FIXUP_Gaspard_NONE", 0, 32, 0},
      {"FIXUP_Gaspard_21", 16, 16 /*21*/, 0},
      {"FIXUP_Gaspard_21_F", 16, 16 /*21*/, 0},
      {"FIXUP_Gaspard_25", 7, 25, 0},
      {"FIXUP_Gaspard_32", 0, 32, 0},
      {"FIXUP_Gaspard_HI16", 16, 16, 0},
      {"FIXUP_Gaspard_LO16", 16, 16, 0}};

  if (Kind < FirstTargetFixupKind)
    return MCAsmBackend::getFixupKindInfo(Kind);

  assert(unsigned(Kind - FirstTargetFixupKind) < getNumFixupKinds() &&
         "Invalid kind!");
  return Infos[Kind - FirstTargetFixupKind];
}

} // namespace

MCAsmBackend *llvm::createGaspardAsmBackend(const Target &T,
                                          const MCSubtargetInfo &STI,
                                          const MCRegisterInfo & /*MRI*/,
                                          const MCTargetOptions & /*Options*/) {
  const Triple &TT = STI.getTargetTriple();
  if (!TT.isOSBinFormatELF())
    llvm_unreachable("OS not supported");

  return new GaspardAsmBackend(T, TT.getOS());
}
