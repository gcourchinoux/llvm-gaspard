//===-- GaspardELFObjectWriter.cpp - Gaspard ELF Writer -----------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "MCTargetDesc/GaspardBaseInfo.h"
#include "MCTargetDesc/GaspardFixupKinds.h"
#include "llvm/BinaryFormat/ELF.h"
#include "llvm/MC/MCELFObjectWriter.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/Support/ErrorHandling.h"

using namespace llvm;

namespace {

class GaspardELFObjectWriter : public MCELFObjectTargetWriter {
public:
  explicit GaspardELFObjectWriter(uint8_t OSABI);

  ~GaspardELFObjectWriter() override = default;

protected:
  unsigned getRelocType(MCContext &Ctx, const MCValue &Target,
                        const MCFixup &Fixup, bool IsPCRel) const override;
  bool needsRelocateWithSymbol(const MCSymbol &SD,
                               unsigned Type) const override;
};

} // end anonymous namespace

GaspardELFObjectWriter::GaspardELFObjectWriter(uint8_t OSABI)
    : MCELFObjectTargetWriter(/*Is64Bit_=*/false, OSABI, ELF::EM_GASPARD,
                              /*HasRelocationAddend_=*/true) {}

unsigned GaspardELFObjectWriter::getRelocType(MCContext & /*Ctx*/,
                                            const MCValue & /*Target*/,
                                            const MCFixup &Fixup,
                                            bool /*IsPCRel*/) const {
  unsigned Type;
  unsigned Kind = static_cast<unsigned>(Fixup.getKind());
  switch (Kind) {
  case Gaspard::FIXUP_Gaspard_21:
    Type = ELF::R_Gaspard_21;
    break;
  case Gaspard::FIXUP_Gaspard_21_F:
    Type = ELF::R_Gaspard_21_F;
    break;
  case Gaspard::FIXUP_Gaspard_25:
    Type = ELF::R_Gaspard_25;
    break;
  case Gaspard::FIXUP_Gaspard_32:
  case FK_Data_4:
    Type = ELF::R_Gaspard_32;
    break;
  case Gaspard::FIXUP_Gaspard_HI16:
    Type = ELF::R_Gaspard_HI16;
    break;
  case Gaspard::FIXUP_Gaspard_LO16:
    Type = ELF::R_Gaspard_LO16;
    break;
  case Gaspard::FIXUP_Gaspard_NONE:
    Type = ELF::R_Gaspard_NONE;
    break;

  default:
    llvm_unreachable("Invalid fixup kind!");
  }
  return Type;
}

bool GaspardELFObjectWriter::needsRelocateWithSymbol(const MCSymbol & /*SD*/,
                                                   unsigned Type) const {
  switch (Type) {
  case ELF::R_Gaspard_21:
  case ELF::R_Gaspard_21_F:
  case ELF::R_Gaspard_25:
  case ELF::R_Gaspard_32:
  case ELF::R_Gaspard_HI16:
    return true;
  default:
    return false;
  }
}

std::unique_ptr<MCObjectTargetWriter>
llvm::createGaspardELFObjectWriter(uint8_t OSABI) {
  return std::make_unique<GaspardELFObjectWriter>(OSABI);
}
