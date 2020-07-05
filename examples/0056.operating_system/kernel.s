	.file	"kernel.cc"
	.text
	.section	.rodata.str1.4,"aMS",@progbits,1
	.align 4
.LC0:
	.string	"Hello Kernel!\nmultiboot_structure:"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC1:
	.string	"\tmagic_number:"
	.text
	.p2align 4
	.globl	kernel_main
	.type	kernel_main, @function
kernel_main:
.LFB13492:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	$753664, %eax
	pushl	%edi
	.cfi_def_cfa_offset 12
	.cfi_offset 7, -12
	pushl	%esi
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushl	%ebx
	.cfi_def_cfa_offset 20
	.cfi_offset 3, -20
	subl	$72, %esp
	.cfi_def_cfa_offset 92
	movl	92(%esp), %ecx
	movl	96(%esp), %edx
	.p2align 4,,10
	.p2align 3
.L2:
	movb	$32, (%eax)
	addl	$2, %eax
	cmpl	$757664, %eax
	jne	.L2
	movl	%ecx, %ebx
	movl	$30768, %eax
	movl	$.LC0, 32(%esp)
	andl	$15, %ebx
	movw	%ax, 11(%esp)
	cmpb	$10, %bl
	leal	87(%ebx), %esi
	leal	48(%ebx), %eax
	movl	%ecx, %ebx
	cmovge	%esi, %eax
	shrb	$4, %bl
	movl	$34, 36(%esp)
	movl	%ebx, %esi
	movl	$12, 44(%esp)
	movb	%al, 22(%esp)
	movl	%ecx, %eax
	leal	87(%esi), %edi
	leal	48(%esi), %ebx
	shrl	$8, %eax
	movl	$.LC1, 48(%esp)
	movl	%eax, %ebp
	movl	%esi, %eax
	movl	$14, 52(%esp)
	cmpb	$10, %al
	movl	%ebp, %eax
	cmovge	%edi, %ebx
	andl	$15, %eax
	leal	87(%eax), %edi
	leal	48(%eax), %esi
	movb	%bl, 21(%esp)
	movl	%ecx, %ebx
	shrl	$12, %ebx
	cmpb	$10, %al
	movl	%edi, %eax
	cmovl	%esi, %eax
	andl	$15, %ebx
	leal	48(%ebx), %esi
	leal	87(%ebx), %edi
	movb	%al, 20(%esp)
	movl	%ecx, %eax
	shrl	$16, %eax
	cmpb	$10, %bl
	cmovl	%esi, %edi
	andl	$15, %eax
	leal	48(%eax), %esi
	movl	%edi, %ebx
	leal	87(%eax), %edi
	movb	%bl, 19(%esp)
	movl	%ecx, %ebx
	shrl	$20, %ebx
	cmpb	$10, %al
	movl	%edi, %eax
	cmovl	%esi, %eax
	andl	$15, %ebx
	leal	48(%ebx), %esi
	leal	87(%ebx), %edi
	movb	%al, 18(%esp)
	movl	%ecx, %eax
	shrl	$24, %eax
	cmpb	$10, %bl
	cmovl	%esi, %edi
	andl	$15, %eax
	shrl	$28, %ecx
	leal	87(%eax), %esi
	cmpb	$10, %al
	movl	%edi, %ebx
	movb	%bl, 17(%esp)
	leal	48(%eax), %ebx
	leal	48(%ecx), %eax
	cmovge	%esi, %ebx
	cmpb	$10, %cl
	movb	%bl, 16(%esp)
	leal	87(%ecx), %ebx
	movl	$12336, %ecx
	cmovge	%ebx, %eax
	movw	%cx, 13(%esp)
	movb	%al, 15(%esp)
	leal	11(%esp), %eax
	movl	%eax, 40(%esp)
	cmpl	$15, %edx
	jbe	.L45
	cmpl	$255, %edx
	jbe	.L46
	cmpl	$4095, %edx
	jbe	.L47
	cmpl	$65535, %edx
	jbe	.L86
	movl	%edx, %eax
	shrl	$16, %eax
	cmpl	$1048575, %edx
	jbe	.L87
	cmpl	$255, %eax
	jbe	.L49
	cmpl	$4095, %eax
	seta	%al
	movzbl	%al, %eax
	addl	$7, %eax
