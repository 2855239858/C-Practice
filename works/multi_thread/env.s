	.file	"env.cpp"
	.text
	.globl	_Z7get_envPKc
	.type	_Z7get_envPKc, @function
_Z7get_envPKc:
.LFB604:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	getenv
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE604:
	.size	_Z7get_envPKc, .-_Z7get_envPKc
	.globl	_Z7set_envPKcS0_i
	.type	_Z7set_envPKcS0_i, @function
_Z7set_envPKcS0_i:
.LFB605:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movl	%edx, -20(%rbp)
	movl	-20(%rbp), %edx
	movq	-16(%rbp), %rcx
	movq	-8(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	setenv
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE605:
	.size	_Z7set_envPKcS0_i, .-_Z7set_envPKcS0_i
	.globl	_Z9unset_envPKcS0_i
	.type	_Z9unset_envPKcS0_i, @function
_Z9unset_envPKcS0_i:
.LFB606:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movl	%edx, -20(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	unsetenv
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE606:
	.size	_Z9unset_envPKcS0_i, .-_Z9unset_envPKcS0_i
	.globl	_Z19create_child_threadv
	.type	_Z19create_child_threadv, @function
_Z19create_child_threadv:
.LFB607:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	call	fork
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE607:
	.size	_Z19create_child_threadv, .-_Z19create_child_threadv
	.section	.rodata
	.align 8
.LC0:
	.string	"This process's pid is %d, father's pid is %d \n"
	.text
	.globl	_Z9print_pidv
	.type	_Z9print_pidv, @function
_Z9print_pidv:
.LFB608:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$8, %rsp
	.cfi_offset 3, -24
	call	getppid
	movl	%eax, %ebx
	call	getpid
	movl	%ebx, %edx
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	nop
	addq	$8, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE608:
	.size	_Z9print_pidv, .-_Z9print_pidv
	.section	.rodata
.LC1:
	.string	"User id is %d\n"
.LC2:
	.string	"Effective user id is %d\n"
	.text
	.globl	_Z17print_u_and_eu_idv
	.type	_Z17print_u_and_eu_idv, @function
_Z17print_u_and_eu_idv:
.LFB609:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	call	getuid
	movl	%eax, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	call	geteuid
	movl	%eax, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE609:
	.size	_Z17print_u_and_eu_idv, .-_Z17print_u_and_eu_idv
	.section	.rodata
.LC3:
	.string	"Group id is %d\n"
.LC4:
	.string	"Effective group id is %d\n"
	.text
	.globl	_Z17print_u_and_eg_idv
	.type	_Z17print_u_and_eg_idv, @function
_Z17print_u_and_eg_idv:
.LFB610:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	call	getgid
	movl	%eax, %esi
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
	call	getegid
	movl	%eax, %esi
	movl	$.LC4, %edi
	movl	$0, %eax
	call	printf
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE610:
	.size	_Z17print_u_and_eg_idv, .-_Z17print_u_and_eg_idv
	.section	.rodata
.LC5:
	.string	"HOME"
.LC6:
	.string	"Env is [%s]\n"
.LC7:
	.string	"Thread begin."
	.text
	.globl	main
	.type	main, @function
main:
.LFB611:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$.LC5, %edi
	call	_Z7get_envPKc
	movq	%rax, %rsi
	movl	$.LC6, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC7, %edi
	call	puts
	call	_Z19create_child_threadv
	call	_Z9print_pidv
	call	_Z17print_u_and_eu_idv
	call	_Z17print_u_and_eg_idv
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE611:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.12) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
