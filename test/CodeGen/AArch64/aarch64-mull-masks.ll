; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: llc -mtriple=aarch64-none-linux-gnu < %s -o -| FileCheck %s

define i64 @umull(i64 %x0, i64 %x1) {
; CHECK-LABEL: umull:
; CHECK:       // %bb.0: // %entry
; CHECK-NEXT:    umull x0, w1, w0
; CHECK-NEXT:    ret
entry:
  %and = and i64 %x0, 4294967295
  %and1 = and i64 %x1, 4294967295
  %mul = mul nuw i64 %and1, %and
  ret i64 %mul
}

define i64 @umull2(i64 %x, i32 %y) {
; CHECK-LABEL: umull2:
; CHECK:       // %bb.0: // %entry
; CHECK-NEXT:    umull x0, w0, w1
; CHECK-NEXT:    ret
entry:
  %and = and i64 %x, 4294967295
  %conv = zext i32 %y to i64
  %mul = mul nuw nsw i64 %and, %conv
  ret i64 %mul
}

define i64 @umull2_commuted(i64 %x, i32 %y) {
; CHECK-LABEL: umull2_commuted:
; CHECK:       // %bb.0: // %entry
; CHECK-NEXT:    umull x0, w0, w1
; CHECK-NEXT:    ret
entry:
  %and = and i64 %x, 4294967295
  %conv = zext i32 %y to i64
  %mul = mul nuw nsw i64 %conv, %and
  ret i64 %mul
}

define i64 @smull(i64 %x0, i64 %x1) {
; CHECK-LABEL: smull:
; CHECK:       // %bb.0: // %entry
; CHECK-NEXT:    smull x0, w1, w0
; CHECK-NEXT:    ret
entry:
  %sext = shl i64 %x0, 32
  %conv1 = ashr exact i64 %sext, 32
  %sext4 = shl i64 %x1, 32
  %conv3 = ashr exact i64 %sext4, 32
  %mul = mul nsw i64 %conv3, %conv1
  ret i64 %mul
}

define i64 @smull2(i64 %x, i32 %y) {
; CHECK-LABEL: smull2:
; CHECK:       // %bb.0: // %entry
; CHECK-NEXT:    smull x0, w0, w1
; CHECK-NEXT:    ret
entry:
  %shl = shl i64 %x, 32
  %shr = ashr exact i64 %shl, 32
  %conv = sext i32 %y to i64
  %mul = mul nsw i64 %shr, %conv
  ret i64 %mul
}

define i64 @smull2_commuted(i64 %x, i32 %y) {
; CHECK-LABEL: smull2_commuted:
; CHECK:       // %bb.0: // %entry
; CHECK-NEXT:    smull x0, w0, w1
; CHECK-NEXT:    ret
entry:
  %shl = shl i64 %x, 32
  %shr = ashr exact i64 %shl, 32
  %conv = sext i32 %y to i64
  %mul = mul nsw i64 %conv, %shr
  ret i64 %mul
}