.L25:
	leal	23(%esp), %esi
	leal	(%esi,%eax), %ecx
.L27:
	movzbl	%dl, %ebx
	subl	$2, %ecx
	shrl	$8, %edx
	movzwl	_ZN7fast_io7details24shared_static_base_tableIcLj16ELb0ELb0EE5tableE(%ebx,%ebx), %ebx
	movw	%bx, (%ecx)
	cmpl	$255, %edx
	ja	.L27
	cmpl	$15, %edx
	ja	.L20
.L19:
	leal	87(%edx), %edi
	leal	48(%edx), %ebx
	cmpl	$10, %edx
	cmovnb	%edi, %ebx
	movb	%bl, -1(%ecx)
.L28:
	movl	%eax, 60(%esp)
	leal	10(%esp), %eax
	xorl	%ebp, %ebp
	xorl	%edx, %edx
	movl	%eax, 64(%esp)
	leal	32(%esp), %eax
	movl	%esi, 56(%esp)
	movb	$10, 10(%esp)
	movl	$1, 68(%esp)
	movl	%eax, (%esp)
.L44:
	movl	(%esp), %esi
	movl	(%esi), %eax
	movl	4(%esi), %edi
	addl	%eax, %edi
	cmpl	%edi, %eax
	je	.L30
	.p2align 4,,10
	.p2align 3
.L43:
	movzbl	(%eax), %ecx
	cmpb	$9, %cl
	je	.L31
	cmpb	$10, %cl
	jne	.L32
	addl	$1, %edx
	cmpl	$25, %edx
	je	.L52
	leal	(%edx,%edx,4), %ecx
	sall	$5, %ecx
	addl	$753664, %ecx
.L33:
	leal	160(%ecx), %ebx
	.p2align 4,,10
	.p2align 3
.L35:
	movb	$32, (%ecx)
	addl	$2, %ecx
	cmpl	%ebx, %ecx
	jne	.L35
.L56:
	xorl	%ebp, %ebp
.L34:
	addl	$1, %eax
	cmpl	%eax, %edi
	jne	.L43
.L30:
	addl	$8, (%esp)
	movl	(%esp), %eax
	leal	72(%esp), %esi
	cmpl	%eax, %esi
	jne	.L44
	addl	$72, %esp
	.cfi_remember_state
	.cfi_def_cfa_offset 20
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 16
	popl	%esi
	.cfi_restore 6
	.cfi_def_cfa_offset 12
	popl	%edi
	.cfi_restore 7
	.cfi_def_cfa_offset 8
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa_offset 4
	ret
.L46:
	.cfi_restore_state
	leal	25(%esp), %ecx
	movl	$2, %eax
	leal	23(%esp), %esi
.L20:
	movzwl	_ZN7fast_io7details24shared_static_base_tableIcLj16ELb0ELb0EE5tableE(%edx,%edx), %edx
	movw	%dx, -2(%ecx)
	jmp	.L28
	.p2align 4,,10
	.p2align 3
.L32:
	leal	(%edx,%edx,4), %ebx
	sall	$4, %ebx
	leal	0(%ebp,%ebx), %esi
	addl	$1, %ebp
	addl	%esi, %esi
	movb	%cl, 753664(%esi)
	cmpl	$80, %ebp
	jne	.L34
	addl	$1, %edx
	cmpl	$25, %edx
	je	.L57
	leal	753824(%ebx,%ebx), %ecx
.L41:
	leal	160(%ecx), %ebx
	.p2align 4,,10
	.p2align 3
.L42:
	movb	$32, (%ecx)
	addl	$2, %ecx
	cmpl	%ebx, %ecx
	jne	.L42
	jmp	.L56
	.p2align 4,,10
	.p2align 3
