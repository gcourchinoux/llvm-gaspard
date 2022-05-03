	.text
	.file	"main.c"
	.globl	get_next_virtual_adress         ! -- Begin function get_next_virtual_adress
	.p2align	2
	.type	get_next_virtual_adress,@function
get_next_virtual_adress:                ! @get_next_virtual_adress
.Lget_next_virtual_adress$local:
	.cfi_startproc
! %bb.0:
	st	%fp, [--%sp]
	add	%sp, 0x8, %fp
	sub	%sp, 0x18, %sp
	ld	0[%fp], %r3
	mov	hi(actuel_adress), %r3
	or	%r3, lo(actuel_adress), %r3
	ld	0[%r3], %r9
	ld	4[%r3], %r3
	sub	%fp, 0x10, %r12
	or	%r12, 0x4, %r12
	st	%r3, 0[%r12]
	st	%r9, -16[%fp]
	bt	.LBB0_1
	st	%r0, -20[%fp]
.LBB0_1:                                ! =>This Inner Loop Header: Depth=1
	ld	-20[%fp], %r3
	ld	0[%fp], %r9
	sha	%r9, -0x1f, %r12
	sh	%r12, -0x1d, %r12
	add	%r9, %r12, %r9
	sha	%r9, -0x3, %r9
	sub.f	%r3, %r9, %r0
	bge	.LBB0_4
	nop
	bt	.LBB0_2
	nop
.LBB0_2:                                !   in Loop: Header=BB0_1 Depth=1
	mov	hi(actuel_adress), %r3
	or	%r3, lo(actuel_adress), %r3
	ld	0[%r3], %r9
	ld	4[%r3], %r12
	add	%r12, 0x1, %r13
	sub.f	%r13, %r12, %r0
	sult	%r12
	add	%r9, %r12, %r9
	st	%r13, 4[%r3]
	bt	.LBB0_3
	st	%r9, 0[%r3]
.LBB0_3:                                !   in Loop: Header=BB0_1 Depth=1
	ld	-20[%fp], %r3
	add	%r3, 0x1, %r3
	bt	.LBB0_1
	st	%r3, -20[%fp]
.LBB0_4:
	sub	%fp, 0x10, %r3
	or	%r3, 0x4, %r3
	ld	0[%r3], %r9
	ld	-16[%fp], %rv
	ld	-4[%fp], %pc ! return
	add	%fp, 0x0, %sp
	ld	-8[%fp], %fp
.Lfunc_end0:
	.size	get_next_virtual_adress, .Lfunc_end0-get_next_virtual_adress
	.cfi_endproc
                                        ! -- End function
	.globl	init_pagination                 ! -- Begin function init_pagination
	.p2align	2
	.type	init_pagination,@function
init_pagination:                        ! @init_pagination
.Linit_pagination$local:
	.cfi_startproc
! %bb.0:
	st	%fp, [--%sp]
	add	%sp, 0x8, %fp
	sub	%sp, 0x30, %sp
	mov	0x10, %r3
	st	%r3, 0[%sp]
	add	%pc, 0x10, %rca
	st	%rca, [--%sp]
	bt	get_next_virtual_adress
	nop
	mov	hi(pag_config), %r3
	or	%r3, lo(pag_config), %r12
	st	%r12, -40[%fp]
	st	%r9, 0[%r12]
	ld	0[%r12], %r3
	mov	0x14, %r9
	st.h	%r9, 2[%r3]
	ld	0[%r12], %r3
	mov	0x1, %r9
	st.b	%r9, 1[%r3]
	ld	0[%r12], %r3
	st.b	%r9, 0[%r3]
	mov	0xa0, %r3
	st	%r3, 0[%sp]
	add	%pc, 0x10, %rca
	st	%rca, [--%sp]
	bt	get_next_virtual_adress
	nop
	mov	hi(pages), %r3
	or	%r3, lo(pages), %r3
	st	%r9, 0[%r3]
	ld	0[%r3], %r3
	ld	-40[%fp], %r9
	ld	0[%r9], %r9
	st	%r3, 12[%r9]
	st	%r0, 8[%r9]
	bt	.LBB1_1
	st	%r0, -12[%fp]
.LBB1_1:                                ! =>This Inner Loop Header: Depth=1
	ld	-12[%fp], %r3
	sub.f	%r3, 0x13, %r0
	bgt	.LBB1_4
	nop
	bt	.LBB1_2
	nop
