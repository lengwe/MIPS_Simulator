#test addi with positive overflow,should return 246
lui $2,0xf000
lui $3,0x8000
addi $2,$3,1
jr   $0
