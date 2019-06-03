	.file	"testfile.cpp"
	.text
	.globl	c
	.data
	.align	8
	.type	c,@object
	.size	c,8
c:
	.double	11.3
	.text
	.globl	main
	.type	main,@function
main:
	pushq   %rbp
	movq    %rsp,%rbp
	subq    $48,%rsp
	movq    %fs:40,%rax
	movq    %rax,-8(%rbp)
	xorl    %eax,%eax
	movq	$11,-48(%rbp)
	movq	$12,-40(%rbp)
	movsd	floatnumber_0(%rip),%xmm0
	movsd	%xmm0,-32(%rbp)
	movq	$100,-24(%rbp)
	movsd	c(%rip),%xmm0
	movsd	%xmm0,-32(%rbp)
	movq    -8(%rbp),%rdx
	xorq    %fs:40,%rdx
	je      endofproc_main
	call    __stack_chk_fail@PLT
endofproc_main: 
	leave
	ret
	.size	main,.-main
	.section	.rodata
floatnumber_0:
	.double	11.1
	.ident		"GNU C Like Simple C Compiler"
	.section	.note.GNU-stack,"",@progbits
