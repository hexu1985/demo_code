.include "record-def.s"
.include "linux.s"

# PURPOSE: This function reads a record from the file
#          descriptor
#
# INPUT: The file descriptor and a buffer
#
# OUTPUT: This function writes the data to the buffer
#         and returns a status code.

# first:  as --32 -o read-record.o read-record.s
# second: ld -melf_i386 -o read-record read-record.o


# STACK LOCAL VARIABLES

.equ	ST_READ_BUFFER,	8
.equ	ST_FILEDES,	12

.section .text

.globl read_record

.type read_record, @function

	read_record:

		push	%ebp
		mov	%esp, %ebp
		push	%ebx

		mov	ST_FILEDES(%ebp), %ebx
		mov	ST_READ_BUFFER(%ebp), %ecx
		mov	$RECORD_SIZE, %edx
		mov	$SYS_READ, %eax
		int	$LINUX_SYSCALL

# NOTE - %eax has the return value, which we will
#        give back to our calling program

		pop	%ebx
		mov	%ebp, %esp
		pop	%ebp
		ret

