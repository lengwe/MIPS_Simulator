#include<iostream>
#include "comop.hpp"
#include "rtype.hpp"
#include "jtype.hpp"
#include "itype.hpp"

using namespace std;

void compare_op(uint32_t r[32], uint32_t ins,uint32_t *ins_mem, uint8_t *data_mem,
                uint64_t &hilo,unsigned int &hi,unsigned int &lo,
                uint32_t &pc, uint32_t &count){

  if(ins==0){
    return;
  }
  else{
    rtype decode;
    decode.opcode=ins>>26;

    if(decode.opcode==0){
      r_type(r[32], ins, ins_mem,data_mem, hilo, hi, lo, pc, count);
    }
    else {
      if(decode.opcode==2||decode.opcode=3){
        j_type(r[32], ins, ins_mem,data_mem, hilo, hi, lo, pc, count);
      }
      else{
        i_type(r[32], ins, ins_mem,data_mem, hilo, hi, lo, pc, count);
      //reset
      }
    }

    if(count<0||count>(0x1000000)>>2){
          exit(-11);
    }

    if(r[0] != 0){
      exit(-21);
    }

    //compare_op(ins_mem[count]);
  }

}
