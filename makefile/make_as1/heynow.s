# Constants
	.equ SYS_OPEN, 5
	.equ SYS_WRITE, 4
	.equ SYS_READ, 3
	.equ SYS_CLOSE, 6
	.equ SYS_EXIT, 1

	.equ O_READONLY, 0
	.equ O_CREATE_WRITEONLY_TRUNC, 03101

	.equ STDIN, 0
	.equ STDOUT, 1
	.equ STDERR, 2

	.equ LINUX_SYSCALL, 0x80
	.equ END_OF_FILE, 0

.section .data
file_name:
	.ascii "heynow.txt\0"

text_to_write:
	.ascii "Hello, world!"
	.set text_size, .-text_to_write

.section .text
	.equ ST_RESERVE, 4
	.equ ST_FD_OUT, -4
.globl _start
_start:
	movl %esp, %ebp
	subl $ST_RESERVE, %esp

	open_fd_out:
		movl $SYS_OPEN, %eax
		movl $file_name, %ebx
		movl $O_CREATE_WRITEONLY_TRUNC, %ecx
		movl $0666, %edx
		int $LINUX_SYSCALL
	
	store_fd_out:
		movl %eax, ST_FD_OUT(%ebp)

	movl $text_size, %edx # buffer size
	movl $SYS_WRITE, %eax
	movl ST_FD_OUT(%ebp), %ebx
	movl $text_to_write, %ecx # buffer location
	int $LINUX_SYSCALL

	end_loop:
		movl $SYS_CLOSE, %eax
		movl ST_FD_OUT(%ebp), %ebx
		int $LINUX_SYSCALL

		movl $SYS_EXIT, %eax
		movl $0, %ebx
		int $LINUX_SYSCALL
