#include<iostream>
#include<cstdio>
#include<stdint.h>
#include<stdlib.h>
#include"itype.hpp"
#include "comop.hpp"
using namespace std;

void addr_getc(int32_t (&r)[32], uint8_t rt){

  int n = getchar();
  if(n==EOF){
    r[rt] = -1;
  }
  else{
    r[rt] = n;
  }
}

void addr_putc(int32_t (&r)[32], uint8_t rt){
    putchar(r[rt]);
}



void i_type(int32_t (&r)[32], uint32_t ins,uint32_t *ins_mem,uint8_t *data_mem,
            int32_t &hi,int32_t &lo, uint32_t &pc, uint32_t &count){

  itype decode;
  decode.opcode=ins>>26;

  decode.rs = ins<<6>>27;
  //<<"rs in itype is "<<decode.rs<<endl;
  decode.rt = ins<<11>>27;
  //<<"rt in itype is "<<decode.rt<<endl;
  decode.ai = ins<<16>>16;
  //<<"ai in itype is "<<decode.ai<<endl;
  decode.sai = ins<<16>>16;
  //<<"sai in itype is "<<decode.sai<<endl;

  switch(decode.opcode){

    case 0b001001:{
    //ADDIU

      r[decode.rt] = (unsigned int)r[decode.rs] + decode.sai;

      count++;
      pc = pc + 4;}
    break;

    case 0b001000:{
    //ADDI
    int64_t tmp1 = r[decode.rs];
    int64_t tmp2 = decode.sai;
    int64_t test = tmp1+tmp2;

    if(test>=-2147483648&&test<=2147483647){
     r[decode.rt] = r[decode.rs]+decode.sai;

    }
    else{
      //<<"overflow"<<endl;
     exit(-10);
    }

      count++;
      pc = pc + 4;}
    break;

    case 0b001100:{
    //ANDI
      uint32_t tmp_ai = decode.ai;
      r[decode.rt] = r[decode.rs] & tmp_ai;
      count++;
      pc = pc + 4;}

    break;

    case 0b001101:{
    //ORI
      int32_t tmp_ai = decode.ai;

      //<<"decode.ai in ori is "<<tmp_ai<<endl;
      r[decode.rt] = r[decode.rs] | tmp_ai;
      //<<"rt in ori is "<<r[decode.rt]<<endl;
      count++;
      pc = pc + 4;}
    break;

    case 0b001110:{
    //XORI
      uint32_t tmp_ai = decode.ai;

      r[decode.rt] = r[decode.rs] ^ tmp_ai;
      count++;
      pc = pc + 4;}
    break;

    case 0b001010:{
    //SLTI

      if(r[decode.rs]<decode.sai){
        r[decode.rt] = 1;
      }
      else{
        r[decode.rt] = 0;
      }

      count++;
      pc = pc + 4;}
    break;

    case 0b001011:{
    //SLTIU

      //sign extension
      unsigned int tmp_sai = decode.sai;

      if(r[decode.rs]<tmp_sai){
        r[decode.rt] = 1;
      }
      else{
        r[decode.rt] = 0;
      }

      count++;
      pc = pc + 4;}
    break;

    case 0b100011:{
    //LW
    uint32_t mem_add = r[decode.rs];
    unsigned int addr = mem_add+decode.sai;
    int addr_off = addr - 0x20000000;

        if(addr>=0x20000000&&addr<=(0x24000000-3)){
          if(addr%4==0){

            uint32_t fir_byte= data_mem[addr_off+3];
            uint32_t sec_byte = data_mem[addr_off+2];
            uint32_t thi_byte = data_mem[addr_off+1];
            int32_t for_byte = data_mem[addr_off];

            r[decode.rt] = fir_byte+(sec_byte<<8)+(thi_byte<<16)+(for_byte<<24);
          }
          else{
            exit(-11);
          }
        }
        else{
          if(addr==0x30000000){
            addr_getc(r,decode.rt);
          }
          else{
            //unaligned
            exit(-11);
          }
        }

    count++;
    pc = pc + 4;}
    break;

    case 0b101011:{
    //SW
    uint32_t mem_add = r[decode.rs];
    uint32_t addr =mem_add+decode.sai;
    int addr_off = addr - 0x20000000;

        if(addr>=0x20000000&&addr<=(0x24000000-3)){
          if(addr%4==0){
            uint32_t word = r[decode.rt];
            data_mem[addr_off] = word>>24;
            data_mem[addr_off+1] = word<<8>>24;
            data_mem[addr_off+2] = word<<16>>24;
            data_mem[addr_off+3] = word<<24>>24;

          }
          else{
            exit(-11);
          }
        }
        else{
          if(addr==0x30000004){
              addr_putc(r,decode.rt);
          }
          else{
            exit(-11);
          }
        }

    count++;
    pc = pc + 4;}
    break;

    case 0b101000:{
    //SB
    uint32_t mem_add = r[decode.rs];
    uint32_t addr = mem_add+decode.sai;
    int addr_off = addr - 0x20000000;

      if(addr>=0x20000000&&addr<=0x24000000){
        uint32_t data_reg = r[decode.rt];
        int8_t tmp=data_reg<<24>>24;
        data_mem[addr_off] = tmp;

      }
      else{
        if(addr<=0x30000007&&addr>=0x30000004){
          addr_putc(r,decode.rt);
        }
        else{
          exit(-11);
        }
      }
    count++;
    pc = pc + 4;}
    break;

    case 0b100000:{
    //LB
    uint32_t mem_add = r[decode.rs];
    unsigned int addr =mem_add+decode.sai;
    int addr_off = addr - 0x20000000;

      if(addr>=0x20000000&&addr<=0x24000000){
        uint32_t data_reg = data_mem[addr_off];
        int8_t tmp = data_reg<<24>>24;
        r[decode.rt] = tmp;
      }
      else{
        if(addr<=0x30000003&&addr>=0x30000000){
          addr_getc(r,decode.rt);
        }
        else{
          exit(-11);
        }
      }
    count++;
    pc = pc + 4;}
    break;

    case 0b100100:{
    //LBU
    uint32_t mem_add = r[decode.rs];
    unsigned int addr =mem_add+decode.sai;
    int addr_off = addr - 0x20000000;

    //IO
      if(addr>=0x20000000&&addr<=0x24000000){
        uint32_t data_reg = data_mem[addr_off];
        uint8_t tmp = data_reg<<24>>24;
        r[decode.rt] = tmp;
      }
      else{
        if(addr<=0x30000003&&addr>=0x30000000){
          addr_getc(r,decode.rt);
        }
        else{
          exit(-11);
        }
      }
    count++;
    pc = pc + 4;}
    break;

    case 0b001111:{
    //LUI
      int tmp = decode.sai<<16;
      r[decode.rt] = tmp;
      //<<"rt in lui is "<<tmp<<endl;

      count++;
      pc = pc + 4;}
    break;

    case 0b100001:{
      //LH
      uint32_t mem_add = r[decode.rs];
      unsigned int addr =mem_add+decode.sai;
      int addr_off = addr - 0x20000000;

        if(addr>=0x20000000&&addr<=(0x24000000-1)){
          if(addr%2==0){
            r[decode.rt] = data_mem[addr_off+1];
            int32_t sec_byte = data_mem[addr_off];
            sec_byte = sec_byte<<8;
            r[decode.rt] = r[decode.rt] + sec_byte;
          }
          else{
            exit(-11);
          }
        }
        else{
          if(addr==0x30000000||addr==0x30000002){
            addr_getc(r,decode.rt);
          }
          else{
            exit(-11);
          }
        }

      count++;
      pc = pc + 4;}
    break;

    case 0b101001:{
    //SH
    uint32_t mem_add = r[decode.rs];
    uint32_t data_reg = r[decode.rt];
    unsigned int addr =mem_add+decode.sai;
    int addr_off = addr - 0x20000000;

      if(addr>=0x20000000&&addr<=(0x24000000-1)){
        if(addr%2==0){

          data_mem[addr_off+1] = data_reg<<24>>24;
          data_mem[addr_off] = data_reg<<16>>24;
        }
        else{
          exit(-11);
        }
      }
      else{
        if(addr==0x30000004||addr==0x30000006){
          addr_putc(r,decode.rt);
        }
        else{
          exit(-11);
        }
      }

    count++;
    pc = pc + 4;}
    break;

    case 0b100101:{
    //LHU
    uint32_t mem_add = r[decode.rs];
    unsigned int addr =mem_add+decode.sai;
    int addr_off = addr - 0x20000000;

      if(addr>=0x20000000&&addr<=(0x24000000-1)){
        if(addr%2==0){
          r[decode.rt] = data_mem[addr_off+1];
          uint32_t sec_byte = data_mem[addr_off];
          sec_byte = sec_byte<<24>>16;
          r[decode.rt] = r[decode.rt] + sec_byte;
        }
        else{
          exit(-11);
        }
      }
      else{
        if(addr<=0x30000000&&addr>=0x30000002){
          addr_getc(r,decode.rt);
        }
        else{
          exit(-11);
        }
      }

    count++;
    pc = pc + 4;}
    break;

    case 0b000100:{
    //BEQ
      int32_t tmp = decode.sai;
      tmp = tmp<<2;
      uint32_t addr = pc+tmp+4;

      compare_op(r, ins_mem[count+1], ins_mem, data_mem, hi, lo, pc, count);

      if(r[decode.rs]==r[decode.rt]){

        if(addr>=0x10000000&&addr<=0x11000000){
          pc = addr;
          count =(addr-0x10000000)>>2;

        }
        else{
          exit(-11);
        }
       }
       else{
         pc=pc+4;
         count++;
       }
     }
    break;

    case 0b000101:{
    //BNE
        int32_t tmp = decode.sai;
        tmp = tmp<<2;
        uint32_t addr = pc+tmp+4;

        compare_op(r, ins_mem[count+1], ins_mem, data_mem, hi, lo, pc, count);

        if(r[decode.rs]!=r[decode.rt]){

          if(addr>=0x10000000&&addr<=0x11000000){
             pc=addr;
             count =(pc-0x10000000)>>2;
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

    case 0b000001:{
    //BGEZ and BLTZ
      switch(decode.rt){
        case 0b00001:{
        //BGEZ
            int32_t tmp = decode.sai;
            tmp = tmp<<2;
            uint32_t addr = pc+tmp+4;

            compare_op(r, ins_mem[count+1], ins_mem, data_mem, hi, lo, pc, count);

            if(r[decode.rs]>=0){


              if(addr>=0x10000000&&addr<=0x11000000){
                 pc=addr;
                 count =(pc-0x10000000)>>2;
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

        case 0b00000:{
          //BLTZ
           int32_t tmp = decode.sai;
           tmp = tmp<<2;
           uint32_t addr = pc+tmp+4;

           compare_op(r, ins_mem[count+1], ins_mem, data_mem, hi, lo, pc, count);

           if(r[decode.rs]<0){

             if(addr>=0x10000000&&addr<=0x11000000){
                pc=addr;
                count =(pc-0x10000000)>>2;
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

        case 0b10001:{
        //BGEZAL
            int32_t tmp = decode.sai;
            tmp = tmp<<2;
            uint32_t addr = pc+tmp+4;
            r[31]=pc+8;

            compare_op(r, ins_mem[count+1], ins_mem, data_mem, hi, lo, pc, count);

            if(r[decode.rs]>=0){

              if(addr>=0x10000000&&addr<=0x11000000){
                 pc=addr;
                 count =(pc-0x10000000)>>2;
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

        case 0b10000:{
        //BLTZAL
            int32_t tmp = decode.sai;
            tmp = tmp<<2;
            uint32_t addr = pc+tmp+4;
            r[31]=pc+8;

            compare_op(r, ins_mem[count+1], ins_mem, data_mem, hi, lo, pc, count);
            if(r[decode.rs]<0){

              if(addr>=0x10000000&&addr<=0x11000000){
                 pc= addr;
                 count =(pc-0x10000000)>>2;
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
    }
      break;

    case 0b000111:{
    //BGTZ
        int32_t tmp = decode.sai;
        tmp = tmp<<2;
        uint32_t addr = pc+tmp+4;

        compare_op(r, ins_mem[count+1], ins_mem, data_mem, hi, lo, pc, count);
        if(r[decode.rs]>0){



          if(addr>=0x10000000&&addr<=0x11000000){
             pc=addr;
             count =(pc-0x10000000)>>2;
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

    case 0b000110:{
    //BLEZ
        int32_t tmp = decode.sai;
        tmp = tmp<<2;
        uint32_t addr = pc+tmp+4;

        compare_op(r, ins_mem[count+1], ins_mem, data_mem, hi, lo, pc, count);
        if(r[decode.rs]<=0){

          if(addr>=0x10000000&&addr<=0x11000000){
             pc=addr;
             count =(pc-0x10000000)>>2;
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

    case 0b100010:{
      //LWL
      uint32_t effaddr = decode.sai + r[decode.rs];
      int effaddr_off = effaddr - 0x20000000;
      int read = 4-(effaddr_off%4);
      int move = read*8;

      if(read==4){
        r[decode.rt] = 0;
      }
      else{
        r[decode.rt] = ((uint32_t)(r[decode.rt]))<<move>>move;
      }

      if ((effaddr>=0x20000000)&&(effaddr<=0x24000000)){

        for (int i=0; i<read;i++){
          uint32_t bytes = data_mem[effaddr_off+i];
          bytes = bytes<<24>>24;
          int shift = 24-i*8;
          r[decode.rt] = r[decode.rt] + (bytes<<shift);
        }
      }
      else{
          if((effaddr>=0x30000000)&&(effaddr<=0x30000003)){
            addr_getc(r,decode.rt);
          }
          else{
            exit(-11);
          }
      }
      count++;
      pc=pc+4;}
    break;

    case 0b100110:{
      //LWR
      uint32_t effaddr = decode.sai + r[decode.rs];

      int effaddr_off = effaddr - 0x20000000;
      int read = (effaddr_off%4)+1;
      r[decode.rt] = ((unsigned int)(r[decode.rt]))>>(read*8)<<(read*8);

      if ((effaddr>=0x20000000)&&(effaddr<=0x24000000)){
        for(int i=0;i<read;i++){
          uint32_t bytes = data_mem[effaddr_off-i];
          bytes = bytes<<24>>24;
          int shift=i*8;
          r[decode.rt] = r[decode.rt] + (bytes<<shift);
        }
      }

      else{
        if((effaddr>=0x30000000)&&(effaddr<=0x30000003)){
          addr_getc(r,decode.rt);
        }
        else{
          exit(-11);
        }
      }

      count++;
      pc=pc+4;}
    break;

    default:
    exit(-12);
  }
}
