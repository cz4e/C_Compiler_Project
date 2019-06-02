	.file	"testfile.cpp"
	.text
	.globl	main
	.type	main,@function
main:
	pushq   %rbp
	movq    %rsp,%rbp
	subq    $32,%rsp
	movq    %fs:40,%rax
	movq    %rax,-8(%rbp)
	xorl    %eax,%eax
	leaq	-32(%rbp),%rdx
	movl	$1,%ecx
	xorl	%eax,%eax
	movq	%rdx,%rdi
	rep stosq
	movb	$97,32(%rbp)
	movb	$98,31(%rbp)
	movb	$99,30(%rbp)
	movb	$101,29(%rbp)
	movb	$102,28(%rbp)
	movb	$103,27(%rbp)
	movb	$49,26(%rbp)
	movb	$50,25(%rbp)
	movb	$51,24(%rbp)
	movq    -8(%rbp),%rdx
	xorq    %fs:40,%rdx
	je      endofproc_main
	call    __stack_chk_fail@PLT
endofproc_main: 
	leave
	ret
	.size	main,.-main
	.section	.rodata
	.ident		"GNU C Like Simple C Compiler"
	.section	.note.GNU-stack,"",@progbits
