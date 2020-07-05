	.file	"helloworld_linux_writev.cc"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"Hello World\n"
.LC1:
	.string	"\nLOL"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB2:
	.text
.LHOTB2:
	.p2align 4
	.globl	_start
	.type	_start, @function
_start:
.LFB13574:
	.cfi_startproc
	leaq	-84(%rsp), %rax
	movb	$53, -84(%rsp)
	leaq	-72(%rsp), %rsi
	movl	$1, %edi
	movq	%rax, -56(%rsp)
	leaq	-85(%rsp), %rax
	movl	$4, %edx
	movq	%rax, -24(%rsp)
	movl	$20, %eax
	movq	$.LC0, -72(%rsp)
	movq	$12, -64(%rsp)
	movq	$1, -48(%rsp)
	movq	$.LC1, -40(%rsp)
	movq	$4, -32(%rsp)
	movb	$10, -85(%rsp)
	movq	$1, -16(%rsp)
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
	ud2
	.cfi_endproc
.LFE13574:
	.text
	.size	_start, .-_start
	.section	.text.unlikely
	.size	_start.cold, .-_start.cold
.LCOLDE2:
	.text
.LHOTE2:
	.ident	"GCC: (cqwrteur) 11.0.0 20200605 (experimental)"
	.section	.note.GNU-stack,"",@progbits
