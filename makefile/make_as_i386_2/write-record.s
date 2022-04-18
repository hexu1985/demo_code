.include	"linux.s"
.include	"record-def.s"

# PURPOSE: This function writes a record to
#          the given file descriptor
#
# INPUT: The file descriptor and a buffer
#
# OUTPUT: This function produces a status code
#
# STACK LOCAL VARIABLES
# first:  as --32 -o write-record.o write-record.s
# second: ld -melf_i386 -o write-record write-record.o

.equ	ST_WRITE_BUFFER,	8
.equ	ST_FILEDES,		12

.section .text

.globl write_record
.type write_record, @function


write_record:
		
		push	%ebp
		mov	%esp, %ebp
		
		push	%ebx
		mov	$SYS_WRITE, %eax
		mov	ST_FILEDES(%ebp), %ebx
		mov	ST_WRITE_BUFFER(%ebp), %ecx
		mov	$RECORD_SIZE, %edx
		int	$LINUX_SYSCALL

# NOTE - %eax has the return value, which we will
#        give back to our calling program

		pop	%ebx
		mov	%ebp, %esp
		pop	%ebp
		ret

