#ifndef LLVM_LIB_TARGET_CHIARA64_MCTARGETDESC_CHIARA64MCASMINFO_H
#define LLVM_LIB_TARGET_CHIARA64_MCTARGETDESC_CHIARA64MCASMINFO_H

#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {
class Triple;

class Chiara64MCAsmInfo : public MCAsmInfoELF {
  void anchor() override;

public:
  explicit Chiara64MCAsmInfo(const Triple &TargetTriple);
};
} // namespace llvm

#endif // LLVM_LIB_TARGET_CHIARA64_MCTARGETDESC_CHIARA64MCASMINFO_H
