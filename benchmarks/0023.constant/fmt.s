	.file	"fmt.cc"
	.text
	.section .rdata,"dr"
.LC0:
	.ascii "%zu%zu\0"
	.text
	.def	_ZL5scanfPKcz.constprop.0;	.scl	3;	.type	32;	.endef
	.seh_proc	_ZL5scanfPKcz.constprop.0
_ZL5scanfPKcz.constprop.0:
.LFB6768:
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	movq	%rdx, 72(%rsp)
	movq	%r8, 80(%rsp)
	movq	%r9, 88(%rsp)
	leaq	72(%rsp), %rbx
	movq	%rbx, 40(%rsp)
	xorl	%ecx, %ecx
	call	*__imp___acrt_iob_func(%rip)
	movq	%rax, %rcx
	movq	%rbx, %r8
	leaq	.LC0(%rip), %rdx
	call	__mingw_vfscanf
	addq	$48, %rsp
	popq	%rbx
	ret
	.seh_endproc
	.def	_ZN3fmt2v65printIA4_cJyEcEEvP6_iobufRKT_DpOT0_.isra.0;	.scl	3;	.type	32;	.endef
	.seh_proc	_ZN3fmt2v65printIA4_cJyEcEEvP6_iobufRKT_DpOT0_.isra.0
