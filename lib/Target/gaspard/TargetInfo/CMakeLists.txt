add_llvm_component_library(LLVMGaspardInfo
  GaspardTargetInfo.cpp

  LINK_COMPONENTS
  Support

  ADD_TO_COMPONENT
  Gaspard
  )
