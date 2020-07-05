	.file	"helloworld_linux_writev_floating_point.cc"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"Hello World\n"
.LC1:
	.string	"\nLOL"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB3:
	.text
.LHOTB3:
	.p2align 4
	.globl	_start
	.type	_start, @function
_start:
.LFB13574:
	.cfi_startproc
	subq	$32, %rsp
	.cfi_def_cfa_offset 40
	movl	$1, %edi
	movl	$5, %edx
	leaq	-104(%rsp), %rax
	movb	$53, -104(%rsp)
	leaq	-56(%rsp), %rsi
	movq	%rax, -40(%rsp)
	movq	.LC2(%rip), %rax
	movl	$3420468, -102(%rsp)
	movq	%rax, -99(%rsp)
	leaq	-103(%rsp), %rax
	movq	%rax, -8(%rsp)
	leaq	-105(%rsp), %rax
	movq	%rax, 8(%rsp)
	movl	$20, %eax
	movq	$.LC0, -56(%rsp)
	movq	$12, -48(%rsp)
	movq	$1, -32(%rsp)
	movq	$.LC1, -24(%rsp)
	movq	$4, -16(%rsp)
	movb	$52, -103(%rsp)
	movb	$46, -102(%rsp)
	movq	$12, (%rsp)
	movb	$10, -105(%rsp)
	movq	$1, 16(%rsp)
#APP
# 74 "../../../include/fast_io_hosted/platforms/linux/amd64.h" 1
	syscall
# 0 "" 2
#NO_APP
	cmpq	$-4096, %rax
	jnb	.L3
	movl	$60, %eax
	xorl	%edi, %edi
#APP
# 43 "../../../include/fast_io_hosted/platforms/linux/amd64.h" 1
	syscall
# 0 "" 2
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.type	_start.cold, @function
_start.cold:
.LFSB13574:
#NO_APP
.L3:
	.cfi_def_cfa_offset 40
	ud2
	.cfi_endproc
.LFE13574:
	.text
	.size	_start, .-_start
	.section	.text.unlikely
	.size	_start.cold, .-_start.cold
.LCOLDE3:
	.text
.LHOTE3:
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC2:
	.long	842086712
	.long	959461428
	.ident	"GCC: (cqwrteur) 11.0.0 20200605 (experimental)"
	.section	.note.GNU-stack,"",@progbits
