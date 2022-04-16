# Example shows how to work with functions in assembler
# Implements programm which calculates 2^3 + 5^2
.section .data
.section .text
.globl _start
_start:
# pushl power and base for 2^3
	pushl $4
	pushl $2
	call power
# Move stack pointer back
	addl $8, %esp

# Save calculated value
	pushl %eax

# pushl power and base for 5^2
	pushl $0
	pushl $5
	call power
# Move stack pointer back
	addl $8, %esp
# Save first power (2^3) in the %ebx
	popl %ebx

# Calculate sum and save in %ebx
	addl %eax, %ebx

	movl $1, %eax
	int $0x80


# %ebx - base number
# %ecx - power
# -4(%ebp) - current result
.type power, @function
power:
	cmpl $0, 8(%esp)
		je zero_power
# Save old base pointer
	pushl %ebp
# Save old stack pointer
	movl %esp, %ebp
# Reserve space to our calculations
	subl $4, %esp

	movl 8(%ebp), %ebx # Base
	movl 12(%ebp), %ecx # Power

	movl %ebx, -4(%ebp) # Current result

	power_loop_start:
		# exit loop if power is 1
		cmpl $1, %ecx
			je end_power
		# move current value into %eax
		movl -4(%ebp), %eax
		# multiply resul by base
		imull %ebx, %eax
		# update current value
		movl %eax, -4(%ebp)
		# decrease power
		decl %ecx
		jmp power_loop_start
	
	end_power:
		# store result in %eax
		movl -4(%ebp), %eax
		# restore stack to the state before function call
		movl %ebp, %esp
		popl %ebp
		ret

	zero_power:
		movl $1, %eax
		ret

