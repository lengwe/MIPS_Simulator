#ifndef JTYPE_H
#define JTYPE_H

struct jtype{
  uint16_t opcode;
  uint32_t target;
};

void j_type(uint32_t reg);

#endif
