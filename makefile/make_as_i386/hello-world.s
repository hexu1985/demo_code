.section .data
message:
	.ascii "Hello, world!\n"
	len = . - message
.section .text
.globl _start
_start:
# Длина сообщения
	movl $len, %edx
# Сообщение
	movl $message, %ecx
# Куда писать - stdout
	movl $1, %ebx
# Системный вызов - sys_write
	movl $4, %eax
# Будем ядро
	int $0x80

# Выход из программы
	movl $1, %eax
	movl $0, %ebx
	int $0x80
