#include<iostream>
#include<stdint.h>
#include<stdlib.h>
#include "comop.hpp"
#include "rtype.hpp"
#include "jtype.hpp"
#include "itype.hpp"

using namespace std;

void compare_op(int32_t (&r)[32], uint32_t ins,uint32_t *ins_mem,uint8_t *data_mem,
                int32_t &hi,int32_t &lo, uint32_t &pc, uint32_t &count){

    if(ins==0){
      count++;
    }
    else{
      rtype decode;
      decode.opcode=ins>>26;

      if(decode.opcode==0){
        r_type(r, ins, ins_mem,data_mem, hi, lo, pc, count);
      }
      else {
        if(decode.opcode==2||decode.opcode==3){
          j_type(r, ins, ins_mem,data_mem, hi, lo, pc, count);
        }
        else{
          i_type(r, ins, ins_mem,data_mem, hi, lo, pc, count);
        }
      }

      if(count>(0x1000000)>>2){
        exit(-11);
      }

      if(r[0] != 0){
        exit(-21);
      }

    }

}
