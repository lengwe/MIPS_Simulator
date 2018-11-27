#test sltiu,should return 1
addiu $4,$0,0xf
sltiu $2,$4,0x1111
jr   $0
