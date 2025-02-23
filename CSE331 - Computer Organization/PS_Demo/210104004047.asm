.data
array:  .word 1, 2, 3, 4, 5, 6, 7, 8, 9, 10    # Array of integers
size:   .word 10                          # Size of the array
	.text
	.globl main
    
main:
	la $t0, array
	lw $t1, size
	li $t2, 0
	li $s0, 0

loop:
	bgt $t2, $t1, print # Check if index is greater than size
	add $s0, $s0, $t0 # Add current element to s0
	addi $t0, $t0, 4($t0)# Increment address of array by 4 
	addi $t2, $t2, 1 # Increment index
	j loop
	
print: # Print result
	move $a0, $s0
	li $v0 1
	syscall
	j exit
	
exit: # Terminate the program
	li $v0 10
	syscall

