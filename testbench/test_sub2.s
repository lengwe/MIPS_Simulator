#test sub overflow,should return 246
li $3,0x80000000
addi $4,$0,1
sub $2,$3,$4
jr   $0
