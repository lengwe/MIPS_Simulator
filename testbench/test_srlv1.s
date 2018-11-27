#test srlv,should return 255
addiu $3,$0,0xff
lui $4,0x5cc5
srlv $2,$3,$4
jr   $0
