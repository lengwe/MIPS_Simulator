#ifndef JTYPE_H
#define JTYPE_H

struct jtype{
  uint6_t opcode;
  uint26_t target;
};

void j_type(uint32_t reg);
