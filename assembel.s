	.file	"testfile.cpp"
	.text
	.section	.rodata
.LC0:
	.string 	"Hello"
.LC1:
	.string 	"USTC"
.LC2:
	.string 	"MAX2"
.LC3:
	.string 	"MAX"
.LC4:
	.string 	"MMA"
	.text
	.globl	main
	.type	main,@function
main:
	pushq   %rbp
	movq    %rsp,%rbp
	subq    $208,%rsp
	movq    %fs:40,%rax
	movq    %rax,-8(%rbp)
	xorl    %eax,%eax
	leaq	-208(%rbp),%rdx
	movl	$10,%ecx
	xorq	%rax,%rax
	movq	%rdx,%rdi
	rep stosq
	leaq	.LC0(%rip),%rax
	movq	%rax,-208(%rbp)
	leaq	.LC1(%rip),%rax
	movq	%rax,-200(%rbp)
	leaq	-128(%rbp),%rdx
	movl	$10,%ecx
	xorq	%rax,%rax
	movq	%rdx,%rdi
	rep stosq
	movq	$10,-128(%rbp)
	movq	$10,-120(%rbp)
	leaq	.LC2(%rip),%rax
	movq	%rax,-48(%rbp)
	leaq	.LC3(%rip),%rax
	movq	%rax,-32(%rbp)
	leaq	.LC4(%rip),%rax
	movq	%rax,-24(%rbp)
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
