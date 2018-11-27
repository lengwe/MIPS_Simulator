#test jal,should return 137
li $2,0x4567
jal hi
l1:jr $31
hi:bne $2,$0,else
j l1
else:
addi $2,$2,34
jr   $0
