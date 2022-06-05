add_llvm_component_library(LLVMGaspardDesc
  GaspardAsmBackend.cpp
  GaspardELFObjectWriter.cpp
  GaspardInstPrinter.cpp
  GaspardMCAsmInfo.cpp
  GaspardMCCodeEmitter.cpp
  GaspardMCExpr.cpp
  GaspardMCTargetDesc.cpp

  LINK_COMPONENTS
  GaspardInfo
  MC
  MCDisassembler
  Support

  ADD_TO_COMPONENT
  Gaspard
)
