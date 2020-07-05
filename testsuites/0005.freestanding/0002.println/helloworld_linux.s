	.file	"helloworld_linux.cc"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"Hello World\n"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB1:
	.text
.LHOTB1:
	.p2align 4
	.globl	_start
	.type	_start, @function
_start:
.LFB13574:
	.cfi_startproc
	movl	$1, %eax
	movl	$1, %edi
	movl	$.LC0, %esi
	movl	$12, %edx
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
.LCOLDE1:
	.text
.LHOTE1:
	.ident	"GCC: (cqwrteur) 11.0.0 20200605 (experimental)"
	.section	.note.GNU-stack,"",@progbits
