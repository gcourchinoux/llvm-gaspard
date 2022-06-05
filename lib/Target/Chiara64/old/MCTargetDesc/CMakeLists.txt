add_llvm_component_library(LLVMChiara64Desc
  Chiara64AsmBackend.cpp
  Chiara64ELFObjectWriter.cpp
  Chiara64MCAsmInfo.cpp
  Chiara64MCTargetDesc.cpp
  Chiara64MCCodeEmitter.cpp
  Chiara64AsmInfo.cpp	
  LINK_COMPONENTS
  MC
  Chiara64Info
  Support

  ADD_TO_COMPONENT
  Chiara64
)
