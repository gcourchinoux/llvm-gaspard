	.text
	.file	"main.c"
	.globl	get_next_virtual_adress         ! -- Begin function get_next_virtual_adress
	.p2align	2
	.type	get_next_virtual_adress,@function
get_next_virtual_adress:                ! @get_next_virtual_adress
.Lget_next_virtual_adress$local:
	.cfi_startproc
! %bb.0:
	st	 fp, [-- GP]
	add	 GP, 0x8,  fp
	sub	 GP, 0x18,  GP
	ld	0[ fp],  GPR3
	mov	hi(actuel_adress),  GPR3
	or	 GPR3, lo(actuel_adress),  GPR3
	ld	0[ GPR3],  GPR9
	ld	4[ GPR3],  GPR3
	sub	 fp, 0x10,  GPR12
	or	 GPR12, 0x4,  GPR12
	st	 GPR3, 0[ GPR12]
	st	 GPR9, -16[ fp]
	bt	.LBB0_1
	st	 GPR0, -20[ fp]
.LBB0_1:                                ! =>This Inner Loop Header: Depth=1
	ld	-20[ fp],  GPR3
	ld	0[ fp],  GPR9
	sha	 GPR9, -0x1f,  GPR12
	sh	 GPR12, -0x1d,  GPR12
	add	 GPR9,  GPR12,  GPR9
	sha	 GPR9, -0x3,  GPR9
	sub.f	 GPR3,  GPR9, r0
	bge	.LBB0_4
	nop
	bt	.LBB0_2
	nop
.LBB0_2:                                !   in Loop: Header=BB0_1 Depth=1
	mov	hi(actuel_adress),  GPR3
	or	 GPR3, lo(actuel_adress),  GPR3
	ld	0[ GPR3],  GPR9
	ld	4[ GPR3],  GPR12
	add	 GPR12, 0x1,  GPR13
	sub.f	 GPR13,  GPR12, r0
	sult	 GPR12
	add	 GPR9,  GPR12,  GPR9
	st	 GPR13, 4[ GPR3]
	bt	.LBB0_3
	st	 GPR9, 0[ GPR3]
.LBB0_3:                                !   in Loop: Header=BB0_1 Depth=1
	ld	-20[ fp],  GPR3
	add	 GPR3, 0x1,  GPR3
	bt	.LBB0_1
	st	 GPR3, -20[ fp]
.LBB0_4:
	sub	 fp, 0x10,  GPR3
	or	 GPR3, 0x4,  GPR3
	ld	0[ GPR3],  GPR9
	ld	-16[ fp],  rv
	ld	-4[fp], pc ! return
	add	 fp, 0x0,  GP
	ld	-8[ fp],  fp
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
	st	 fp, [-- GP]
	add	 GP, 0x8,  fp
	sub	 GP, 0x30,  GP
	mov	0x10,  GPR3
	st	 GPR3, 0[ GP]
	add	 SP, 0x10,  rca
	st	 rca, [-- GP]
	bt	get_next_virtual_adress
	nop
	mov	hi(pag_config),  GPR3
	or	 GPR3, lo(pag_config),  GPR12
	st	 GPR12, -40[ fp]
	st	 GPR9, 0[ GPR12]
	ld	0[ GPR12],  GPR3
	mov	0x14,  GPR9
	st.h	 GPR9, 2[ GPR3]
	ld	0[ GPR12],  GPR3
	mov	0x1,  GPR9
	st.b	 GPR9, 1[ GPR3]
	ld	0[ GPR12],  GPR3
	st.b	 GPR9, 0[ GPR3]
	mov	0xa0,  GPR3
	st	 GPR3, 0[ GP]
	add	 SP, 0x10,  rca
	st	 rca, [-- GP]
	bt	get_next_virtual_adress
	nop
	mov	hi(pages),  GPR3
	or	 GPR3, lo(pages),  GPR3
	st	 GPR9, 0[ GPR3]
	ld	0[ GPR3],  GPR3
	ld	-40[ fp],  GPR9
	ld	0[ GPR9],  GPR9
	st	 GPR3, 12[ GPR9]
	st	 GPR0, 8[ GPR9]
	bt	.LBB1_1
	st	 GPR0, -12[ fp]
.LBB1_1:                                ! =>This Inner Loop Header: Depth=1
	ld	-12[ fp],  GPR3
	sub.f	 GPR3, 0x13, r0
	bgt	.LBB1_4
	nop
	bt	.LBB1_2
	nop
