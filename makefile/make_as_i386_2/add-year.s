.include "linux.s"
.include "record-def.s"

.section .data

input_file_name:	.ascii "test.dat\0"
output_file_name:	.ascii "testout.dat\0"

.section .bss

.lcomm	record_buffer,	RECORD_SIZE

# Stack offsets of local variables

.equ	ST_INPUT_DESCRIPTOR,	-4
.equ	ST_OUTPUT_DESCRIPTOR,	-8

.section .text

.globl	_start
	_start:
		
		mov	%esp, %ebp	# Copy stack pointer and make room for local variables
		sub	$8, %esp
		
		# Open file for reading

		mov	$SYS_OPEN, %eax
		mov	$input_file_name, %ebx
		mov	$0, %ecx
		mov	$0666, %edx
		int	$LINUX_SYSCALL

		mov	%eax, ST_INPUT_DESCRIPTOR(%ebp)
		
		# Open file for writning

		mov	$SYS_OPEN, %eax
		mov	$output_file_name, %ebx
		mov	$0101, %ecx
		mov	$0666, %edx
		int	$LINUX_SYSCALL

		mov	%eax, ST_OUTPUT_DESCRIPTOR(%ebp)

	loop_begin:

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
		jne	loop_end

		# Increment the age

		incl	record_buffer + RECORD_AGE

		# Write the record out

		push	ST_OUTPUT_DESCRIPTOR(%ebp)
		push	$record_buffer
		call	write_record
		add	$8, %esp
		
		jmp	loop_begin

	loop_end:

		mov	$SYS_EXIT, %eax
		mov	$0, %ebx
		int	$LINUX_SYSCALL

