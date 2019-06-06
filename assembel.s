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
	movw	$10,-32(%rbp)
	movswl	-32(%rbp),%eax
	cvtsi2sd	%eax,%xmm0
	movsd	floatnumber_0(%rip),%xmm1
	mulsd	%xmm1,%xmm0
	cvttsd2si	%xmm0,%eax
	movw	%ax,-32(%rbp)
	movss	floatnumber_1(%rip),%xmm0
	movss	%xmm0,-30(%rbp)
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
	.double	10.5
floatnumber_1:
	.float	12.3
	.ident		"GNU C Like Simple C Compiler"
	.section	.note.GNU-stack,"",@progbits
