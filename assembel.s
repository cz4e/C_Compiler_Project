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
	.section	.rodata
.LC0:
	.string 	"Hello"
.LC1:
	.string 	"USTC"
	.text
	.globl	main
	.type	main,@function
main:
	pushq   %rbp
	movq    %rsp,%rbp
	subq    $352,%rsp
	movq    %fs:40,%rax
	movq    %rax,-8(%rbp)
	xorl    %eax,%eax
	movq	$11,-352(%rbp)
	movq	$12,-344(%rbp)
	movsd	floatnumber_0(%rip),%xmm0
	movsd	%xmm0,-336(%rbp)
	movq	$100,-328(%rbp)
	movsd	c(%rip),%xmm0
	movsd	%xmm0,-336(%rbp)
	movss	floatnumber_1(%rip),%xmm0
	movss	%xmm0,-320(%rbp)
	movss	floatnumber_2(%rip),%xmm0
	movss	%xmm0,-316(%rbp)
	movss	floatnumber_3(%rip),%xmm0
	movss	%xmm0,-312(%rbp)
	movq	$11,-280(%rbp)
	movsd	floatnumber_4(%rip),%xmm0
	movsd	%xmm0,-272(%rbp)
	movsd	floatnumber_5(%rip),%xmm0
	movsd	%xmm0,-264(%rbp)
	leaq	-176(%rbp),%rdx
	movl	$10,%ecx
	xorq	%rax,%rax
	movq	%rdx,%rdi
	rep stosq
	leaq	.LC0(%rip),%rax
	movq	%rax,-176(%rbp)
	leaq	.LC1(%rip),%rax
	movq	%rax,-168(%rbp)
	leaq	-96(%rbp),%rdx
	movl	$10,%ecx
	xorq	%rax,%rax
	movq	%rdx,%rdi
	rep stosq
	movq	$10,-96(%rbp)
	movq	$10,-88(%rbp)
	movq    -8(%rbp),%rdx
	xorq    %fs:40,%rdx
	je      endofproc_main
	call    __stack_chk_fail@PLT
endofproc_main: 
	leave
	ret
	.size	main,.-main
	.section	.rodata
floatnumber_1:
	.float	1.1
floatnumber_2:
	.float	2.2
floatnumber_3:
	.float	3.3
floatnumber_4:
	.double	3.4
floatnumber_5:
	.double	4.5
floatnumber_0:
	.double	11.1
	.ident		"GNU C Like Simple C Compiler"
	.section	.note.GNU-stack,"",@progbits