.LBB1_2:                                !   in Loop: Header=BB1_1 Depth=1
	uld.b	-32[ fp],  GPR3
	mov	0xe1,  GPR9
	and	 GPR3,  GPR9,  GPR3
	or	 GPR3, 0x6,  GPR3
	st.b	 GPR3, -32[ fp]
	sub	 fp, 0x20,  GPR3
	st	 GPR3, -36[ fp]
	or	 GPR3, 0x1,  GPR3
	uld.b	0[ GPR3],  GPR9
	mov	0xf0,  GPR12
	and	 GPR9,  GPR12,  GPR9
	st.b	 GPR9, 0[ GPR3]
	mov	0x1,  GPR3
	st	 GPR3, 0[ GP]
	add	 SP, 0x10,  rca
	st	 rca, [-- GP]
	bt	get_next_virtual_adress
	nop
	st	 GPR9, -20[ fp]
	st	 rv, -24[ fp]
	mov	hi(pages),  GPR3
	or	 GPR3, lo(pages),  GPR3
	ld	0[ GPR3],  GPR9
	ld	-12[ fp],  GPR12
	sh	 GPR12, 0x3,  GPR12
	add	 GPR9,  GPR12,  GPR9
	ld	-20[ fp],  GPR12
	st	 GPR12, 20[ GPR9]
	ld	-24[ fp],  GPR12
	st	 GPR12, 16[ GPR9]
	ld	-36[ fp],  GPR12
	or	 GPR12, 0x4,  GPR12
	ld	0[ GPR12],  GPR12
	st	 GPR12, 12[ GPR9]
	ld	-32[ fp],  GPR12
	st	 GPR12, 8[ GPR9]
	ld	0[ GPR3],  GPR9
	ld	-12[ fp],  GPR12
	sh	 GPR12, 0x3,  GPR12
	uld.h	[ GPR9 add  GPR12],  GPR13
	mov	0xfff0,  GPR14
	and	 GPR13,  GPR14,  GPR13
	or	 GPR13, 0x3,  GPR13
	st.h	 GPR13, [ GPR9 add  GPR12]
	ld	0[ GPR3],  GPR9
	ld	-12[ fp],  GPR12
	sh	 GPR12, 0x3,  GPR12
	add	 GPR9,  GPR12,  GPR13
	uld.h	0[ GPR13],  GPR13
	or	 GPR13, 0x100,  GPR13
	st.h	 GPR13, [ GPR9 add  GPR12]
	ld	0[ GPR3],  GPR3
	ld	-12[ fp],  GPR9
	sh	 GPR9, 0x3,  GPR9
	uld.h	[ GPR3 add  GPR9],  GPR12
	mov	0xff0f,  GPR13
	and	 GPR12,  GPR13,  GPR12
	bt	.LBB1_3
	st.h	 GPR12, [ GPR3 add  GPR9]
.LBB1_3:                                !   in Loop: Header=BB1_1 Depth=1
	ld	-12[ fp],  GPR3
	add	 GPR3, 0x1,  GPR3
	bt	.LBB1_1
	st	 GPR3, -12[ fp]
.LBB1_4:
	mov	hi(pag_config),  GPR3
	or	 GPR3, lo(pag_config),  GPR3
	ld	0[ GPR3],  GPR3
	st	 GPR3, 4[ GP]
	mov	hi(.L.str),  GPR3
	or	 GPR3, lo(.L.str),  GPR3
	st	 GPR3, 0[ GP]
	add	 SP, 0x10,  rca
	st	 rca, [-- GP]
	bt	chiara_asm
	nop
	ld	-4[fp], pc ! return
	add	 fp, 0x0,  GP
	ld	-8[ fp],  fp
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
	st	 fp, [-- GP]
	add	 GP, 0x8,  fp
	sub	 GP, 0x8,  GP
	ld	-4[fp], pc ! return
	add	 fp, 0x0,  GP
	ld	-8[ fp],  fp
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
	st	 fp, [-- GP]
	add	 GP, 0x8,  fp
	sub	 GP, 0x8,  GP
	ld	-4[fp], pc ! return
	add	 fp, 0x0,  GP
	ld	-8[ fp],  fp
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
	st	 fp, [-- GP]
	add	 GP, 0x8,  fp
	sub	 GP, 0x8,  GP
	ld	-4[fp], pc ! return
	add	 fp, 0x0,  GP
	ld	-8[ fp],  fp
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
	st	 fp, [-- GP]
	add	 GP, 0x8,  fp
	sub	 GP, 0x8,  GP
	ld	-4[fp], pc ! return
	add	 fp, 0x0,  GP
	ld	-8[ fp],  fp
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
	st	 fp, [-- GP]
	add	 GP, 0x8,  fp
	sub	 GP, 0x18,  GP
	mov	0xff0,  GPR3
	st	 GPR3, 0[ GP]
	add	 SP, 0x10,  rca
	st	 rca, [-- GP]
	bt	get_next_virtual_adress
	nop
	mov	hi(chiara64_interrupt),  GPR3
	or	 GPR3, lo(chiara64_interrupt),  GPR3
	st	 GPR9, 0[ GPR3]
	ld	0[ GPR3],  GPR9
	uld.b	0[ GPR9],  GPR12
	or	 GPR12, 0x1,  GPR12
	st.b	 GPR12, 0[ GPR9]
	ld	0[ GPR3],  GPR9
	mov	hi(chiara_handle_no_stack_pointer),  GPR12
	or	 GPR12, lo(chiara_handle_no_stack_pointer),  GPR12
	st	 GPR12, 12[ GPR9]
	st	 GPR0, 8[ GPR9]
	ld	0[ GPR3],  GPR9
	uld.b	16[ GPR9],  GPR12
	or	 GPR12, 0x1,  GPR12
	st.b	 GPR12, 16[ GPR9]
	ld	0[ GPR3],  GPR9
	mov	hi(chiara_handle_bad_permissions),  GPR12
	or	 GPR12, lo(chiara_handle_bad_permissions),  GPR12
	st	 GPR12, 28[ GPR9]
	st	 GPR0, 24[ GPR9]
	ld	0[ GPR3],  GPR9
	uld.b	32[ GPR9],  GPR12
	or	 GPR12, 0x1,  GPR12
	st.b	 GPR12, 32[ GPR9]
	ld	0[ GPR3],  GPR9
	mov	hi(chiara_handle_bad_opcode),  GPR12
	or	 GPR12, lo(chiara_handle_bad_opcode),  GPR12
	st	 GPR12, 44[ GPR9]
	st	 GPR0, 40[ GPR9]
	ld	0[ GPR3],  GPR9
	uld.b	48[ GPR9],  GPR12
	or	 GPR12, 0x1,  GPR12
	st.b	 GPR12, 48[ GPR9]
	ld	0[ GPR3],  GPR3
	mov	hi(chiara_handle_bad_adress),  GPR9
	or	 GPR9, lo(chiara_handle_bad_adress),  GPR9
	st	 GPR9, 60[ GPR3]
	st	 GPR0, 56[ GPR3]
	mov	0x4,  GPR3
	bt	.LBB6_1
	st	 GPR3, -12[ fp]
