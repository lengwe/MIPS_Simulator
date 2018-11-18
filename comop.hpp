#ifndef COMOP_H
#define COMOP_H

void compare_op(uint32_t r[32], uint32_t ins,uint32_t *ins_mem, uint8_t *data_mem,
                uint64_t &hilo,unsigned int &hi,unsigned int &lo,
                uint32_t &pc, uint32_t &count);

#endif
