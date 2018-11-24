#ifndef RTYPE_H
#define RTYPE_H



struct rtype {
  uint16_t opcode, func;
  uint16_t rs,rt,rd,shamt;
};


void r_type(int32_t (&r)[32], uint32_t ins,uint32_t *ins_mem,uint8_t *data_mem,
            int32_t &hi,int32_t &lo,
            uint32_t &pc, uint32_t &count);

#endif
