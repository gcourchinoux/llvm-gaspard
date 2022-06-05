include_directories( ${CMAKE_CURRENT_BINARY_DIR}/.. ${CMAKE_CURRENT_SOURCE_DIR}/.. )

add_llvm_component_library(LLVMGaspardAsmParser
  GaspardAsmParser.cpp

  LINK_COMPONENTS
  MC
  MCParser
  Support
  GaspardDesc
  GaspardInfo

  ADD_TO_COMPONENT
  Gaspard
  )

add_dependencies( LLVMGaspardAsmParser GaspardCommonTableGen )