.L31:
	cmpl	$80, %ebp
	je	.L88
	leal	(%edx,%edx,4), %ecx
	sall	$4, %ecx
	leal	0(%ebp,%ecx), %esi
	movl	%ecx, 4(%esp)
	movl	%ebp, %ecx
	addl	%esi, %esi
	andl	$7, %ecx
	movb	$32, 753664(%esi)
	leal	753664(%esi), %ebx
	cmpl	$7, %ecx
	je	.L38
	movb	$32, 753666(%esi)
	cmpl	$6, %ecx
	je	.L38
	movb	$32, 753668(%esi)
	cmpl	$5, %ecx
	je	.L38
	movb	$32, 753670(%esi)
	cmpl	$4, %ecx
	je	.L38
	movb	$32, 753672(%esi)
	cmpl	$3, %ecx
	je	.L38
	movb	$32, 753674(%esi)
	leal	6(%ecx), %esi
	cmpl	$2, %ecx
	je	.L38
	movb	$32, 12(%ebx)
	cmpl	$6, %esi
	jne	.L38
	movb	$32, 14(%ebx)
.L38:
	addl	$8, %ebp
	subl	%ecx, %ebp
	cmpl	$80, %ebp
	jne	.L34
	addl	$1, %edx
	cmpl	$25, %edx
	je	.L55
	movl	4(%esp), %esi
	leal	753824(%esi,%esi), %ecx
.L39:
	leal	160(%ecx), %ebx
	.p2align 4,,10
	.p2align 3
.L40:
	movb	$32, (%ecx)
	addl	$2, %ecx
	cmpl	%ebx, %ecx
	jne	.L40
	jmp	.L56
.L88:
	addl	$1, %edx
	leal	(%edx,%edx,4), %ebx
	sall	$5, %ebx
	leal	753664(%ebx), %ecx
	addl	$753824, %ebx
	.p2align 4,,10
	.p2align 3
.L37:
	movb	$32, (%ecx)
	addl	$2, %ecx
	cmpl	%ebx, %ecx
	jne	.L37
	jmp	.L56
.L52:
	movl	$753664, %ecx
	xorl	%edx, %edx
	jmp	.L33
.L55:
	movl	$753664, %ecx
	xorl	%edx, %edx
	jmp	.L39
.L57:
	movl	$753664, %ecx
	xorl	%edx, %edx
	jmp	.L41
.L49:
	movl	$6, %eax
	leal	29(%esp), %ecx
	leal	23(%esp), %esi
	jmp	.L27
.L87:
	movl	$5, %eax
	jmp	.L25
.L86:
	movl	$4, %eax
	jmp	.L25
.L47:
	movl	$3, %eax
	jmp	.L25
.L45:
	leal	24(%esp), %ecx
	movl	$1, %eax
	leal	23(%esp), %esi
	jmp	.L19
	.cfi_endproc
.LFE13492:
	.size	kernel_main, .-kernel_main
	.weak	_ZN7fast_io7details24shared_static_base_tableIcLj16ELb0ELb0EE5tableE
	.section	.rodata._ZN7fast_io7details24shared_static_base_tableIcLj16ELb0ELb0EE5tableE,"aG",@progbits,_ZN7fast_io7details24shared_static_base_tableIcLj16ELb0ELb0EE5tableE,comdat
	.align 32
	.type	_ZN7fast_io7details24shared_static_base_tableIcLj16ELb0ELb0EE5tableE, @gnu_unique_object
	.size	_ZN7fast_io7details24shared_static_base_tableIcLj16ELb0ELb0EE5tableE, 512
