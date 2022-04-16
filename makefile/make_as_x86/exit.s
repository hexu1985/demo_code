.section .data
.section .text
.globl _start
_start:
# Linux system call для выхода из программы
movl $1, %eax

# Возвращаемое программой значение
movl $0, %ebx

# Разбудить ядро, для исполнения нашего системного вызова
int $0x80
