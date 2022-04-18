# PURPOSE: Count the characters until a null byte is reached.
#
# INPUT: The address of the character string
#
# OUTPUT: Returns the count in %eax
#
# PROCESS:
#   Registers used:
#     %ecx - character count
#     %al - current character
#     %edx - current character address

.type count_chars, @function

.globl count_chars


.equ	ST_STRING_START_ADDRESS,	8

count_chars:
	
		push	%ebp
		mov	%esp, %ebp
		
		# Counter starts at zero
		mov	$0, %ecx
		mov	ST_STRING_START_ADDRESS(%ebp), %edx

	count_loop_begin:

		movb	(%edx), %al	# Grab the current character
		cmp	$0, %al		# Is it null?
		je	count_loop_end	# If yes, we’re done
		inc	%ecx		# Otherwise, increment the counter and the pointer
		inc	%edx
		jmp	count_loop_begin	# Go back to the beginning of the loop

	count_loop_end:

		mov	%ecx, %eax	# We’re done. Move the count into %eax
					# and return.

                mov     %ebp, %esp	# this line are absent in book, because of error
                pop     %ebp

		ret

