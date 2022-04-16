.include	"linux.s"
.include	"record-def.s"

.section .data

# Constant data of the records we want to write
# Each text data item is padded to the proper
# length with null (i.e. 0) bytes.
# .rept is used to pad each item. .rept tells
# the assembler to repeat the section between
# .rept and .endr the number of times specified.
# This is used in this program to add extra null
# characters at the end of each field to fill
# it up

# first:  as --32 -o write-records.o write-records.s
# second: ld -melf_i386 -o write-records write-records.o


record1:

	.ascii	"Fredrick\0"
	.rept	31		# Padding to 40 bytes
	.byte	0
	.endr

	.ascii	"Bartlett\0"
	.rept	31		# Padding to 40 bytes
	.byte	0
	.endr

	.ascii	"4242 S Prairie\nTulsa, OK 55555\0"
	.rept	209		# Padding to 240 bytes
	.byte	0
	.endr
	.long	45


record2:

	.ascii	"Marilyn\0"
	.rept	32		# Padding to 40 bytes
	.byte	0
	.endr

	.ascii	"Taylor\0"
	.rept	33		# Padding to 40 bytes
	.byte	0
	.endr

	.ascii	"2224 S Johannan St\nChicago, IL 12345\0"
	.rept	203		# Padding to 240 bytes
	.byte	0
	.endr
	.long	29


record3:

	.ascii	"Derrick\0"
	.rept	32		# Padding to 40 bytes
	.byte	0
	.endr

	.ascii	"McIntire\0"
	.rept	31 		# Padding to 40 bytes
	.byte	0
	.endr

	.ascii	"500 W Oakland\nSan Diego, CA 54321\0"
	.rept	206		# Padding to 240 bytes
	.byte	0
	.endr
	.long	36

file_name:	.ascii	"test.dat\0"	#This is the name of the file we will write to

	.equ	ST_FILE_DESCRIPTOR,	-4

.globl _start
	
	_start:

		mov	%esp, %ebp	# Copy the stack pointer to %ebp
		sub	$4, %esp	# Allocate space to hold the file descriptor

		mov	$SYS_OPEN, %eax	# open the file
		mov	$file_name, %ebx	
		mov	$0101, %ecx	# This says to create if it
					# doesn’t exist, and open for
					# writing
		mov	$0666, %edx
		int	$LINUX_SYSCALL

		mov	%eax, ST_FILE_DESCRIPTOR(%ebp)	# Store the file descriptor away

		# Write the first record
		push	ST_FILE_DESCRIPTOR(%ebp)
		push	$record1
		call	write_record
		add	$8, %esp
		
		# Write the second record
		push    ST_FILE_DESCRIPTOR(%ebp)
                push    $record2
                call    write_record
                add     $8, %esp

                # Write the third record
                push    ST_FILE_DESCRIPTOR(%ebp)
                push    $record3
                call    write_record
                add     $8, %esp

		# Close the file descriptor
		mov	$SYS_CLOSE, %eax
		mov	ST_FILE_DESCRIPTOR(%ebp), %ebx
		int	$LINUX_SYSCALL

		# Exit the program
		mov	$SYS_EXIT, %eax
		mov	$0x00, %ebx
		int     $LINUX_SYSCALL
