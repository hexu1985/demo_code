# first:  as --32 -o write-newline.o write-newline.s
# second: ld -melf_i386 -o write-newline write-newline.o

.include	"linux.s"

.globl	write_newline
.type	write_newline, @function

.section .data

newline:	.ascii	"\n"

.section .text

.equ	ST_FILEDES,	8

	write_newline:

		push	%ebp
		mov	%esp, %ebp

		mov	$SYS_WRITE, %eax
		mov	ST_FILEDES(%ebp), %ebx
		mov	$newline, %ecx
		mov	$1, %edx
		int	$LINUX_SYSCALL
		
		mov	%ebp, %esp
		pop	%ebp
		ret

