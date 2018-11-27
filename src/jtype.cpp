#include<iostream>
#include<stdint.h>
#include<stdlib.h>
#include "jtype.hpp"
#include "comop.hpp"
using namespace std;


void j_type(int32_t (&r)[32], uint32_t ins,uint32_t *ins_mem,uint8_t *data_mem,
            int32_t &hi,int32_t &lo,
            uint32_t &pc, uint32_t &count){

  jtype decode;
  decode.opcode = ins>>26;
  decode.target = ins<<6>>6;

  switch(decode.opcode){

    case 0b000010:{
    //J

        compare_op(r, ins_mem[count+1], ins_mem, data_mem, hi, lo, pc, count);

        uint32_t tmp_target = decode.target<<2;
        uint32_t tmp_pc = pc>>28<<28;
        pc=tmp_target+tmp_pc;

        if(pc>=0x10000000&&pc<=0x11000000){

          count =(pc-0x10000000)>>2;
        }
        else{
          exit(-11);
        }
    }
    break;

    case 0b000011:{
    //JAL
        r[31] = pc+8;
        compare_op(r, ins_mem[count+1], ins_mem, data_mem, hi, lo, pc, count);

        uint32_t tmp_target = decode.target<<2;
        uint32_t tmp_pc = pc>>28<<28;
        pc=tmp_target+tmp_pc;

        if(pc>=0x10000000&&pc<=0x11000000){

          count =(pc-0x10000000)>>2;
        }
        else{
           exit(-11);
        }
    }
    break;

    default:
    exit(-12);
  }
}
