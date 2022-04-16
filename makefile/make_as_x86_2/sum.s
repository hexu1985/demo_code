# Example shows simple functions summing up 2 numbers
.section .data
.section .text
.globl _start
_start:
	pushl $2
	pushl $5
	call sum

	movl %eax, %ebx

	movl $1, %eax
	int $0x80

.type sum, @function
sum:
	# store state before function call
	pushl %ebp
	movl %esp, %ebp

	# calculate sum
	movl 8(%ebp), %eax
	addl 12(%ebp), %eax
	
	# restore state
	movl %ebp, %esp
	popl %ebp
	ret
