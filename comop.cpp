#include<iostream>
#include "comop.hpp"
#include "rtype.hpp"
#include "jtype.hpp"
#include "itype.hpp"

using namespace std;

unsigned int count  = 0;

void compare_op(uint32_t reg){
  rtype decode;
  decode.opcode=reg>>26;
  if(decode.opcode==0){
    r_type(reg);
    count++;
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
}
