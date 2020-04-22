	.file	"helloworld_win32_raw.cc"
	.text
	.section .rdata,"dr"
.LC0:
	.ascii "Hello World\12\0"
	.text
	.globl	wWinMain
	.def	wWinMain;	.scl	2;	.type	32;	.endef
	.seh_proc	wWinMain
wWinMain:
	subq	$72, %rsp
	.seh_stackalloc	72
	.seh_endprologue
	movq	$0, 32(%rsp)
	leaq	60(%rsp), %r9
	movl	$12, %r8d
	leaq	.LC0(%rip), %rdx
	movl	$296, %ecx
	call	WriteFile
	testl	%eax, %eax
	jne	.L2
	movb	$0, 0
	ud2
.L2:
	xorl	%eax, %eax
	addq	$72, %rsp
	ret
	.seh_endproc
	.ident	"GCC: (master HEAD with MCF thread model, built by cqwrteur.) 10.0.1 20200415 (experimental)"
	.def	WriteFile;	.scl	2;	.type	32;	.endef