_ZN3fmt2v65printIA4_cJyEcEEvP6_iobufRKT_DpOT0_.isra.0:
.LFB6767:
	pushq	%r12
	.seh_pushreg	%r12
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$80, %rsp
	.seh_stackalloc	80
	.seh_endprologue
	movq	%rcx, %r12
	movq	%rdx, %rbx
	movq	%r8, 64(%rsp)
	leaq	64(%rsp), %rsi
	movq	%rdx, %rcx
	call	strlen
	movq	%rbx, 48(%rsp)
	movq	%rax, 56(%rsp)
	movq	$4, 32(%rsp)
	movq	%rsi, 40(%rsp)
	leaq	48(%rsp), %rdx
	leaq	32(%rsp), %r8
	movq	%r12, %rcx
	call	_ZN3fmt2v66vprintEP6_iobufNS0_17basic_string_viewIcEENS0_11format_argsE
	nop
	addq	$80, %rsp
	popq	%rbx
	popq	%rsi
	popq	%r12
	ret
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
.LC1:
	.ascii "{}\12\0"
	.section	.text.startup,"x"
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
.LFB6000:
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$56, %rsp
	.seh_stackalloc	56
	.seh_endprologue
	call	__main
	leaq	32(%rsp), %rdx
	leaq	40(%rsp), %r8
	leaq	.LC0(%rip), %rcx
	call	_ZL5scanfPKcz.constprop.0
	movq	40(%rsp), %rsi
	addq	32(%rsp), %rsi
	movl	$1, %ecx
	movq	__imp___acrt_iob_func(%rip), %rbx
	call	*%rbx
	movq	%rax, %rcx
	movq	%rsi, %r8
	leaq	.LC1(%rip), %rdx
	call	_ZN3fmt2v65printIA4_cJyEcEEvP6_iobufRKT_DpOT0_.isra.0
	movq	40(%rsp), %rsi
	addq	32(%rsp), %rsi
	movl	$1, %ecx
	call	*%rbx
	movq	%rax, %rcx
	movq	%rsi, %r8
	leaq	.LC1(%rip), %rdx
	call	_ZN3fmt2v65printIA4_cJyEcEEvP6_iobufRKT_DpOT0_.isra.0
	movq	40(%rsp), %rsi
	addq	32(%rsp), %rsi
	movl	$1, %ecx
	call	*%rbx
	movq	%rax, %rcx
	movq	%rsi, %r8
	leaq	.LC1(%rip), %rdx
	call	_ZN3fmt2v65printIA4_cJyEcEEvP6_iobufRKT_DpOT0_.isra.0
	movq	40(%rsp), %rsi
	addq	32(%rsp), %rsi
	movl	$1, %ecx
	call	*%rbx
	movq	%rax, %rcx
	movq	%rsi, %r8
	leaq	.LC1(%rip), %rdx
	call	_ZN3fmt2v65printIA4_cJyEcEEvP6_iobufRKT_DpOT0_.isra.0
	movq	40(%rsp), %rsi
	addq	32(%rsp), %rsi
	movl	$1, %ecx
	call	*%rbx
	movq	%rax, %rcx
	movq	%rsi, %r8
	leaq	.LC1(%rip), %rdx
	call	_ZN3fmt2v65printIA4_cJyEcEEvP6_iobufRKT_DpOT0_.isra.0
	movq	40(%rsp), %rsi
	addq	32(%rsp), %rsi
	movl	$1, %ecx
	call	*%rbx
	movq	%rax, %rcx
	movq	%rsi, %r8
	leaq	.LC1(%rip), %rdx
	call	_ZN3fmt2v65printIA4_cJyEcEEvP6_iobufRKT_DpOT0_.isra.0
	movq	40(%rsp), %rsi
	addq	32(%rsp), %rsi
	movl	$1, %ecx
	call	*%rbx
	movq	%rax, %rcx
	movq	%rsi, %r8
	leaq	.LC1(%rip), %rdx
	call	_ZN3fmt2v65printIA4_cJyEcEEvP6_iobufRKT_DpOT0_.isra.0
	movq	40(%rsp), %rsi
	addq	32(%rsp), %rsi
	movl	$1, %ecx
	call	*%rbx
	movq	%rax, %rcx
	movq	%rsi, %r8
	leaq	.LC1(%rip), %rdx
	call	_ZN3fmt2v65printIA4_cJyEcEEvP6_iobufRKT_DpOT0_.isra.0
	movq	40(%rsp), %rsi
	addq	32(%rsp), %rsi
	movl	$1, %ecx
	call	*%rbx
	movq	%rax, %rcx
	movq	%rsi, %r8
	leaq	.LC1(%rip), %rdx
	call	_ZN3fmt2v65printIA4_cJyEcEEvP6_iobufRKT_DpOT0_.isra.0
	movq	40(%rsp), %rsi
	addq	32(%rsp), %rsi
	movl	$1, %ecx
	call	*%rbx
	movq	%rax, %rcx
	movq	%rsi, %r8
	leaq	.LC1(%rip), %rdx
	call	_ZN3fmt2v65printIA4_cJyEcEEvP6_iobufRKT_DpOT0_.isra.0
	movq	40(%rsp), %rsi
	addq	32(%rsp), %rsi
	movl	$1, %ecx
	call	*%rbx
	movq	%rax, %rcx
	movq	%rsi, %r8
	leaq	.LC1(%rip), %rdx
	call	_ZN3fmt2v65printIA4_cJyEcEEvP6_iobufRKT_DpOT0_.isra.0
	movq	40(%rsp), %rsi
	addq	32(%rsp), %rsi
	movl	$1, %ecx
	call	*%rbx
	movq	%rax, %rcx
	movq	%rsi, %r8
	leaq	.LC1(%rip), %rdx
	call	_ZN3fmt2v65printIA4_cJyEcEEvP6_iobufRKT_DpOT0_.isra.0
	movq	40(%rsp), %rsi
	addq	32(%rsp), %rsi
	movl	$1, %ecx
	call	*%rbx
	movq	%rax, %rcx
	movq	%rsi, %r8
	leaq	.LC1(%rip), %rdx
	call	_ZN3fmt2v65printIA4_cJyEcEEvP6_iobufRKT_DpOT0_.isra.0
	movq	40(%rsp), %rsi
	addq	32(%rsp), %rsi
	movl	$1, %ecx
	call	*%rbx
	movq	%rax, %rcx
	movq	%rsi, %r8
	leaq	.LC1(%rip), %rdx
	call	_ZN3fmt2v65printIA4_cJyEcEEvP6_iobufRKT_DpOT0_.isra.0
	movq	40(%rsp), %rsi
	addq	32(%rsp), %rsi
	movl	$1, %ecx
	call	*%rbx
	movq	%rax, %rcx
	movq	%rsi, %r8
	leaq	.LC1(%rip), %rdx
	call	_ZN3fmt2v65printIA4_cJyEcEEvP6_iobufRKT_DpOT0_.isra.0
	movq	40(%rsp), %rsi
	addq	32(%rsp), %rsi
	movl	$1, %ecx
	call	*%rbx
	movq	%rax, %rcx
	movq	%rsi, %r8
	leaq	.LC1(%rip), %rdx
	call	_ZN3fmt2v65printIA4_cJyEcEEvP6_iobufRKT_DpOT0_.isra.0
	movq	40(%rsp), %rsi
	addq	32(%rsp), %rsi
	movl	$1, %ecx
	call	*%rbx
	movq	%rax, %rcx
	movq	%rsi, %r8
	leaq	.LC1(%rip), %rdx
	call	_ZN3fmt2v65printIA4_cJyEcEEvP6_iobufRKT_DpOT0_.isra.0
	movq	40(%rsp), %rsi
	addq	32(%rsp), %rsi
	movl	$1, %ecx
	call	*%rbx
	movq	%rax, %rcx
	movq	%rsi, %r8
	leaq	.LC1(%rip), %rdx
	call	_ZN3fmt2v65printIA4_cJyEcEEvP6_iobufRKT_DpOT0_.isra.0
	movq	40(%rsp), %rsi
	addq	32(%rsp), %rsi
	movl	$1, %ecx
	call	*%rbx
	movq	%rax, %rcx
	movq	%rsi, %r8
	leaq	.LC1(%rip), %rdx
	call	_ZN3fmt2v65printIA4_cJyEcEEvP6_iobufRKT_DpOT0_.isra.0
	movq	40(%rsp), %rsi
	addq	32(%rsp), %rsi
	movl	$1, %ecx
	call	*%rbx
	movq	%rax, %rcx
	movq	%rsi, %r8
	leaq	.LC1(%rip), %rdx
	call	_ZN3fmt2v65printIA4_cJyEcEEvP6_iobufRKT_DpOT0_.isra.0
	xorl	%eax, %eax
	addq	$56, %rsp
	popq	%rbx
	popq	%rsi
	ret
	.seh_endproc
	.ident	"GCC: (master HEAD with MCF thread model, built by cqwrteur.) 11.0.0 20200515 (experimental)"
	.def	__mingw_vfscanf;	.scl	2;	.type	32;	.endef
	.def	strlen;	.scl	2;	.type	32;	.endef
	.def	_ZN3fmt2v66vprintEP6_iobufNS0_17basic_string_viewIcEENS0_11format_argsE;	.scl	2;	.type	32;	.endef
