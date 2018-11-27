#test add with negative overflow,should return 246
li $3, 0x80000000
li $4, 0x80000000
add $2,$3,$4
jr   $0
