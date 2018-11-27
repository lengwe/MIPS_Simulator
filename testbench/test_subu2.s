#test subu,should return 255
li $3,0x80000000
addi $4,$0,1
subu $2,$3,$4
jr   $0
