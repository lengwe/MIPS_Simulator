#lhu2 should get 245, memory exception 

lui $6,0x2000
addiu $2,$2,0xFF
sb $2,3($6)
lh $2,3($6)
jr $zero