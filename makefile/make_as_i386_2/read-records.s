.include "linux.s"
.include "record-def.s"

.section .data

file_name:	.ascii	"test.dat\0"

.section .bss

.lcomm	record_buffer,	RECORD_SIZE

.section .text

# Main program
.globl	_start

	_start:

# These are the locations on the stack where
# we will store the input and output descriptors
# (FYI - we could have used memory addresses in
# a .data section instead)

.equ	ST_INPUT_DESCRIPTOR,	-4
.equ	ST_OUTPUT_DESCRIPTOR,	-8

		mov	%esp, %ebp	# Copy the stack pointer to %ebp
		sub	$8, %esp	# Allocate space to hold the file descriptors

		# Open file

		mov	$SYS_OPEN, %eax
		mov	$file_name, %ebx
		mov	$0, %ecx	#This says to open read-only
		mov	$0666, %edx
		int	$LINUX_SYSCALL

		# Save file descriptor
		
		mov	%eax, ST_INPUT_DESCRIPTOR(%ebp)
		
		# Even though it’s a constant, we are
		# saving the output file descriptor in
		# a local variable so that if we later
		# decide that it isn’t always going to
		# be STDOUT, we can change it easily.

		movl	$STDOUT, ST_OUTPUT_DESCRIPTOR(%ebp)

	record_read_loop:

		push	ST_INPUT_DESCRIPTOR(%ebp)
		push	$record_buffer
		call	read_record
		add	$8, %esp

		# Returns the number of bytes read.
		# If it isn’t the same number we
		# requested, then it’s either an
		# end-of-file, or an error, so we’re
		# quitting

		cmp	$RECORD_SIZE, %eax
		jne	finished_reading
		
		# Otherwise, print out the first name
		# but first, we must know it’s size
		
		push	$RECORD_FIRSTNAME + record_buffer
		call	count_chars
		add	$4, %esp

		mov	%eax, %edx
		mov	ST_OUTPUT_DESCRIPTOR(%ebp), %ebx
		mov	$SYS_WRITE, %eax
		mov 	$RECORD_FIRSTNAME + record_buffer, %ecx
		int	$LINUX_SYSCALL
		
		push	ST_OUTPUT_DESCRIPTOR(%ebp)
		call	write_newline
		add	$4, %esp
		
		jmp	record_read_loop
		
	finished_reading:

		mov	$SYS_EXIT, %eax
		mov	$0, %ebx
		int	$LINUX_SYSCALL