.LBB1_2:                                !   in Loop: Header=BB1_1 Depth=1
	uld.b	-32[%fp], %r3
	mov	0xe1, %r9
	and	%r3, %r9, %r3
	or	%r3, 0x6, %r3
	st.b	%r3, -32[%fp]
	sub	%fp, 0x20, %r3
	st	%r3, -36[%fp]
	or	%r3, 0x1, %r3
	uld.b	0[%r3], %r9
	mov	0xf0, %r12
	and	%r9, %r12, %r9
	st.b	%r9, 0[%r3]
	mov	0x1, %r3
	st	%r3, 0[%sp]
	add	%pc, 0x10, %rca
	st	%rca, [--%sp]
	bt	get_next_virtual_adress
	nop
	st	%r9, -20[%fp]
	st	%rv, -24[%fp]
	mov	hi(pages), %r3
	or	%r3, lo(pages), %r3
	ld	0[%r3], %r9
	ld	-12[%fp], %r12
	sh	%r12, 0x3, %r12
	add	%r9, %r12, %r9
	ld	-20[%fp], %r12
	st	%r12, 20[%r9]
	ld	-24[%fp], %r12
	st	%r12, 16[%r9]
	ld	-36[%fp], %r12
	or	%r12, 0x4, %r12
	ld	0[%r12], %r12
	st	%r12, 12[%r9]
	ld	-32[%fp], %r12
	st	%r12, 8[%r9]
	ld	0[%r3], %r9
	ld	-12[%fp], %r12
	sh	%r12, 0x3, %r12
	uld.h	[%r9 add %r12], %r13
	mov	0xfff0, %r14
	and	%r13, %r14, %r13
	or	%r13, 0x3, %r13
	st.h	%r13, [%r9 add %r12]
	ld	0[%r3], %r9
	ld	-12[%fp], %r12
	sh	%r12, 0x3, %r12
	add	%r9, %r12, %r13
	uld.h	0[%r13], %r13
	or	%r13, 0x100, %r13
	st.h	%r13, [%r9 add %r12]
	ld	0[%r3], %r3
	ld	-12[%fp], %r9
	sh	%r9, 0x3, %r9
	uld.h	[%r3 add %r9], %r12
	mov	0xff0f, %r13
	and	%r12, %r13, %r12
	bt	.LBB1_3
	st.h	%r12, [%r3 add %r9]
.LBB1_3:                                !   in Loop: Header=BB1_1 Depth=1
	ld	-12[%fp], %r3
	add	%r3, 0x1, %r3
	bt	.LBB1_1
	st	%r3, -12[%fp]
.LBB1_4:
	mov	hi(pag_config), %r3
	or	%r3, lo(pag_config), %r3
	ld	0[%r3], %r3
	st	%r3, 4[%sp]
	mov	hi(.L.str), %r3
	or	%r3, lo(.L.str), %r3
	st	%r3, 0[%sp]
	add	%pc, 0x10, %rca
	st	%rca, [--%sp]
	bt	chiara_asm
	nop
	ld	-4[%fp], %pc ! return
	add	%fp, 0x0, %sp
	ld	-8[%fp], %fp
.Lfunc_end1:
	.size	init_pagination, .Lfunc_end1-init_pagination
	.cfi_endproc
                                        ! -- End function
	.globl	chiara_handle_bad_opcode        ! -- Begin function chiara_handle_bad_opcode
	.p2align	2
	.type	chiara_handle_bad_opcode,@function
chiara_handle_bad_opcode:               ! @chiara_handle_bad_opcode
.Lchiara_handle_bad_opcode$local:
	.cfi_startproc
! %bb.0:
	st	%fp, [--%sp]
	add	%sp, 0x8, %fp
	sub	%sp, 0x8, %sp
	ld	-4[%fp], %pc ! return
	add	%fp, 0x0, %sp
	ld	-8[%fp], %fp
.Lfunc_end2:
	.size	chiara_handle_bad_opcode, .Lfunc_end2-chiara_handle_bad_opcode
	.cfi_endproc
                                        ! -- End function
	.globl	chiara_handle_no_stack_pointer  ! -- Begin function chiara_handle_no_stack_pointer
	.p2align	2
	.type	chiara_handle_no_stack_pointer,@function
chiara_handle_no_stack_pointer:         ! @chiara_handle_no_stack_pointer
.Lchiara_handle_no_stack_pointer$local:
	.cfi_startproc
! %bb.0:
	st	%fp, [--%sp]
	add	%sp, 0x8, %fp
	sub	%sp, 0x8, %sp
	ld	-4[%fp], %pc ! return
	add	%fp, 0x0, %sp
	ld	-8[%fp], %fp
