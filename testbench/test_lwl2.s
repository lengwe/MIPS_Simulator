#lwl should return 245,memory exception

lui $4, 0x1000
addi $2,$2,5112
sw $2,($4)
lwl $2,1($4)
jr $zero 