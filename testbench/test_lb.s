#LB should return 255 

li $3, 0x2000
sll $3,$3,16
addi $4,$0,0xFF
sb $4,3($3)
lb $2,3($3)
jr $zero