.Lfunc_end3:
	.size	chiara_handle_no_stack_pointer, .Lfunc_end3-chiara_handle_no_stack_pointer
	.cfi_endproc
                                        ! -- End function
	.globl	chiara_handle_bad_permissions   ! -- Begin function chiara_handle_bad_permissions
	.p2align	2
	.type	chiara_handle_bad_permissions,@function
chiara_handle_bad_permissions:          ! @chiara_handle_bad_permissions
.Lchiara_handle_bad_permissions$local:
	.cfi_startproc
! %bb.0:
	st	%fp, [--%sp]
	add	%sp, 0x8, %fp
	sub	%sp, 0x8, %sp
	ld	-4[%fp], %pc ! return
	add	%fp, 0x0, %sp
	ld	-8[%fp], %fp
.Lfunc_end4:
	.size	chiara_handle_bad_permissions, .Lfunc_end4-chiara_handle_bad_permissions
	.cfi_endproc
                                        ! -- End function
	.globl	chiara_handle_bad_adress        ! -- Begin function chiara_handle_bad_adress
	.p2align	2
	.type	chiara_handle_bad_adress,@function
chiara_handle_bad_adress:               ! @chiara_handle_bad_adress
.Lchiara_handle_bad_adress$local:
	.cfi_startproc
! %bb.0:
	st	%fp, [--%sp]
	add	%sp, 0x8, %fp
	sub	%sp, 0x8, %sp
	ld	-4[%fp], %pc ! return
	add	%fp, 0x0, %sp
	ld	-8[%fp], %fp
.Lfunc_end5:
	.size	chiara_handle_bad_adress, .Lfunc_end5-chiara_handle_bad_adress
	.cfi_endproc
                                        ! -- End function
	.globl	init_interrupts                 ! -- Begin function init_interrupts
	.p2align	2
	.type	init_interrupts,@function
init_interrupts:                        ! @init_interrupts
.Linit_interrupts$local:
	.cfi_startproc
! %bb.0:
	st	%fp, [--%sp]
	add	%sp, 0x8, %fp
	sub	%sp, 0x18, %sp
	mov	0xff0, %r3
	st	%r3, 0[%sp]
	add	%pc, 0x10, %rca
	st	%rca, [--%sp]
	bt	get_next_virtual_adress
	nop
	mov	hi(chiara64_interrupt), %r3
	or	%r3, lo(chiara64_interrupt), %r3
	st	%r9, 0[%r3]
	ld	0[%r3], %r9
	uld.b	0[%r9], %r12
	or	%r12, 0x1, %r12
	st.b	%r12, 0[%r9]
	ld	0[%r3], %r9
	mov	hi(chiara_handle_no_stack_pointer), %r12
	or	%r12, lo(chiara_handle_no_stack_pointer), %r12
	st	%r12, 12[%r9]
	st	%r0, 8[%r9]
	ld	0[%r3], %r9
	uld.b	16[%r9], %r12
	or	%r12, 0x1, %r12
	st.b	%r12, 16[%r9]
	ld	0[%r3], %r9
	mov	hi(chiara_handle_bad_permissions), %r12
	or	%r12, lo(chiara_handle_bad_permissions), %r12
	st	%r12, 28[%r9]
	st	%r0, 24[%r9]
	ld	0[%r3], %r9
	uld.b	32[%r9], %r12
	or	%r12, 0x1, %r12
	st.b	%r12, 32[%r9]
	ld	0[%r3], %r9
	mov	hi(chiara_handle_bad_opcode), %r12
	or	%r12, lo(chiara_handle_bad_opcode), %r12
	st	%r12, 44[%r9]
	st	%r0, 40[%r9]
	ld	0[%r3], %r9
	uld.b	48[%r9], %r12
	or	%r12, 0x1, %r12
	st.b	%r12, 48[%r9]
	ld	0[%r3], %r3
	mov	hi(chiara_handle_bad_adress), %r9
	or	%r9, lo(chiara_handle_bad_adress), %r9
	st	%r9, 60[%r3]
	st	%r0, 56[%r3]
	mov	0x4, %r3
	bt	.LBB6_1
	st	%r3, -12[%fp]
.LBB6_1:                                ! =>This Inner Loop Header: Depth=1
	ld	-12[%fp], %r3
	sub.f	%r3, 0xfe, %r0
	bgt	.LBB6_4
	nop
	bt	.LBB6_2
	nop
