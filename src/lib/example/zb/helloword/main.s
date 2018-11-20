	.section .rodata
C0:
	.ascii "HelloWorld"
	C0_length = . - C0
	.section .text
	.global _start
_start:
	movq $1, %rax
	movq $1, %rdi

	lea C0(%rip), %rsi

	movq $C0_length, %rdx

	syscall
	movq $60, %rax
	xor %rdi, %rdi
	syscall
