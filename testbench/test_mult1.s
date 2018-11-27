#test mult,should return 36
addiu $5,$0,6
mult $5,$5
mfhi $6
mflo $2
jr   $0
