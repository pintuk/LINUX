	.file	"memlayout.c"
.globl global_var2
	.data
	.align 4
	.type	global_var2, @object
	.size	global_var2, 4
global_var2:
	.long	5
	.align 4
	.type	global_static_2, @object
	.size	global_static_2, 4
global_static_2:
	.long	2
.globl const_global
	.section	.rodata
	.align 4
	.type	const_global, @object
	.size	const_global, 4
const_global:
	.long	100
	.data
	.align 4
	.type	local_static_var2.1787, @object
	.size	local_static_var2.1787, 4
local_static_var2.1787:
	.long	1
	.local	local_static_var1.1786
	.comm	local_static_var1.1786,4,4
	.section	.rodata
	.align 4
.LC0:
	.string	"*********************** Address Details ***********************"
	.align 4
.LC1:
	.string	"================================================================="
	.align 4
.LC2:
	.string	"Address of uninitialized_local                = %p\n"
	.align 4
.LC3:
	.string	"Address of initialized_local                  = %p\n"
	.align 4
.LC4:
	.string	"Address of reg_variable                       = %p\n"
	.align 4
.LC5:
	.string	"Address of uninitialized_global               = %p\n"
	.align 4
.LC6:
	.string	"Address of uninitialized_global_static        = %p\n"
	.align 4
.LC7:
	.string	"Address of uninitialized_local_static         = %p\n"
	.align 4
.LC8:
	.string	"Address of initialized_local_static           = %p\n"
	.align 4
.LC9:
	.string	"Address of initialized_global                 = %p\n"
	.align 4
.LC10:
	.string	"Address of initialized_global_static          = %p\n"
	.align 4
.LC11:
	.string	"Address of const_local                        = %p\n"
	.align 4
.LC12:
	.string	"Address of const_global                       = %p\n"
	.align 4
.LC13:
	.string	"Address of main()                             = %p\n"
	.text
.globl main
	.type	main, @function
main:
	leal	4(%esp), %ecx
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%ecx
	subl	$32, %esp
	movl	$1, -16(%ebp)
	movl	$10, -20(%ebp)
	movl	$1, %ebx
	movl	$.LC0, (%esp)
	call	puts
	movl	$.LC1, (%esp)
	call	puts
	leal	-12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$.LC2, (%esp)
	call	printf
	leal	-16(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$.LC3, (%esp)
	call	printf
	movl	%ebx, 4(%esp)
	movl	$.LC4, (%esp)
	call	printf
	movl	$global_var1, 4(%esp)
	movl	$.LC5, (%esp)
	call	printf
	movl	$global_static_1, 4(%esp)
	movl	$.LC6, (%esp)
	call	printf
	movl	$local_static_var1.1786, 4(%esp)
	movl	$.LC7, (%esp)
	call	printf
	movl	$local_static_var2.1787, 4(%esp)
	movl	$.LC8, (%esp)
	call	printf
	movl	$global_var2, 4(%esp)
	movl	$.LC9, (%esp)
	call	printf
	movl	$global_static_2, 4(%esp)
	movl	$.LC10, (%esp)
	call	printf
	leal	-20(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$.LC11, (%esp)
	call	printf
	movl	$const_global, 4(%esp)
	movl	$.LC12, (%esp)
	call	printf
	movl	$main, 4(%esp)
	movl	$.LC13, (%esp)
	call	printf
	addl	$32, %esp
	popl	%ecx
	popl	%ebx
	popl	%ebp
	leal	-4(%ecx), %esp
	ret
	.size	main, .-main
	.local	global_static_1
	.comm	global_static_1,4,4
	.comm	global_var1,4,4
	.ident	"GCC: (GNU) 4.1.0 20060304 (Red Hat 4.1.0-3)"
	.section	.note.GNU-stack,"",@progbits
