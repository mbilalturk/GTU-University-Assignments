.data
	prompt: .asciiz "Enter a number: "
	isDivisible: .asciiz " is divisible by 9."
	notDivisible: .asciiz " is not divisible by 9"
	
.text
.globl main

main:	
	la $a0, prompt
	li $v0, 4
	syscall
	
	li $v0, 5
	syscall
	
	move $t0, $v0	# Store prompted number in $t0
	move $t3, $v0
	li $s0, 0 	# Store sum of digits
	li $t1, 10
	
	j process
	
process:
	beqz $t0, check 
	
	div $t0, $t1
	mfhi $t2	# Store digit
	add $s0, $s0, $t2	# Add digit to sum 
	
	div $t0, $t0, $t1
	
	j process
	
check:
	bltz $s0, print_not_divisible
	beqz $s0, print_divisible
	
	div $s0, $s0, 9		# Divide sum of the digits by 9
	j check

print_divisible:
	move $a0, $t3
	li $v0, 1
	syscall
	
	la $a0, isDivisible
	li $v0, 4
	syscall
	
	j exit

print_not_divisible:
	move $a0, $t3
	li $v0, 1
	syscall
	
	la $a0, notDivisible
	li $v0, 4
	syscall
	
	j exit
	
exit:
	li $v0, 10
	syscall
