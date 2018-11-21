#ifndef RTYPE_H
#define RTYPE_H



struct rtype {
  uint8_t opcode, func;
  uint8_t rs,rt,rd,shamt;
};


void r_type(uint32_t r[], uint32_t ins,uint32_t *ins_mem,
            uint8_t *data_mem,uint64_t &hilo,unsigned int &hi,
            unsigned int &lo,uint32_t &pc, uint32_t &count);

#endif