.LBB6_2:                                !   in Loop: Header=BB6_1 Depth=1
	mov	hi(chiara64_interrupt), %r3
	or	%r3, lo(chiara64_interrupt), %r3
	ld	0[%r3], %r9
	ld	-12[%fp], %r12
	sh	%r12, 0x4, %r12
	uld.b	[%r9 add %r12], %r13
	mov	0xfe, %r14
	and	%r13, %r14, %r13
	st.b	%r13, [%r9 add %r12]
	ld	0[%r3], %r3
	ld	-12[%fp], %r9
	sh	%r9, 0x4, %r9
	add	%r3, %r9, %r3
	st	%r0, 12[%r3]
	bt	.LBB6_3
	st	%r0, 8[%r3]
.LBB6_3:                                !   in Loop: Header=BB6_1 Depth=1
	ld	-12[%fp], %r3
	add	%r3, 0x1, %r3
	bt	.LBB6_1
	st	%r3, -12[%fp]
.LBB6_4:
	mov	hi(chiara64_interrupt), %r3
	or	%r3, lo(chiara64_interrupt), %r3
	ld	0[%r3], %r3
	st	%r3, 4[%sp]
	mov	hi(.L.str.1), %r3
	or	%r3, lo(.L.str.1), %r3
	st	%r3, 0[%sp]
	add	%pc, 0x10, %rca
	st	%rca, [--%sp]
	bt	chiara_asm
	nop
	ld	-4[%fp], %pc ! return
	add	%fp, 0x0, %sp
	ld	-8[%fp], %fp
.Lfunc_end6:
	.size	init_interrupts, .Lfunc_end6-init_interrupts
	.cfi_endproc
                                        ! -- End function
	.globl	init_restraint_mode             ! -- Begin function init_restraint_mode
	.p2align	2
	.type	init_restraint_mode,@function
init_restraint_mode:                    ! @init_restraint_mode
.Linit_restraint_mode$local:
	.cfi_startproc
! %bb.0:
	st	%fp, [--%sp]
	add	%sp, 0x8, %fp
	sub	%sp, 0x10, %sp
	mov	hi(.L.str.2), %r3
	or	%r3, lo(.L.str.2), %r3
	st	%r3, 0[%sp]
	add	%pc, 0x10, %rca
	st	%rca, [--%sp]
	bt	chiara_asm
	nop
	ld	-4[%fp], %pc ! return
	add	%fp, 0x0, %sp
	ld	-8[%fp], %fp
.Lfunc_end7:
	.size	init_restraint_mode, .Lfunc_end7-init_restraint_mode
	.cfi_endproc
                                        ! -- End function
	.globl	main                            ! -- Begin function main
	.p2align	2
	.type	main,@function
main:                                   ! @main
.Lmain$local:
	.cfi_startproc
! %bb.0:
	st	%fp, [--%sp]
	add	%sp, 0x8, %fp
	sub	%sp, 0x8, %sp
	add	%pc, 0x10, %rca
	st	%rca, [--%sp]
	bt	init_pagination
	nop
	add	%pc, 0x10, %rca
	st	%rca, [--%sp]
	bt	init_interrupts
	nop
	add	%pc, 0x10, %rca
	st	%rca, [--%sp]
	bt	init_restraint_mode
	nop
	or	%r0, 0x0, %rv
	ld	-4[%fp], %pc ! return
	add	%fp, 0x0, %sp
	ld	-8[%fp], %fp
.Lfunc_end8:
	.size	main, .Lfunc_end8-main
	.cfi_endproc
                                        ! -- End function
	.type	actuel_adress,@object           ! @actuel_adress
	.data
	.globl	actuel_adress
	.p2align	3
actuel_adress:
.Lactuel_adress$local:
	.quad	4096                            ! 0x1000
	.size	actuel_adress, 8

	.type	pag_config,@object              ! @pag_config
	.comm	pag_config,4,8
	.type	pages,@object                   ! @pages
	.comm	pages,4,8
	.type	.L.str,@object                  ! @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"prcfg PAG,%x"
	.size	.L.str, 13

	.type	chiara64_interrupt,@object      ! @chiara64_interrupt
	.comm	chiara64_interrupt,4,8
	.type	.L.str.1,@object                ! @.str.1
.L.str.1:
	.asciz	"prcfg INT,%x"
	.size	.L.str.1, 13

	.type	.L.str.2,@object                ! @.str.2
.L.str.2:
	.asciz	"prcfg EXEC,2"
	.size	.L.str.2, 13

	.ident	"clang version 7.0.1-8+deb10u2 (tags/RELEASE_701/final)"
	.section	".note.GNU-stack","",@progbits
