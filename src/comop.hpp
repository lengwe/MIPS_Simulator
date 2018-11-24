#ifndef COMOP_H
#define COMOP_H

void compare_op(int32_t (&r)[32], uint32_t ins,uint32_t *ins_mem,uint8_t *data_mem,
                int32_t &hi,int32_t &lo,uint32_t &pc, uint32_t &count);

#endif
