#test divu,should return 11
addiu $5,$0,55
addi $2,$0,5
divu $5,$2
mflo $2
jr   $0
