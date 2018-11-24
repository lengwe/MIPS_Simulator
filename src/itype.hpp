#ifndef ITYPE_H
#define ITYPE_H


struct itype{
  uint16_t opcode;
  uint16_t rs,rt;
  uint16_t ai;
  int16_t sai;
};

void i_type(int32_t (&r)[32], uint32_t ins,uint32_t *ins_mem,uint8_t *data_mem,
            int32_t &hi,int32_t &lo,
            uint32_t &pc, uint32_t &count);

int32_t addr_getc();
void addr_putc(uint8_t *data_mem, uint32_t addr);

#endif
