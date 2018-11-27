#test bltzal,should return 48
addi $5,$0,55
addi $2,$0,5
bgezal $2,hi
subu $5,$5,$2
add $2,$0,$5
jr $0
hi:addi $2,$2,2
jr   $31
