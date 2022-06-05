add_llvm_component_group(Gaspard)

set(LLVM_TARGET_DEFINITIONS Gaspard.td)

tablegen(LLVM GaspardGenAsmMatcher.inc -gen-asm-matcher)
tablegen(LLVM GaspardGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM GaspardGenCallingConv.inc -gen-callingconv)
tablegen(LLVM GaspardGenDAGISel.inc -gen-dag-isel)
tablegen(LLVM GaspardGenDisassemblerTables.inc -gen-disassembler)
tablegen(LLVM GaspardGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM GaspardGenMCCodeEmitter.inc -gen-emitter)
tablegen(LLVM GaspardGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM GaspardGenSubtargetInfo.inc -gen-subtarget)

add_public_tablegen_target(GaspardCommonTableGen)

add_llvm_target(GaspardCodeGen
  GaspardAsmPrinter.cpp
  GaspardDelaySlotFiller.cpp
  GaspardFrameLowering.cpp
  GaspardInstrInfo.cpp
  GaspardISelDAGToDAG.cpp
  GaspardISelLowering.cpp
  GaspardMachineFunctionInfo.cpp
  GaspardMCInstLower.cpp
  GaspardMemAluCombiner.cpp
  GaspardRegisterInfo.cpp
  GaspardSelectionDAGInfo.cpp
  GaspardSubtarget.cpp
  GaspardTargetMachine.cpp
  GaspardTargetObjectFile.cpp

  LINK_COMPONENTS
  Analysis
  AsmPrinter
  CodeGen
  Core
  GaspardAsmParser
  GaspardDesc
  GaspardInfo
  MC
  SelectionDAG
  Support
  Target
  TransformUtils

  ADD_TO_COMPONENT
  Gaspard
)

add_subdirectory(AsmParser)
add_subdirectory(Disassembler)
add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)
