#ifndef ITYPE_H
#define ITYPE_H


struct itype{
  uint8_t opcode;
  uint8_t rs,rt;
  uint16_t ai;
  int16_t sai;
};

void i_type(uint32_t r[32], uint32_t ins,uint32_t *ins_mem, uint8_t *data_mem,
                uint64_t &hilo,unsigned int &hi,unsigned int &lo,
                uint32_t &pc, uint32_t &count);

int32_t addr_getc();
void addr_putc(uint8_t *data_mem, uint32_t addr);

#endif
