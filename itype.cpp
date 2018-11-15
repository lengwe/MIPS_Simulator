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
    count++;
    pc = pc + 4;
    break;

    case 0b001000:
    //ADDI
    int tmp1 = r[decode.rs];
    int tmp2 = r[decode.rt];
    if((tmp1+tmp2)>=-2147483648&&
    (tmp1+tmp2)<=2147483647){
      r[decode.rt] = tmp1+decode.sai;
    }
    else{
      exit(-10);
    }
    count++;
    pc = pc + 4;
    break;

    case:0b001100:
    //ANDI
    r[decode.rt] = r[decode.rs] & decode.ai;
    count++;
    pc = pc + 4;
    break;

    case:0b001101:
    //ORI
    r[decode.rt] = r[decode.rs] | decode.ai;
    count++;
    pc = pc + 4;
    break;

    case:0b001110:
    //XORI
    r[decode.rt] = r[decode.rs] ^ decode.ai;
    count++;
    pc = pc + 4;
    break;

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
    count++;
    pc = pc + 4;
    break;

    case 0b001011:
    //SLTIU
    if(r[decode.rs]<decode.ai){
      r[decode.rt] = 1;
    }
    else{
      r[decode.rt] = 0;
    }
    count++;
    pc = pc + 4;
    break;

    case 0b100011：
    //LW
    uint32_t mem_add = r[decode.rs];
      if((mem_add+decode.sai)%4==0||
         ((mem_add+decode.sai)>=0&&
         (mem_add+decode.sai)<=0x4000000-3)){
        int32_t fir_byte= data_mem[mem_add+decode.sai];
        int32_t sec_byte = data_mem[mem_add+decode.sai+1];
        int32_t thi_byte = data_mem[mem_add+decode.sai+2];
        int32_t for_byte = data_mem[mem_add+decode.sai+3];
        r[decode.rt] = fir_byte+(sec_byte<<8)+(thi_byte<<16)+(for_byte<<24);
      }
      else{
        //unaligned
        exit(-11);
      }
   }
    count++;
    pc = pc + 4;
    break;

    case 0b101011:
    //SW
    if((mem_add+decode.sai)%4==0||
       ((mem_add+decode.sai)>=0&&
       (mem_add+decode.sai)<=0x4000000-3)){
      uint32_t word = r[decode.rt];
      data_mem[mem_add+decode.sai] = word<<24>>24;
      data_mem[mem_add+decode.sai+1] = word<<16>>24;
      data_mem[mem_add+decode.sai+2] = word<<8>>24;
      data_mem[mem_add+decode.sai+3] = word>>24;
    }
    else{
      exit(-11);
    }
    count++;
    pc = pc + 4;
    break;

    case 0b101000:
    //SB
    if((mem_add+decode.sai)>=0&&
    (mem_add+decode.sai)<=0x4000000){
    uint32_t mem_add = r[decode.rs];
    uint32_t data_reg = r[decode.rt];
    int8_t tmp=data_reg<<24>>24;
    data_mem[mem_add+decode.sai] = tmp;
    }
    else{
      exit(-11);
    }
    count++;
    pc = pc + 4;
    break;

    case 0b100000:
    //LB
    if((mem_add+decode.sai)>=0&&
    (mem_add+decode.sai)<=0x4000000){
    uint32_t mem_add = r[decode.rs];
    uint32_t data_reg = data_mem[mem_add+decode.sai];
    int8_t tmp = data_reg<<24>>24;
    r[decode.rt] = tmp;
    }
    else{
      exit(-11);
    }
    count++;
    pc = pc + 4;
    break;

    case 0b100100:
    //LBU
    if((mem_add+decode.sai)>=0&&
    (mem_add+decode.sai)<=0x4000000){
    uint32_t mem_add = r[decode.rs];
    uint32_t data_reg = data_mem[mem_add+decode.sai];
    uint8_t tmp = data_reg<<24>>24;
    r[decode.rt] = tmp;
    }
    else{
      exit(-11);
    }
    count++;
    pc = pc + 4;
    break;

    case 0b001111:
    //LUI
    int tmp = r[decode.sai]<<16;
    r[decode.rt] = tmp;
    count++;
    pc = pc + 4;
    break;

    case 0b100001:
    //LH
    uint32_t mem_add = r[decode.rs];
    if((mem_add+decode.sai)%4==0||
    ((mem_add+decode.sai)>=0&&
    (mem_add+decode.sai)<=0x4000000-1))
    {
      r[decode.rt] = data_mem[mem_add+decode.sai];
      int32_t sec_byte = data_mem[mem_add+decode.sai+1];
      sec_byte = sec_byte<<8;
      r[decode.rt] = r[decode.rt] + sec_byte;
    }
    else{
      exit(-11);
    }
    count++;
    pc = pc + 4;
    break;

    case 0b101001:
    //SH
    uint32_t mem_add = r[decode.rs];
    uint32_t data_reg = r[decode.rt];
    if((mem_add+decode.sai)%4==0||
    ((mem_add+decode.sai)>=0&&
    (mem_add+decode.sai)<=0x4000000-1)){
      data_mem[mem_add+decode.sai] = data_reg<<24>>24;
      data_mem[mem_add+decode.sai+1] = data_reg<<16>>24;
    }
    else{
      exit(-11);
    }
    count++;
    pc = pc + 4;
    break;

    case 0b100101:
    //LHU
    uint32_t mem_add = r[decode.rs];
    if((mem_add+decode.sai)%4==0||
    ((mem_add+decode.sai)>=0&&
    (mem_add+decode.sai)<=0x4000000-1)){
      r[decode.rt] = data_mem[mem_add+decode.sai];
      uint32_t sec_byte = data_mem[mem_add+decode.sai+1];
      sec_byte = sec_byte<<8;
      r[decode.rt] = r[decode.rt] + sec_byte;
    }
    else{
      exit(-11);
    }
    count++;
    pc = pc + 4;
    break;

    case 0b000100:
    //BEQ

      if (ins_mem[count+1]==0){

        if(r[decode.rs]==r[decode.rt]){
          uint32_t tmp = decode.sai<<2;
          count = count+tmp+1;

          if(count>=0&&
            count<=(0x1000000>>2)){
          pc = pc + (count<<2);
        }
          else{
            exit(-11);
          }
      }

        else{
          count++;
          pc = pc + 4;
        }
      }

      else{
        //branch delay
        compare_op(ins_mem[count+1]);
        if(r[decode.rs]==r[decode.rt]){
          uint32_t tmp = decode.sai<<2;
          count = count+tmp+1;
          if(count>=0&&
            count<=(0x1000000>>2)){
          pc = pc + (count<<2);
        }
          else{
            exit(-11);
          }
      }

        else{
          count++;
          pc = pc + 4;
        }
      }
    break;

    case 0b000101:
    //BNE

    if (ins_mem[count+1]==0){

      if(r[decode.rs]!=r[decode.rt]){
        uint32_t tmp = decode.sai<<2;
        count = count+tmp+1;
        if(count>=0&&
          count<=(0x1000000>>2)){
        pc = pc + (count<<2);
      }
        else{
          exit(-11);
        }
      }

      else{
        count++;
        pc = pc + 4;
      }
    }

    else{
      compare_op(ins_mem[count+1]);
      if(r[decode.rs]!=r[decode.rt]){
        uint32_t tmp = decode.sai<<2;
        count = count+tmp+1;
        if(count>=0&&
          count<=(0x1000000>>2)){
        pc = pc + (count<<2);
      }
        else{
          exit(-11);
        }
      }

      else{
        count++;
        pc = pc + 4;
      }
    }
    break;

    case 0b000001:
    //BGEZ and BLTZ
      switch(decode.rt){
        case 0b00001:
        //BEGZ

        if (ins_mem[count+1]==0){

          if(r[decode.rs]>=0){
            uint32_t tmp = decode.sai<<2;
            count = count+tmp+1;
            if(count>=0&&
              count<=(0x1000000>>2)){
            pc = pc + (count<<2);
          }
            else{
              exit(-11);
            }
          }

          else{
            count++;
            pc=pc+4;
          }
        }

        else{
          compare_op(ins_mem[count+1]);
          if(r[decode.rs]>=0){
            uint32_t tmp = decode.sai<<2;
            count = count+tmp+1;
            if(count>=0&&
              count<=(0x1000000>>2)){
            pc = pc + (count<<2);
          }
            else{
              exit(-11);
            }
          }

          else{
            count++;
            pc=pc+4;
          }
        }
        break;

        case 0b00000:
        //BLTZ

        if (ins_mem[count+1]==0){

          if(r[decode.rs]<0){
            uint32_t tmp = decode.sai<<2;
            count = count+tmp+1;
            if(count>=0&&
              count<=(0x1000000>>2)){
            pc = pc + (count<<2);
          }
            else{
              exit(-11);
            }
          }

          else{
            count++;
            pc=pc+4;
          }
        }

        else{
          compare_op(ins_mem[count+1]);
          if(r[decode.rs]<0){
            uint32_t tmp = decode.sai<<2;
            count = count+tmp+1;
            if(count>=0&&
              count<=(0x1000000>>2)){
            pc = pc + (count<<2);
          }
            else{
              exit(-11);
            }
          }

          else{
            count++;
            pc=pc+4;
          }
        }
        break;

        case 0b10001:
        //BGEZAL

        if(ins_mem[count+1]==0){

          if(r[decode.rs>=0]){
            r[31] = count+2;
            uint32_t tmp_target = decode.sai<<2;
            count = tmp_target;
            if(count>=0&&
              count<=(0x1000000>>2)){
            pc = pc + (count<<2);
          }
            else{
              exit(-11);
            }
          }
          else{
            count++;
            pc=pc+4;
          }
        }

        else{
          compare_op(ins_mem[count+1]);
          if(r[decode.rs>=0]){
            r[31] = count+2;
            uint32_t tmp_target = decode.sai<<2;
            count = tmp_target;
            if(count>=0&&
              count<=(0x1000000>>2)){
            pc = pc + (count<<2);
          }
            else{
              exit(-11);
            }
          }

          else{
            count++;
            pc=pc+4;
          }
        }
        break;

        case 0b10000:
        //BLTZAL
        if(ins_mem[count+1]==0){

          if(r[decode.rs<0]){
            r[31] = count+2;
            uint32_t tmp_target = decode.sai<<2;
            count = tmp_target;
            if(count>=0&&
              count<=(0x1000000>>2)){
            pc = pc + (count<<2);
          }
            else{
              exit(-11);
            }
          }
          else{
            count++;
            pc=pc+4;
          }
        }

        else{
          compare_op(ins_mem[count+1]);
          if(r[decode.rs<0]){
            r[31] = count+2;
            uint32_t tmp_target = decode.sai<<2;
            count = tmp_target;
            if(count>=0&&
              count<=(0x1000000>>2)){
            pc = pc + (count<<2);
          }
            else{
              exit(-11);
            }
          }
          else{
            count++;
            pc=pc+4;
          }
        }
        break;


        default:
        exit(-12);

      }

    case: 0b000111:
    //BGTZ

    if (ins_mem[count+1]==0){

      if(r[decode.rs]>0){
        uint32_t tmp = decode.sai<<2;
        count = count+tmp+1;
        if(count>=0&&
          count<=(0x1000000>>2)){
        pc = pc + (count<<2);
      }
        else{
          exit(-11);
        }
      }

      else{
        count++;
        pc=pc+4;
      }
    }

    else{
      compare_op(ins_mem[count+1]);
      if(r[decode.rs]>0){
        uint32_t tmp = decode.sai<<2;
        count = count+tmp+1;
        if(count>=0&&
          count<=(0x1000000>>2)){
        pc = pc + (count<<2);
      }
        else{
          exit(-11);
        }
      }

      else{
        count++;
        pc=pc+4;
      }
    }
    break;

    case 0b000110:
    //BLEZ

    if (ins_mem[count+1]==0){

      if(r[decode.rs]<=0){
        uint32_t tmp = decode.sai<<2;
        count = count+tmp+1;
        if(count>=0&&
          count<=(0x1000000>>2)){
        pc = pc + (count<<2);
      }
        else{
          exit(-11);
        }
      }

      else{
        count++;
        pc=pc+4;
      }
    }

    else{
      compare_op(ins_mem[count+1]);
      if(r[decode.rs]<=0){
        uint32_t tmp = decode.sai<<2;
        count = count+tmp+1;
        if(count>=0&&
          count<=(0x1000000>>2)){
        pc = pc + (count<<2);
      }
        else{
          exit(-11);
        }
      }

      else{
        count++;
        pc=pc+4;
      }
    }
    break;

    case 0b100010:
    //LWL
    uint32_t effaddr = decode.sai + r[decode.rs];
    if(effaddr>=0&&
      effaddr<=0x4000000){
      int32_t msig_byte = data_mem[effaddr];
      uint32_t lsig_byte = data_mem[effaddr-1];
      int32_t h_word = (msig_byte<<24) + (lsig_byte<<16);
      uint32_t tmp_rt = r[decode.rt];
      r[decode.rt] = (tmp_rt<<16>>16)+h_word;
    }
    else{
      exit(-11);
    }

    count++;
    pc=pc+4;
    break;

    case 0b100110:
    //LWR
    uint32_t effaddr = decode.sai + r[decode.rs];
    if(effaddr>=0&&
      effaddr<=0x4000000-1){
      uint32_t lsig_byte = data_mem[effaddr];
      uint32_t msig_byte = data_mem[effaddr+1];
      int32_t h_word = (msig_byte<<8) + lsig_byte;
      uint32_t tmp_rt = r[decode.rt];
      r[decode.rt] = (tmp_rt>>16<<16)+h_word;
    }
    else{
      exit(-11);
    }

    count++;
    pc=pc+4;
    break;

    default:
    exit(-12);
  }

}
