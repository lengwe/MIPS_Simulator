#test lw,should return 205
lui $3,0x2000
addi $4,$0,0xabcd
sw $4,0($3)
lw $2,0($3)
jr   $0
