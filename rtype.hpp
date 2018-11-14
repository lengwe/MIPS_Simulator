#ifndef RTYPE_H
#define RTYPE_H



struct rtype {
  uint8_t opcode, func;
  uint8_t rs,rt,rd,shamt;
};


void r_type(uint32_t reg);

#endif
