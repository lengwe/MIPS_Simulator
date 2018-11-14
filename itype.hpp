#ifndef ITYPE_H
#define ITYPE_H


struct itype{
  uint8_t opcode;
  uint8_t rs,rt;
  uint16_t ai;
  int16_t sai;
};

void i_type(uint32_t reg);

#endif
