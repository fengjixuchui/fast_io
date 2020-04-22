	.file	"helloworld_win32.cc"
	.text
	.section .rdata,"dr"
.LC0:
	.ascii "Hello World\12\0"
	.text
	.globl	wWinMain
	.def	wWinMain;	.scl	2;	.type	32;	.endef
	.seh_proc	wWinMain
wWinMain:
	pushq	%r12
	.seh_pushreg	%r12
	subq	$64, %rsp
	.seh_stackalloc	64
	.seh_endprologue
	movl	$-11, %ecx
	call	GetStdHandle
	movq	%rax, %r12
	movq	_ZN7fast_io12_GLOBAL__N_13outE(%rip), %rcx
	testq	%rcx, %rcx
	je	.L2
	call	CloseHandle
.L2:
	movq	%r12, _ZN7fast_io12_GLOBAL__N_13outE(%rip)
	movq	$0, 32(%rsp)
	leaq	60(%rsp), %r9
	movl	$12, %r8d
	leaq	.LC0(%rip), %rdx
	movq	%r12, %rcx
	call	WriteFile
	testl	%eax, %eax
	jne	.L3
	movb	$0, 0
	ud2
.L3:
	xorl	%eax, %eax
	addq	$64, %rsp
	popq	%r12
	ret
	.seh_endproc
	.section	.text.startup,"x"
	.def	_GLOBAL__sub_I_wWinMain;	.scl	3;	.type	32;	.endef
	.seh_proc	_GLOBAL__sub_I_wWinMain
_GLOBAL__sub_I_wWinMain:
	subq	$40, %rsp
	.seh_stackalloc	40
	.seh_endprologue
	movl	$-11, %ecx
	call	GetStdHandle
	movq	%rax, _ZN7fast_io12_GLOBAL__N_13outE(%rip)
	movl	$-12, %ecx
	addq	$40, %rsp
	jmp	GetStdHandle
	.seh_endproc
	.section	.ctors,"w"
	.align 8
	.quad	_GLOBAL__sub_I_wWinMain
.lcomm _ZN7fast_io12_GLOBAL__N_13outE,8,8
	.ident	"GCC: (master HEAD with MCF thread model, built by cqwrteur.) 10.0.1 20200415 (experimental)"
	.def	GetStdHandle;	.scl	2;	.type	32;	.endef
	.def	CloseHandle;	.scl	2;	.type	32;	.endef
	.def	WriteFile;	.scl	2;	.type	32;	.endef
