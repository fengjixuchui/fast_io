	.file	"printf.cc"
	.text
	.section	.text$_Z5scanfPKcz,"x"
	.linkonce discard
	.globl	_Z5scanfPKcz
	.def	_Z5scanfPKcz;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z5scanfPKcz
_Z5scanfPKcz:
.LFB2:
	pushq	%r12
	.seh_pushreg	%r12
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$56, %rsp
	.seh_stackalloc	56
	.seh_endprologue
	movq	%rcx, %r12
	movq	%rdx, 88(%rsp)
	movq	%r8, 96(%rsp)
	movq	%r9, 104(%rsp)
	leaq	88(%rsp), %rbx
	movq	%rbx, 40(%rsp)
	xorl	%ecx, %ecx
	call	*__imp___acrt_iob_func(%rip)
	movq	%rax, %rcx
	movq	%rbx, %r8
	movq	%r12, %rdx
	call	__mingw_vfscanf
	addq	$56, %rsp
	popq	%rbx
	popq	%r12
	ret
	.seh_endproc
	.section	.text$_Z6printfPKcz,"x"
	.linkonce discard
	.globl	_Z6printfPKcz
	.def	_Z6printfPKcz;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z6printfPKcz
_Z6printfPKcz:
.LFB8:
	pushq	%r12
	.seh_pushreg	%r12
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$56, %rsp
	.seh_stackalloc	56
	.seh_endprologue
	movq	%rcx, %r12
	movq	%rdx, 88(%rsp)
	movq	%r8, 96(%rsp)
	movq	%r9, 104(%rsp)
	leaq	88(%rsp), %rbx
	movq	%rbx, 40(%rsp)
	movl	$1, %ecx
	call	*__imp___acrt_iob_func(%rip)
	movq	%rax, %rcx
	movq	%rbx, %r8
	movq	%r12, %rdx
	call	__mingw_vfprintf
	addq	$56, %rsp
	popq	%rbx
	popq	%r12
	ret
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
.LC0:
	.ascii "%zu%zu\0"
.LC1:
	.ascii "%zu\12\0"
	.section	.text.startup,"x"
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
.LFB46:
	subq	$56, %rsp
	.seh_stackalloc	56
	.seh_endprologue
	call	__main
	leaq	32(%rsp), %rdx
	leaq	40(%rsp), %r8
	leaq	.LC0(%rip), %rcx
	call	_Z5scanfPKcz
	movq	40(%rsp), %rdx
	addq	32(%rsp), %rdx
	leaq	.LC1(%rip), %rcx
	call	_Z6printfPKcz
	movq	40(%rsp), %rdx
	addq	32(%rsp), %rdx
	leaq	.LC1(%rip), %rcx
	call	_Z6printfPKcz
	movq	40(%rsp), %rdx
	addq	32(%rsp), %rdx
	leaq	.LC1(%rip), %rcx
	call	_Z6printfPKcz
	movq	40(%rsp), %rdx
	addq	32(%rsp), %rdx
	leaq	.LC1(%rip), %rcx
	call	_Z6printfPKcz
	movq	40(%rsp), %rdx
	addq	32(%rsp), %rdx
	leaq	.LC1(%rip), %rcx
	call	_Z6printfPKcz
	movq	40(%rsp), %rdx
	addq	32(%rsp), %rdx
	leaq	.LC1(%rip), %rcx
	call	_Z6printfPKcz
	movq	40(%rsp), %rdx
	addq	32(%rsp), %rdx
	leaq	.LC1(%rip), %rcx
	call	_Z6printfPKcz
	movq	40(%rsp), %rdx
	addq	32(%rsp), %rdx
	leaq	.LC1(%rip), %rcx
	call	_Z6printfPKcz
	movq	40(%rsp), %rdx
	addq	32(%rsp), %rdx
	leaq	.LC1(%rip), %rcx
	call	_Z6printfPKcz
	movq	40(%rsp), %rdx
	addq	32(%rsp), %rdx
	leaq	.LC1(%rip), %rcx
	call	_Z6printfPKcz
	movq	40(%rsp), %rdx
	addq	32(%rsp), %rdx
	leaq	.LC1(%rip), %rcx
	call	_Z6printfPKcz
	movq	40(%rsp), %rdx
	addq	32(%rsp), %rdx
	leaq	.LC1(%rip), %rcx
	call	_Z6printfPKcz
	movq	40(%rsp), %rdx
	addq	32(%rsp), %rdx
	leaq	.LC1(%rip), %rcx
	call	_Z6printfPKcz
	movq	40(%rsp), %rdx
	addq	32(%rsp), %rdx
	leaq	.LC1(%rip), %rcx
	call	_Z6printfPKcz
	movq	40(%rsp), %rdx
	addq	32(%rsp), %rdx
	leaq	.LC1(%rip), %rcx
	call	_Z6printfPKcz
	movq	40(%rsp), %rdx
	addq	32(%rsp), %rdx
	leaq	.LC1(%rip), %rcx
	call	_Z6printfPKcz
	movq	40(%rsp), %rdx
	addq	32(%rsp), %rdx
	leaq	.LC1(%rip), %rcx
	call	_Z6printfPKcz
	movq	40(%rsp), %rdx
	addq	32(%rsp), %rdx
	leaq	.LC1(%rip), %rcx
	call	_Z6printfPKcz
	movq	40(%rsp), %rdx
	addq	32(%rsp), %rdx
	leaq	.LC1(%rip), %rcx
	call	_Z6printfPKcz
	movq	40(%rsp), %rdx
	addq	32(%rsp), %rdx
	leaq	.LC1(%rip), %rcx
	call	_Z6printfPKcz
	xorl	%eax, %eax
	addq	$56, %rsp
	ret
	.seh_endproc
	.ident	"GCC: (master HEAD with MCF thread model, built by cqwrteur.) 11.0.0 20200515 (experimental)"
	.def	__mingw_vfscanf;	.scl	2;	.type	32;	.endef
	.def	__mingw_vfprintf;	.scl	2;	.type	32;	.endef