.LBB6_1:                                ! =>This Inner Loop Header: Depth=1
	ld	-12[ fp],  GPR3
	sub.f	 GPR3, 0xfe, r0
	bgt	.LBB6_4
	nop
	bt	.LBB6_2
	nop
.LBB6_2:                                !   in Loop: Header=BB6_1 Depth=1
	mov	hi(chiara64_interrupt),  GPR3
	or	 GPR3, lo(chiara64_interrupt),  GPR3
	ld	0[ GPR3],  GPR9
	ld	-12[ fp],  GPR12
	sh	 GPR12, 0x4,  GPR12
	uld.b	[ GPR9 add  GPR12],  GPR13
	mov	0xfe,  GPR14
	and	 GPR13,  GPR14,  GPR13
	st.b	 GPR13, [ GPR9 add  GPR12]
	ld	0[ GPR3],  GPR3
	ld	-12[ fp],  GPR9
	sh	 GPR9, 0x4,  GPR9
	add	 GPR3,  GPR9,  GPR3
	st	 GPR0, 12[ GPR3]
	bt	.LBB6_3
	st	 GPR0, 8[ GPR3]
.LBB6_3:                                !   in Loop: Header=BB6_1 Depth=1
	ld	-12[ fp],  GPR3
	add	 GPR3, 0x1,  GPR3
	bt	.LBB6_1
	st	 GPR3, -12[ fp]
.LBB6_4:
	mov	hi(chiara64_interrupt),  GPR3
	or	 GPR3, lo(chiara64_interrupt),  GPR3
	ld	0[ GPR3],  GPR3
	st	 GPR3, 4[ GP]
	mov	hi(.L.str.1),  GPR3
	or	 GPR3, lo(.L.str.1),  GPR3
	st	 GPR3, 0[ GP]
	add	 SP, 0x10,  rca
	st	 rca, [-- GP]
	bt	chiara_asm
	nop
	ld	-4[fp], pc ! return
	add	 fp, 0x0,  GP
	ld	-8[ fp],  fp
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
	st	 fp, [-- GP]
	add	 GP, 0x8,  fp
	sub	 GP, 0x10,  GP
	mov	hi(.L.str.2),  GPR3
	or	 GPR3, lo(.L.str.2),  GPR3
	st	 GPR3, 0[ GP]
	add	 SP, 0x10,  rca
	st	 rca, [-- GP]
	bt	chiara_asm
	nop
	ld	-4[fp], pc ! return
	add	 fp, 0x0,  GP
	ld	-8[ fp],  fp
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
	st	 fp, [-- GP]
	add	 GP, 0x8,  fp
	sub	 GP, 0x8,  GP
	add	 SP, 0x10,  rca
	st	 rca, [-- GP]
	bt	init_pagination
	nop
	add	 SP, 0x10,  rca
	st	 rca, [-- GP]
	bt	init_interrupts
	nop
	add	 SP, 0x10,  rca
	st	 rca, [-- GP]
	bt	init_restraint_mode
	nop
	or	 GPR0, 0x0,  rv
	ld	-4[fp], pc ! return
	add	 fp, 0x0,  GP
	ld	-8[ fp],  fp
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
