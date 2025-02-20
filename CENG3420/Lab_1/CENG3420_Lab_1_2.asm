.globl _start

.data
	array1: .word -3, 22, 32, 9, 5, 2, 11, 2, 1, 69
	space: .string " "
	line: .asciz "\n"

.text
_start:
	la a1, array1			# load array base address to a1
	li a2, 0			# load lo position of array1
	li a3, 9			# load hi position of array1
	lw t1, 12(a1)			# load fixed pivot to t1 = 9
	
	# swap pivot to hi
	lw t2, 12(a1)
	lw t3, 36(a1)
	sw t3, 12(a1)
	sw t2, 36(a1)
	
	li t2, -1			# variable i from lo-1, i = t2 = -1
	li t3, 0			# variable j from lo  , j = t3 = -1

partition:
	slli t4, t3, 2			# get offset relative to array
	add t4, t4, a1			# get address of next element of array
	lw t5, 0(t4)			# load element of array to t5, t5 = A[j]
	bgt t5, t1, continue		# check if need to be swapped
	swapLoop:
		addi t2, t2, 1		# move i to next block
		slli t6, t2, 2		# add offset
		add t6, t6, a1		# add offset form address
		lw t0, 0(t6)		# load from <9 part
		lw t5, 0(t4)		# load from current operating address
		sw t0, 0(t4)		# swap elements
		sw t5, 0(t6)		# swap elements
	continue:
		addi t3, t3, 1		# move j to next
		ble t3, a3, partition	# continue the loop
		
print:
	li t1, 0			# clear t1
	li t2, 9			# clear t2
	printLoop: 
		slli t3, t1, 2		# add offset
		add t3, t3, a1		# add offset form address
		lw a0, 0(t3)		# load from element to a0
		li a7, 1		# print value
		ecall
		la a0, space		# add space
		li a7, 4		# print space
		ecall
		addi t1, t1, 1		# next element
		ble t1, t2, printLoop	# continue printing
		
	la a0, line	# print new-line
	li a7, 4	# system call code for PrintString
	ecall
