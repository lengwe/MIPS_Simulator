#test sllv,should return 0
addiu $3,$0,0xff
lui $4,0x5cc5
sllv $2,$4,$3
jr   $0
