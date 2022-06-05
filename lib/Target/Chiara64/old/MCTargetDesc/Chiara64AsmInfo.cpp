
#include "CHIARA64MCAsmInfo.h"
#include "llvm/BinaryFormat/Dwarf.h"
#include "llvm/MC/MCStreamer.h"

using namespace llvm;

void Chiara64MCAsmInfo::anchor() {}

Chiara64MCAsmInfo::Chiara64MCAsmInfo(const Triple &TargetTriple) {
  AlignmentIsInBytes = false;
  SupportsDebugInformation = true;
  CommentString = "//";

  ExceptionsType = ExceptionHandling::DwarfCFI;
}
