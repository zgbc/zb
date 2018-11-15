	.file	"main.c"
	.section	.rodata
.LC0:
	.string	"int is %d,%d,%d,%d\n"
.LC1:
	.string	"long is %d\n"
.LC2:
	.string	"long long is %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$96, %rsp
	movl	%edi, -84(%rbp)
	movq	%rsi, -96(%rbp)
	movl	$3001, -4(%rbp)
	movl	$1000, -8(%rbp)
	movl	-8(%rbp), %eax
	movl	-4(%rbp), %edx
	addl	%edx, %eax
	movl	%eax, -12(%rbp)
	movl	-8(%rbp), %eax
	movl	-4(%rbp), %edx
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -16(%rbp)
	movl	-4(%rbp), %eax
	imull	-8(%rbp), %eax
	movl	%eax, -20(%rbp)
	movl	-4(%rbp), %eax
	cltd
	idivl	-8(%rbp)
	movl	%eax, -24(%rbp)
	movl	-24(%rbp), %esi
	movl	-20(%rbp), %ecx
	movl	-16(%rbp), %edx
	movl	-12(%rbp), %eax
	movl	%esi, %r8d
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movq	$4001, -32(%rbp)
	movq	$2000, -40(%rbp)
	movq	-40(%rbp), %rax
	movq	-32(%rbp), %rdx
	addq	%rdx, %rax
	movq	%rax, -48(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movq	$6001, -56(%rbp)
	movq	$5000, -64(%rbp)
	movq	-64(%rbp), %rax
	movq	-56(%rbp), %rdx
	addq	%rdx, %rax
	movq	%rax, -72(%rbp)
	movq	-72(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-28)"
	.section	.note.GNU-stack,"",@progbits
