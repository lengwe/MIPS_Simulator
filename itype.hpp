#ifndef ITYPE_H
#define ITYPE_H


typedef unsigned int uint6_t[6];
typedef unsigned int uint5_t[5];

struct itype{
  uint6_t opcode;
  uint5_t rs,rt;
  uint16_t ai;
  int16_t sai;
};

void i_type(uint32_t reg);

#endif
