#include<iostream>
#include "comop.hpp"
#include "rtype.hpp"
#include "jtype.hpp"
#include "itype.hpp"

using namespace std;

uint32_t count  = 0;

void compare_op(uint32_t reg){
  rtype decode;
  decode.opcode=reg>>26;
  if(decode.opcode==0){
    r_type(reg);
  }
  else {
    if(decode.opcode==2||decode.opcode=3){
    //go to I j_type
    j_type(reg);
  }
  else{
    //go to i_type
    i_type(reg);
    //reset
    }
  }

  if(count<0||
    count>(0x1000000)>>2){
        exit(-11);
      }

  if(r[0] != 0){
    exit(-21);
  }

}
