#ifndef RTYPE_H
#define RTYPE_H


typedef unsigned int uint6_t[6];
typedef unsigned int uint5_t[5];

struct rtype {
  uint6_t opcode, func;
  uint5_t rs,rt,rd,shamt;
};


void r_type(uint32_t reg);

#endif
