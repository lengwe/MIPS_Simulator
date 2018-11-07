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
    uint28_t tmp_target = decode.target<<2;
    count = tmp_target;
    pc = &memory[count];
    break;

    case 0b000011:
    //JAL
    r[31] = count++;
    uint28_t tmp_target = decode.target<<2;
    count = tmp_target;
    pc = &memory[count];
    break;

    default:
    exit(-20);

  }
}
