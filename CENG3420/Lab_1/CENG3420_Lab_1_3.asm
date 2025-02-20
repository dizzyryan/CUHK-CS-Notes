.globl _start

.data
	array1: .word -5, 24, -8, 45, -15, 24, 11, 7, 0, 125
	space: .string " "
	line: .asciz "\n"

.text
_start:
	la a1, array1			# load array base address
	li a2, 0			# load a2 = lo
	li a3, 9			# load a3 = hi
	
	jal ra, sort			# jump to sorting, ra <- next line (print)
	j print				# print the sequence, end of program

sort:					# sorting start
	addi sp, sp, -16		# create stack
	sw ra, 0(sp)			# save ra <- next line (print)
	sw a2, 4(sp)			# save lo = 0
	sw a3, 8(sp)			# save hi = 9
	sw t1, 12(sp)			# save t1 <- pivot

	bge a2, a3, sort_end		# if lo >= hi, finish looping
		jal ra, partition	# do partition, ra -> next line
		addi a3, t2, -1		# move hi to left
		jal ra, sort		# do left sorting, ra -> next line
		addi a2, t2, 1		# move lo to right
		lw a3, 8(sp)		# get hi = 9 back
		jal ra, sort		# do right sorting, ra -> sort_end

sort_end:				# finish sorting
	lw ra, 0(sp)			# load ra = print
	lw a2, 4(sp)			# load lo = 0
	lw a3, 8(sp)			# load hi = 9
	lw t1, 12(sp)			# load pivot
	addi sp, sp, 16			# free stack
	jr ra				# jump to print elements

partition:				# function to partition the list
	addi sp, sp, -4			# add stack
	sw ra, 0(sp)			# store ra = Line 28
	
	slli t1, a3, 2			# offset for hi
	add t1, a1, t1			# form address of element
	lw t1, 0(t1)			# load element to t1 -> pivot (hi element)
	addi t2, a2, -1			# variable i from lo-1, i = -1
	mv t3, a2			# variable j from lo  , j = 0
	addi a4, a3, -1			# end loop indicator
	
	outer_loop:			# loop from j = 0 -> 9
	bgt t3, a4, outer_loop_end	# if j > 8 -> end of loop
		slli t4, t3, 2		# offset for address
		add t4, t4, a1		# form address for array
		lw t5, 0(t4)		# load element of array to t5, t5 = A[t3]
		
		bgt t5, t1, continue		# check if need to be swapped
		swapLoop:
			addi t2, t2, 1		# move i to next block
			slli t6, t2, 2		# add offset
			add t6, t6, a1		# add offset form address
			lw t0, 0(t6)		# load from a[i]
			sw t0, 0(t4)		# swap elements
			sw t5, 0(t6)		# swap elements
		continue:
			addi t3, t3, 1		# move j to next
			j outer_loop		# continue the loop
			
	outer_loop_end:
		addi t2, t2, 1			# move i to next block
		slli t6, t2, 2			# add offset
		add t6, t6, a1			# add offset form address
		lw t0, 0(t6)			# load from a[i]
		
		slli t4, t3, 2			# get offset relative to array
		add t4, t4, a1			# get address of next element of array
		lw t5, 0(t4)			# load element of array to t5, t5 = A[j]
		
		sw t0, 0(t4)			# swap elements
		sw t5, 0(t6)			# swap elements
		
		lw ra, 0(sp)			# get ra back
		addi sp, sp, 4			# free stack
		jr ra
	
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
