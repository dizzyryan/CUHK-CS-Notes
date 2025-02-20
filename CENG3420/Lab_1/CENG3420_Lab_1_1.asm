.globl _start

.data
	var1: .word 0
	var2: .word 0
	var3: .word 0
	line: .asciz "\n"

.text
_start:
	# load variables to address
	lw a1, var1
	lw a2, var2
	lw a3, var3
	
	# input from user, load to variables
	li a7, 5
	ecall
	mv a1, a0	# Load input to var1
	li a7, 5
	ecall
	mv a2, a0	# Load input to var2
	li a7, 5
	ecall
	mv a3, a0	# Load input to var3
	
	# increase var1 by 5 and print 
	addi a1, a1, 5
	mv a0, a1	# address of string to print
	li a7, 1	# system call code for PrintInt
	ecall
	la a0, line	# print new-line
	li a7, 4	# system call code for PrintString
	ecall
	
	# multiply var2 by 4 and print 
	slli a2, a2, 2
	mv a0, a2	# address of string to print
	li a7, 1	# system call code for PrintInt
	ecall
	la a0, line	# print new-line
	li a7, 4	# system call code for PrintString
	ecall
	
	# increase var3 by var1 + var2
	add a3, a3, a1
	add a3, a3, a2
	mv a0, a3	# address of string to print
	li a7, 1	# system call code for PrintInt
	ecall 
	la a0, line	# print new-line
	li a7, 4	# system call code for PrintString
	ecall
