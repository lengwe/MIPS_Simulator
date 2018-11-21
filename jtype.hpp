#ifndef JTYPE_H
#define JTYPE_H

struct jtype{
  uint16_t opcode;
  uint32_t target;
};

void j_type(uint32_t r[], uint32_t ins,uint32_t *ins_mem,
            uint8_t *data_mem,uint64_t &hilo,unsigned int &hi,
            unsigned int &lo,uint32_t &pc, uint32_t &count);

#endif
