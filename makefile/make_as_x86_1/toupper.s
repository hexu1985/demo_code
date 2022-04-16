# Example shows a program which converts lower case symbols of the Input file into Upper case and stores result in Output file
.section .data
	error_message:
		.ascii "Error occuried during sys call\n"
		len = . - error_message

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

	.equ NUMBER_ARGUMENTS, 2

.section .bss
	.equ BUFFER_SIZE, 500
	.lcomm BUFFER_DATA, BUFFER_SIZE

.section .text
	.equ ST_SIZE_RESERVE, 8
	.equ ST_FD_IN, -4
	.equ ST_FD_OUT, -8
	.equ ST_ARGC, 0		# Number of arguments
	.equ ST_ARGV_0, 4	# Program name 
	.equ ST_ARGV_1, 8	# Input file name
	.equ ST_ARGV_2, 12	# Output file name

.globl _start
_start:
	movl %esp, %ebp
	subl $ST_SIZE_RESERVE, %esp

	open_files:
	open_fd_in:
		# Sys call
		movl $SYS_OPEN, %eax
		# File name
		movl ST_ARGV_1(%ebp), %ebx
		# Readonly
		movl $O_READONLY, %ecx
		movl $0666, %edx
		int $LINUX_SYSCALL
		cmpl $0, %eax
			jl print_error_code
	
	store_fd_in:
		movl %eax, ST_FD_IN(%ebp)

	open_fd_out:
		movl $SYS_OPEN, %eax
		movl ST_ARGV_2(%ebp), %ebx
		movl $O_CREATE_WRITEONLY_TRUNC, %ecx
		movl $0666, %edx
		int $LINUX_SYSCALL
		cmpl $0, %eax
			jl print_error_code

	store_fd_out:
		movl %eax, ST_FD_OUT(%ebp)

	read_loop_begin:
		# read block of the data
		movl $SYS_READ, %eax
		movl ST_FD_IN(%ebp), %ebx
		movl $BUFFER_DATA, %ecx
		movl $BUFFER_SIZE, %edx
		int $LINUX_SYSCALL
		cmpl $0, %eax
			jl print_error_code

		# exit if we reached the end
		cmpl $END_OF_FILE, %eax
			jle end_loop

	continue_read_loop:
		# convert to upper case
		pushl $BUFFER_DATA	# Buffer location
		pushl %eax			# Buffer size
		call convert_to_upper
		popl %eax
		addl $4, %esp		# Restore stack

		# write changes to output file
		movl %eax, %edx # buffer size
		movl $SYS_WRITE, %eax
		movl ST_FD_OUT(%ebp), %ebx
		movl $BUFFER_DATA, %ecx # buffer location
		int $LINUX_SYSCALL
		cmpl $0, %eax
			jl print_error_code

		jmp read_loop_begin

	end_loop:
		movl $SYS_CLOSE, %eax
		movl ST_FD_OUT(%ebp), %ebx
		int $LINUX_SYSCALL
		cmpl $0, %eax
			jl print_error_code

		movl $SYS_CLOSE, %eax
		movl ST_FD_IN(%ebp), %ebx
		int $LINUX_SYSCALL
		cmpl $0, %eax
			jl print_error_code


		movl $SYS_EXIT, %eax
		movl $0, %ebx
		int $LINUX_SYSCALL

	print_error_code:
		movl $len, %edx
		movl $SYS_WRITE, %eax
		movl $STDOUT, %ebx
		movl $error_message, %ecx
		int $LINUX_SYSCALL
		jmp end_loop

# The actual conversion happens here
.equ LOWER_CASE_A, 'a'
.equ LOWER_CASE_Z, 'z'
.equ UPPER_CONVERSION, 'A' -'a'
.equ ST_BUFFER_LEN, 8
.equ ST_BUFFER, 12
convert_to_upper:
	pushl %ebp
	movl %esp, %ebp
	movl ST_BUFFER(%ebp), %eax
	movl ST_BUFFER_LEN(%ebp), %ebx
	movl $0, %edi
	cmpl $0, %ebx
		je end_convert_loop
	
	convert_loop:
		# get current byte
		movb (%eax, %edi, 1), %cl
		cmpb $LOWER_CASE_A, %cl
			jl next_byte
		cmpb $LOWER_CASE_Z, %cl
			jg next_byte

		# convert to uppercase
		addb $UPPER_CONVERSION, %cl
		movb %cl, (%eax, %edi, 1)
		
	next_byte:
		incl %edi
		cmpl %edi, %ebx
			jne convert_loop
	
	end_convert_loop:
		movl %ebp, %esp
		popl %ebp
		ret
