	.file	"helloworld_win32.cc"
	.text
	.section .rdata,"dr"
.LC0:
	.ascii "Hello World\12\0"
	.section	.text.unlikely,"x"
.LCOLDB1:
	.text
.LHOTB1:
	.globl	wWinMain
	.def	wWinMain;	.scl	2;	.type	32;	.endef
	.seh_proc	wWinMain
wWinMain:
	subq	$72, %rsp
	.seh_stackalloc	72
	.seh_endprologue
	movl	$-11, %ecx
	call	GetStdHandle
	movq	%rax, %rcx
	movq	$0, 32(%rsp)
	leaq	60(%rsp), %r9
	movl	$12, %r8d
	leaq	.LC0(%rip), %rdx
	call	WriteFile
	testl	%eax, %eax
	je	.L3
	xorl	%eax, %eax
	addq	$72, %rsp
	ret
	.seh_endproc
	.section	.text.unlikely,"x"
	.def	wWinMain.cold;	.scl	3;	.type	32;	.endef
	.seh_proc	wWinMain.cold
	.seh_stackalloc	72
	.seh_endprologue
wWinMain.cold:
.L3:
	ud2
	.text
	.section	.text.unlikely,"x"
	.seh_endproc
.LCOLDE1:
	.text
.LHOTE1:
	.ident	"GCC: (master HEAD with MCF thread model, built by cqwrteur.) 11.0.0 20200515 (experimental)"
	.def	GetStdHandle;	.scl	2;	.type	32;	.endef
	.def	WriteFile;	.scl	2;	.type	32;	.endef
