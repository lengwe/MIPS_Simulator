#include<iostream>
#include"itype.hpp"
using namespace std;

void i_type(uint32_t reg){
  itype decode;
  decode.opcode=reg>>26；
  decode.rs = reg<<6>>27;
  decode.rt = reg<<11>>27;
  decode.ai = reg<<16>>16;
  decode.sai = reg<<16>>16;

  switch(decode.opcode){

    case 0b001001:
    //ADDIU
    r[decode.rt] = r[decode.rs] + decode.ai;
  }
    break;

    case 0b001000:
    //ADDI
    int tmp1 = r[decode.rs];
    int tmp2 = r[decode.rt];
    if(-2147483648<=tmp1+tmp2<=2147483647){
      r[decode.rt] = tmp1+decode.sai;
    }
    else{
      exit(-10);
    }
    break;

    case:0b001100:
    //ANDI
    r[decode.rt] = r[decode.rs] & decode.ai;
    break;

    case:0b001101:
    //ORI
    r[decode.rt] = r[decode.rs] | decode.ai;
    break;

    case:0b001110:
    //XORI
    r[decode.rt] = r[decode.rs] ^ decode.ai;

    case:0b001010:
    //SLTI
    int rs_tmp = r[decode.rs];
    int ai_tmp = decode.sai

    if(rs_tmp<ai_tmp){
      r[decode.rt] = 1;
    }
    else{
      r[decode.rt] = 0;
    }
    break;

    case 0b001011:
    //SLTIU
    if(r[decode.rs]<decode.ai){
      r[decode.rt] = 1;
    }
    else{
      r[decode.rt] = 0;
    }
    break;

    case 0b100011：
    //LW
    //read the data into mem_address
    mem_add = &r[decode.rs];
    data_reg = &memory[*mem_add+decode.sai];
    r[decode.rt] = *data_reg;
    count++;
    break;

    case 0b101011:
    //SW
    mem_add = &r[decode.rs];
    data_reg = &r[decode.rt];
    memory[*mem_add+decode.sai] = *data_reg;
    count++;
    break;

    case 0b101000:
    //SB
    mem_add = &r[decode.rs];
    data_reg = &r[decode.rt];
    int32_t tmp=*data_reg<<24>>24;
    memory[*mem_add+decode.sai] = tmp;
    count++;
    break;

    case 0b100000:
    //LB
    mem_add = &r[decode.rs];
    data_reg = &memory[*mem_add+decode.sai];
    int32_t tmp=*data_reg<<24>>24;
    r[decode.rt] = tmp;
    count++;
    break;

    case 0b100100:
    //LBU
    mem_add = &r[decode.rs];
    data_reg = &memory[*mem_add+decode.sai];
    uint32_t tmp=*data_reg<<24>>24;
    r[decode.rt] = tmp;
    count++;
    break;

    case 0b001111:
    //LUI
    int tmp = r[decode.sai]<<16;
    r[decode.rt] = tmp;
    break;

    case 0b100001:
    //LH
    mem_add = &r[decode.rs];
    data_reg = &memory[*mem_add+decode.sai];
    int16_t tmp = *data_reg<<16>>16;
    r[decode.rt] = tmp;
    count++;
    break;

    case 0b101001:
    //SH
    mem_add = &r[decode.rs];
    data_reg = &r[decode.rt];
    int16_t tmp = *data_reg<<16>>16;
    memory[*mem_add+decode.sai] = tmp;
    count++;
    break;

    case 0b100101:
    //LHU
    mem_add = &r[decode.rs];
    data_reg = &memory[*mem_add+decode.sai];
    uint16_t tmp = *data_reg<<16>>16;
    r[decode.rt] = tmp;
    count++;
    break;

    case 0b000100:
    //BEQ
    if(r[decode.rs]==r[decode.rt]){
      int18_t tmp = decode.sai<<2;
      count += tmp;
      pc =&memory[count];
    }
    else{
      count++;
      pc = &memory[count];
    }
    break;

    case 0b000101:
    //BNE
    if(r[decode.rs]!=r[decode.rt]){
      int18_t tmp = decode.sai<<2;
      count += tmp;
      pc =&memory[count];
    }
    else{
      count++;
      pc = &memory[count];
    }
    break;

    case 0b000001:
    //BGEZ and BLTZ
      switch(decode.rt){
        case 0b00001:
        //BEGZ
          if(r[decode.rs]>=0){
            int18_t tmp = decode.sai<<2;
            count += tmp;
            pc =&memory[count];
          }
          else{
            count++;
            pc = &memory[count];
          }
        break;

        case 0b00000:
        //BLTZ
          if(r[decode.rs]<0){
            int18_t tmp = decode.sai<<2;
            count += tmp;
            pc =&memory[count];
          }
          else{
            count++;
            pc = &memory[count];
          }
        break;

        case 0b10001:
        //BGEZAL
          if(r[decode.rs]>=0){
            r[31] = count++;
            int18_t tmp_target = decode.sai<<2;
            count = tmp_target;
            pc = &memory[count];
          }
          else{
            count++;
            pc = &memory[count];
          }
        break;

        case 0b10000:
        //BLTZAL
          if(r[decode.rs]<=0){
            r[31] = count++;
            int18_t tmp_target = decode.sai<<2;
            count = tmp_target;
            pc = &memory[count];
          }
          else{
            count++;
            pc = &memory[count];
          }
        break;


        default:
        exit(-20);

        }



      if(r[decode.rs]<0){
        int18_t tmp = decode.sai<<2;
        count += tmp;
        pc =&memory[count];
      }
      else{
        count++;
        pc = &memory[count];
      }
    break;

    case: 0b000111:
    //BGTZ
    if(r[decode.rs]>0){
      int18_t tmp = decode.sai<<2;
      count += tmp;
      pc =&memory[count];
    }
    else{
      count++;
      pc = &memory[count];
    }
    break;

    case 0b000110:
    //BLEZ
    if(r[decode.rs]<=0){
      int18_t tmp = decode.sai<<2;
      count += tmp;
      pc =&memory[count];
    }
    else{
      count++;
      pc = &memory[count];
    }
    break;


    default:
    exit(-20);

}
