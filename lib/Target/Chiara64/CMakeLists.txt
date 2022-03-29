add_llvm_component_group(Chiara64)

set(LLVM_TARGET_DEFINITIONS Chiara64.td)

tablegen(LLVM Chiara64GenRegisterInfo.inc -gen-register-info)
tablegen(LLVM Chiara64GenInstrInfo.inc -gen-instr-info)
tablegen(LLVM Chiara64GenMCCodeEmitter.inc -gen-emitter)

add_public_tablegen_target(Chiara64CommonTableGen)

add_llvm_target(Chiara64CodeGen
  Chiara64TargetMachine.cpp
Chiara64AsmPrinter.cpp
  LINK_COMPONENTS
  Core
  CodeGen
  Chiara64Info
  Support
  Target

  ADD_TO_COMPONENT
  Chiara64
  )

add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)
