#ifndef rtype_H
#define rtype_H


struct rtype {
  uint6_t opcode, func;
  uint5_t rs,rt,rd,shamt;
};


void r_type(uint32_t reg);

#endif