_ZN7fast_io7details24shared_static_base_tableIcLj16ELb0ELb0EE5tableE:
	.byte	48
	.byte	48
	.byte	48
	.byte	49
	.byte	48
	.byte	50
	.byte	48
	.byte	51
	.byte	48
	.byte	52
	.byte	48
	.byte	53
	.byte	48
	.byte	54
	.byte	48
	.byte	55
	.byte	48
	.byte	56
	.byte	48
	.byte	57
	.byte	48
	.byte	97
	.byte	48
	.byte	98
	.byte	48
	.byte	99
	.byte	48
	.byte	100
	.byte	48
	.byte	101
	.byte	48
	.byte	102
	.byte	49
	.byte	48
	.byte	49
	.byte	49
	.byte	49
	.byte	50
	.byte	49
	.byte	51
	.byte	49
	.byte	52
	.byte	49
	.byte	53
	.byte	49
	.byte	54
	.byte	49
	.byte	55
	.byte	49
	.byte	56
	.byte	49
	.byte	57
	.byte	49
	.byte	97
	.byte	49
	.byte	98
	.byte	49
	.byte	99
	.byte	49
	.byte	100
	.byte	49
	.byte	101
	.byte	49
	.byte	102
	.byte	50
	.byte	48
	.byte	50
	.byte	49
	.byte	50
	.byte	50
	.byte	50
	.byte	51
	.byte	50
	.byte	52
	.byte	50
	.byte	53
	.byte	50
	.byte	54
	.byte	50
	.byte	55
	.byte	50
	.byte	56
	.byte	50
	.byte	57
	.byte	50
	.byte	97
	.byte	50
	.byte	98
	.byte	50
	.byte	99
	.byte	50
	.byte	100
	.byte	50
	.byte	101
	.byte	50
	.byte	102
	.byte	51
	.byte	48
	.byte	51
	.byte	49
	.byte	51
	.byte	50
	.byte	51
	.byte	51
	.byte	51
	.byte	52
	.byte	51
	.byte	53
	.byte	51
	.byte	54
	.byte	51
	.byte	55
	.byte	51
	.byte	56
	.byte	51
	.byte	57
	.byte	51
	.byte	97
	.byte	51
	.byte	98
	.byte	51
	.byte	99
	.byte	51
	.byte	100
	.byte	51
	.byte	101
	.byte	51
	.byte	102
	.byte	52
	.byte	48
	.byte	52
	.byte	49
	.byte	52
	.byte	50
	.byte	52
	.byte	51
	.byte	52
	.byte	52
	.byte	52
	.byte	53
	.byte	52
	.byte	54
	.byte	52
	.byte	55
	.byte	52
	.byte	56
	.byte	52
	.byte	57
	.byte	52
	.byte	97
	.byte	52
	.byte	98
	.byte	52
	.byte	99
	.byte	52
	.byte	100
	.byte	52
	.byte	101
	.byte	52
	.byte	102
	.byte	53
	.byte	48
	.byte	53
	.byte	49
	.byte	53
	.byte	50
	.byte	53
	.byte	51
	.byte	53
	.byte	52
	.byte	53
	.byte	53
	.byte	53
	.byte	54
	.byte	53
	.byte	55
	.byte	53
	.byte	56
	.byte	53
	.byte	57
	.byte	53
	.byte	97
	.byte	53
	.byte	98
	.byte	53
	.byte	99
	.byte	53
	.byte	100
	.byte	53
	.byte	101
	.byte	53
	.byte	102
	.byte	54
	.byte	48
	.byte	54
	.byte	49
	.byte	54
	.byte	50
	.byte	54
	.byte	51
	.byte	54
	.byte	52
	.byte	54
	.byte	53
	.byte	54
	.byte	54
	.byte	54
	.byte	55
	.byte	54
	.byte	56
	.byte	54
	.byte	57
	.byte	54
	.byte	97
	.byte	54
	.byte	98
	.byte	54
	.byte	99
	.byte	54
	.byte	100
	.byte	54
	.byte	101
	.byte	54
	.byte	102
	.byte	55
	.byte	48
	.byte	55
	.byte	49
	.byte	55
	.byte	50
	.byte	55
	.byte	51
	.byte	55
	.byte	52
	.byte	55
	.byte	53
	.byte	55
	.byte	54
	.byte	55
	.byte	55
	.byte	55
	.byte	56
	.byte	55
	.byte	57
	.byte	55
	.byte	97
	.byte	55
	.byte	98
	.byte	55
	.byte	99
	.byte	55
	.byte	100
	.byte	55
	.byte	101
	.byte	55
	.byte	102
	.byte	56
	.byte	48
	.byte	56
	.byte	49
	.byte	56
	.byte	50
	.byte	56
	.byte	51
	.byte	56
	.byte	52
	.byte	56
	.byte	53
	.byte	56
	.byte	54
	.byte	56
	.byte	55
	.byte	56
	.byte	56
	.byte	56
	.byte	57
	.byte	56
	.byte	97
	.byte	56
	.byte	98
	.byte	56
	.byte	99
	.byte	56
	.byte	100
	.byte	56
	.byte	101
	.byte	56
	.byte	102
	.byte	57
	.byte	48
	.byte	57
	.byte	49
	.byte	57
	.byte	50
	.byte	57
	.byte	51
	.byte	57
	.byte	52
	.byte	57
	.byte	53
	.byte	57
	.byte	54
	.byte	57
	.byte	55
	.byte	57
	.byte	56
	.byte	57
	.byte	57
	.byte	57
	.byte	97
	.byte	57
	.byte	98
	.byte	57
	.byte	99
	.byte	57
	.byte	100
	.byte	57
	.byte	101
	.byte	57
	.byte	102
	.byte	97
	.byte	48
	.byte	97
	.byte	49
	.byte	97
	.byte	50
	.byte	97
	.byte	51
	.byte	97
	.byte	52
	.byte	97
	.byte	53
	.byte	97
	.byte	54
	.byte	97
	.byte	55
	.byte	97
	.byte	56
	.byte	97
	.byte	57
	.byte	97
	.byte	97
	.byte	97
	.byte	98
	.byte	97
	.byte	99
	.byte	97
	.byte	100
	.byte	97
	.byte	101
	.byte	97
	.byte	102
	.byte	98
	.byte	48
	.byte	98
	.byte	49
	.byte	98
	.byte	50
	.byte	98
	.byte	51
	.byte	98
	.byte	52
	.byte	98
	.byte	53
	.byte	98
	.byte	54
	.byte	98
	.byte	55
	.byte	98
	.byte	56
	.byte	98
	.byte	57
	.byte	98
	.byte	97
	.byte	98
	.byte	98
	.byte	98
	.byte	99
	.byte	98
	.byte	100
	.byte	98
	.byte	101
	.byte	98
	.byte	102
	.byte	99
	.byte	48
	.byte	99
	.byte	49
	.byte	99
	.byte	50
	.byte	99
	.byte	51
	.byte	99
	.byte	52
	.byte	99
	.byte	53
	.byte	99
	.byte	54
	.byte	99
	.byte	55
	.byte	99
	.byte	56
	.byte	99
	.byte	57
	.byte	99
	.byte	97
	.byte	99
	.byte	98
	.byte	99
	.byte	99
	.byte	99
	.byte	100
	.byte	99
	.byte	101
	.byte	99
	.byte	102
	.byte	100
	.byte	48
	.byte	100
	.byte	49
	.byte	100
	.byte	50
	.byte	100
	.byte	51
	.byte	100
	.byte	52
	.byte	100
	.byte	53
	.byte	100
	.byte	54
	.byte	100
	.byte	55
	.byte	100
	.byte	56
	.byte	100
	.byte	57
	.byte	100
	.byte	97
	.byte	100
	.byte	98
	.byte	100
	.byte	99
	.byte	100
	.byte	100
	.byte	100
	.byte	101
	.byte	100
	.byte	102
	.byte	101
	.byte	48
	.byte	101
	.byte	49
	.byte	101
	.byte	50
	.byte	101
	.byte	51
	.byte	101
	.byte	52
	.byte	101
	.byte	53
	.byte	101
	.byte	54
	.byte	101
	.byte	55
	.byte	101
	.byte	56
	.byte	101
	.byte	57
	.byte	101
	.byte	97
	.byte	101
	.byte	98
	.byte	101
	.byte	99
	.byte	101
	.byte	100
	.byte	101
	.byte	101
	.byte	101
	.byte	102
	.byte	102
	.byte	48
	.byte	102
	.byte	49
	.byte	102
	.byte	50
	.byte	102
	.byte	51
	.byte	102
	.byte	52
	.byte	102
	.byte	53
	.byte	102
	.byte	54
	.byte	102
	.byte	55
	.byte	102
	.byte	56
	.byte	102
	.byte	57
	.byte	102
	.byte	97
	.byte	102
	.byte	98
	.byte	102
	.byte	99
	.byte	102
	.byte	100
	.byte	102
	.byte	101
	.byte	102
	.byte	102
	.ident	"GCC: (cqwrteur) 11.0.0 20200703 (experimental)"
	.section	.note.GNU-stack,"",@progbits
