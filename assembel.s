	.file	"testfile.cpp"
	.text
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
	movb	$97,-32(%rbp)
	movb	$98,-31(%rbp)
	movzbl	-32(%rbp),%edx
	movl	%edx,%eax
	sall	$2,%eax
	imull	$25,%eax
	movb	%al,-32(%rbp)
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
