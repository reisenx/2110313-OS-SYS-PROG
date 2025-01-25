	.file	"act03_q02.c"
	.text
	.globl	compute_period
	.data
	.align 4
	.type	compute_period, @object
	.size	compute_period, 4
compute_period:
	.long	5
	.globl	sleep_period
	.align 4
	.type	sleep_period, @object
	.size	sleep_period, 4
sleep_period:
	.long	5
	.section	.rodata
.LC0:
	.string	"Sleep"
.LC1:
	.string	"Wake up"
	.text
	.globl	on_alarm
	.type	on_alarm, @function
on_alarm:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	sleep_period(%rip), %eax
	movl	%eax, %edi
	call	sleep@PLT
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	compute_period(%rip), %eax
	movl	%eax, %edi
	call	alarm@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	on_alarm, .-on_alarm
	.section	.rodata
.LC2:
	.string	"Enter compute period : "
.LC3:
	.string	"%d"
.LC4:
	.string	"Enter sleep period : "
.LC5:
	.string	"computing"
	.text
	.globl	main
	.type	main, @function
main:
.LFB7:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	compute_period(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	sleep_period(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	leaq	on_alarm(%rip), %rax
	movq	%rax, %rsi
	movl	$14, %edi
	call	signal@PLT
	movl	compute_period(%rip), %eax
	movl	%eax, %edi
	call	alarm@PLT
	movl	$0, -4(%rbp)
.L4:
	cmpl	$0, -4(%rbp)
	jne	.L3
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L3:
	addl	$1, -4(%rbp)
	jmp	.L4
	.cfi_endproc
.LFE7:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
