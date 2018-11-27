#test slt,should return 1
addiu $3,$0,0xff
lui $4,5
slt $2,$3,$4
jr   $0
