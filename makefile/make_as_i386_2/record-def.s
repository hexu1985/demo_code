# first:  as --32 -o record-def.o record-def.s
# second: ld -melf_i386 -o record-def record-def.o

.equ	RECORD_FIRSTNAME,	0
.equ	RECORD_LASTNAME,	40
.equ	RECORD_ADDRESS,		80
.equ	RECORD_AGE,		320
.equ	RECORD_SIZE,		324

