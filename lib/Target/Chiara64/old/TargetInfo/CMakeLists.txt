add_llvm_component_library(LLVMChiara64Info
  Chiara64TargetInfo.cpp

  LINK_COMPONENTS
  Support

  ADD_TO_COMPONENT
  Chiara64
)
