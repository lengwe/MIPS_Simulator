#include<iostream>
#include "jtype.hpp"
using namespace std;


void j_type(uint32_t reg){
  jtype decode;
  decode.opcode = reg>>26；
  decode.target = reg<<6>>6;

  switch(decode.opcode){

    case 0b000010:
    //J
    if (ins_mem[count+1]==0){
      uint32_t tmp_target = decode.target<<2;
      uint32_t tmp_c = count>>28<<28;
      count = tmp_target+tmp_c;
      if(0<=count<=0x1000000){
      pc =&ins_mem[count];
    }
      else{
        exit(-11);
      }
    }

    else{
      compare_op(ins_mem[count+1]);
      uint32_t tmp_target = decode.target<<2;
      uint32_t tmp_c = count>>28<<28;
      count = tmp_target+tmp_c;
      if(0<=count<=0x1000000){
      pc =&ins_mem[count];
    }
      else{
        exit(-11);
      }
    }
    break;

    case 0b000011:
    //JAL
    if(ins_mem[count+1]==0){
      if(2<=(count+2)<=0x1000000){
        r[31] = count+2;
      }
      else{
        exit(-11);
      }
      uint32_t tmp_target = decode.target<<2;
      uint32_t tmp_c = count>>28<<28;
      count = tmp_target+tmp_c;
      if(0<=count<=0x1000000){
      pc =&ins_mem[count];
    }
      else{
        exit(-11);
      }
    }

    else{
      compare_op(ins_mem[count+1]);
      if(2<=(count+2)<=0x1000000){
        r[31] = count+2;
      }
      else{
        exit(-11);
      }
      uint32_t tmp_target = decode.target<<2;
      uint32_t tmp_c = count>>28<<28;
      count = tmp_target+tmp_c;
      if(0<=count<=0x1000000){
      pc =&ins_mem[count];
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
