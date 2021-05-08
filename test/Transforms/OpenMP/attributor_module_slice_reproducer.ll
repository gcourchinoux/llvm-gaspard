; NOTE: Assertions have been autogenerated by utils/update_test_checks.py UTC_ARGS: --function-signature
; RUN: opt -S -openmpopt < %s | FileCheck %s
; RUN: opt -S -passes=openmpopt < %s | FileCheck %s

define internal fastcc void @"_omp$reduction$reduction_func14"() unnamed_addr {
  %call = call i8 @_ZStplIdESt7complexIT_ERKS2_S4_()
  ret void
}

define linkonce_odr hidden i8 @_ZStplIdESt7complexIT_ERKS2_S4_() local_unnamed_addr {
; CHECK-LABEL: define {{[^@]+}}@_ZStplIdESt7complexIT_ERKS2_S4_() local_unnamed_addr {
; CHECK-NEXT:    ret i8 undef
;
  ret i8 undef
}

declare void @__omp_offloading_2b_4010cad__ZN11qmcplusplus7ompBLAS17gemv_batched_implIfEEiRiciiPKT_PKS5_iS7_iS5_PKPS3_ii_l148(i64, i64, i64, float**, float**, i64, float**, float*, float*, i64) local_unnamed_addr

declare dso_local fastcc void @__kmpc_for_static_init_8u() unnamed_addr

!nvvm.annotations = !{!0}

!0 = !{void (i64, i64, i64, float**, float**, i64, float**, float*, float*, i64)* @__omp_offloading_2b_4010cad__ZN11qmcplusplus7ompBLAS17gemv_batched_implIfEEiRiciiPKT_PKS5_iS7_iS5_PKPS3_ii_l148, !"kernel", i32 1}
