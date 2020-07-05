	.arch armv8-a
	.file	"helloworld_linux_writev_floating_point.cc"
	.text
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align	3
.LC0:
	.string	"Hello World\n"
	.align	3
.LC1:
	.string	"\nLOL"
	.text
	.align	2
	.p2align 4,,11
	.global	_start
	.type	_start, %function
_start:
.LFB8228:
	.cfi_startproc
	sub	sp, sp, #144
	.cfi_def_cfa_offset 144
	mov	x9, 52681
	add	x3, sp, 29
	movk	x9, 0xa8f1, lsl 16
	mov	x10, x3
	add	x6, sp, 16
	adrp	x1, .LC0
	adrp	x0, .LC1
	add	x1, x1, :lo12:.LC0
	add	x0, x0, :lo12:.LC1
	mov	x7, 12
	mov	w8, 53
	mov	x5, 1
	mov	x4, 4
	movk	x9, 0x9, lsl 32
	mov	x2, 10
	strb	w8, [sp, 16]
	stp	x1, x7, [sp, 64]
	stp	x6, x5, [sp, 80]
	stp	x0, x4, [sp, 96]
.L2:
	mov	x0, x9
	udiv	x9, x9, x2
	msub	x0, x9, x2, x0
	add	w0, w0, 48
	strb	w0, [x10, -1]!
	sub	x0, x3, x10
	cmp	x0, 11
	bne	.L2
	ldrb	w9, [sp, 18]
	add	x7, sp, 17
	add	x0, sp, 15
	mov	w8, 46
	mov	x1, 12
	mov	x4, 1
	add	x5, sp, 64
	mov	x3, 66
	mov	x6, 5
	strb	w2, [sp, 15]
	strb	w9, [sp, 17]
	strb	w8, [sp, 18]
	stp	x7, x1, [sp, 112]
	stp	x0, x4, [sp, 128]
#APP
// 81 "../../../include/fast_io_hosted/platforms/linux/aarch64.h" 1
	mov x8,x3
	mov x0,x4
	mov x1,x5
	mov x2,x6
	svc 0
	mov x3,x0
	
// 0 "" 2
#NO_APP
	cmn	x3, #4096
	bcs	.L7
	mov	x1, 93
	mov	w2, 0
#APP
// 45 "../../../include/fast_io_hosted/platforms/linux/aarch64.h" 1
	mov x8,x1
	mov x0,x2
	svc 0
	mov x1,x0
	
// 0 "" 2
#NO_APP
.L7:
	brk #1000
	.cfi_endproc
.LFE8228:
	.size	_start, .-_start
	.ident	"GCC: (cqwrteur) 11.0.0 20200629 (experimental)"
	.section	.note.GNU-stack,"",@progbits
