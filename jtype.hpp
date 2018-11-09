#ifndef JTYPE_H
#define JTYPE_H

typedef unsigned int uint6_t[6];
typedef unsigned int uint26_t[26];

struct jtype{
  uint6_t opcode;
  uint26_t target;
};

void j_type(uint32_t reg);

#endif
