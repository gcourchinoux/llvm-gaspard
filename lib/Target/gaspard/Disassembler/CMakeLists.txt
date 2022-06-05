add_llvm_component_library(LLVMGaspardDisassembler
  GaspardDisassembler.cpp

  LINK_COMPONENTS
  GaspardDesc
  GaspardInfo
  MC
  MCDisassembler
  Support

  ADD_TO_COMPONENT
  Gaspard
  )
