	.file	"memLeakTest.c"
	.section	.rodata
.LC0:
	.string	"function1() - is called !"
	.text
.globl function1
	.type	function1, @function
function1:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	$.LC0, (%esp)
	call	puts
	leave
	ret
	.size	function1, .-function1
	.section	.rodata
.LC1:
	.string	"Entering - main() -"
.LC2:
	.string	"Address of function1 - %u\n"
	.text
.globl main
	.type	main, @function
main:
	leal	4(%esp), %ecx
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ecx
	subl	$36, %esp
	movl	$.LC1, (%esp)
	call	puts
	movl	$function1, -8(%ebp)
	movl	-8(%ebp), %eax
	call	*%eax
	movl	-8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$.LC2, (%esp)
	call	printf
	addl	$36, %esp
	popl	%ecx
	popl	%ebp
	leal	-4(%ecx), %esp
	ret
	.size	main, .-main
	.ident	"GCC: (GNU) 4.1.0 20060304 (Red Hat 4.1.0-3)"
	.section	.note.GNU-stack,"",@progbits
