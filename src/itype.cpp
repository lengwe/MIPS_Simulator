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
  decode.rt = ins<<11>>27;
  decode.ai = ins<<16>>16;
  decode.sai = ins<<16>>16;

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
      uint32_t tmp_ai = decode.ai;
      r[decode.rt] = r[decode.rs] | tmp_ai;
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
      unsigned int tmp_ai = decode.ai;
      if(r[decode.rs]<tmp_ai){
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

      if((addr%4==0)||(addr%2==0)){

        if(addr>=0x20000000&&addr<=(0x24000000-3)){

          uint32_t fir_byte= data_mem[mem_add+decode.sai+3];
          uint32_t sec_byte = data_mem[mem_add+decode.sai+2];
          uint32_t thi_byte = data_mem[mem_add+decode.sai+1];
          int32_t for_byte = data_mem[mem_add+decode.sai];

          r[decode.rt] = fir_byte+(sec_byte<<8)+(thi_byte<<16)+(for_byte<<24);
        }
        else{
          if(addr==0x30000000){
            addr_getc(r,decode.rt);
          }
        }
      }
      else{
        //unaligned
        exit(-11);
      }
    count++;
    pc = pc + 4;}
    break;

    case 0b101011:{
    //SW
    uint32_t mem_add = r[decode.rs];
    uint32_t addr =mem_add+decode.sai;

    //IO
    if((addr%4==0)||(addr%2==0)){

        if(addr>=0x20000000&&addr<=(0x24000000-3)){
        uint32_t word = r[decode.rt];
        data_mem[addr+3] = word<<24>>24;
        data_mem[addr+2] = word<<16>>24;
        data_mem[addr+1] = word<<8>>24;
        data_mem[addr] = word>>24;
      }
      else{
        if(addr==0x30000004){
            addr_putc(r,decode.rt);
        }
      }
    }
    else{
      exit(-11);
    }

    count++;
    pc = pc + 4;}
    break;

    case 0b101000:{
    //SB
    uint32_t mem_add = r[decode.rs];
    uint32_t addr = mem_add+decode.sai;

    //IO
    if(addr<=0x30000007&&addr>=0x30000004){
      addr_putc(r,decode.rt);
    }
    if(addr>=0x20000000&&addr<=0x24000000){

      uint32_t data_reg = r[decode.rt];
      int8_t tmp=data_reg<<24>>24;
      data_mem[addr] = tmp;
    }
    else{
      exit(-11);
    }

    count++;
    pc = pc + 4;}
    break;

    case 0b100000:{
    //LB
    uint32_t mem_add = r[decode.rs];
    unsigned int addr =mem_add+decode.sai;

    if(addr!=0){
      if(addr>=0x20000000&&addr<=0x24000000){
        uint32_t data_reg = data_mem[addr];
        int8_t tmp = data_reg<<24>>24;
        r[decode.rt] = tmp;
      }
      else{
        if(addr<=0x30000003&&addr>=0x30000000){
          addr_getc(r,decode.rt);
        }
      }
    }
    else{
      exit(-11);
    }

    count++;
    pc = pc + 4;}
    break;

    case 0b100100:{
    //LBU
    uint32_t mem_add = r[decode.rs];
    unsigned int addr =mem_add+decode.sai;

    //IO
    if(addr!=0){
      if(addr>=0x20000000&&addr<=0x24000000){
        uint32_t data_reg = data_mem[addr];
        uint8_t tmp = data_reg<<24>>24;
        r[decode.rt] = tmp;
      }
      else{
        if(addr<=0x30000003&&addr>=0x30000000){
          addr_getc(r,decode.rt);
        }
      }
    }
    else{
      exit(-11);
    }
    count++;
    pc = pc + 4;}
    break;

    case 0b001111:{
    //LUI
    int tmp = decode.sai<<16;
    r[decode.rt] = tmp;
    count++;
    pc = pc + 4;}
    break;

    case 0b100001:{
    //LH
    uint32_t mem_add = r[decode.rs];
    unsigned int addr =mem_add+decode.sai;

    //IO
    if(addr%2==0){
      if(addr>=0x20000000&&addr<=(0x24000000-1)){

        r[decode.rt] = data_mem[addr+1];
        int32_t sec_byte = data_mem[addr];
        sec_byte = sec_byte<<8;
        r[decode.rt] = r[decode.rt] + sec_byte;
      }
      else{
        if(addr==0x30000000||addr==0x30000002){
          addr_getc(r,decode.rt);
        }
      }
    }
    else{
      exit(-11);
    }

    count++;
    pc = pc + 4;}
    break;

    case 0b101001:{
    //SH
    uint32_t mem_add = r[decode.rs];
    uint32_t data_reg = r[decode.rt];
    unsigned int addr =mem_add+decode.sai;

    //IO
    if((addr%2==0)){

      if(addr>=0x20000000&&addr<=(0x24000000-1)){
        data_mem[addr+1] = data_reg<<24>>24;
        data_mem[addr] = data_reg<<16>>24;
      }
      else{
        if(addr==0x30000004||addr==0x30000006){
          addr_putc(r,decode.rt);
        }
      }
    }
    else{
      exit(-11);
    }

    count++;
    pc = pc + 4;}
    break;

    case 0b100101:{
    //LHU
    uint32_t mem_add = r[decode.rs];
    unsigned int addr =mem_add+decode.sai;

    //IO
    if((addr%2==0)&&(addr>=0x20000000&&addr<=0x24000000-1)){
      if(addr>=0x20000000&&addr<=(0x24000000-1)){
        r[decode.rt] = data_mem[addr+1];
        uint32_t sec_byte = data_mem[addr];
        sec_byte = sec_byte<<8;
        r[decode.rt] = r[decode.rt] + sec_byte;
      }
      else{
        if(addr<=0x30000000&&addr>=0x30000002){
          addr_getc(r,decode.rt);
        }
      }
    }
    else{
      exit(-11);
    }

    count++;
    pc = pc + 4;}
    break;

    case 0b000100:{
    //BEQ

      if (ins_mem[count+1]==0){

        if(r[decode.rs]==r[decode.rt]){

          //signed extension to 32 bits;
          int32_t tmp = decode.sai;
          //shift 2 bits to left
          tmp = tmp<<2;
          pc = pc+tmp+4;
          if(pc>=0x10000000&&pc<=0x11000000){

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

      else{//branch delay

        compare_op(r, ins_mem[count+1], ins_mem, data_mem, hi, lo, pc, count);

        if(r[decode.rs]==r[decode.rt]){

          //signed extension to 32 bits;
          int32_t tmp = decode.sai;
          //shift 2 bits to left
          tmp = tmp<<2;
          pc = pc+tmp+4;
          if(pc>=0x10000000&&pc<=0x11000000){

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
    }
    break;

    case 0b000101:{
    //BNE

      if (ins_mem[count+1]==0){

        if(r[decode.rs]!=r[decode.rt]){

          //signed extension to 32 bits;
          int32_t tmp = decode.sai;
          //shift 2 bits to left
          tmp = tmp<<2;
          pc = pc+tmp+4;
          if(pc>=0x10000000&&pc<=0x11000000){

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
      else{
        compare_op(r, ins_mem[count+1], ins_mem, data_mem, hi, lo, pc, count);
        if(r[decode.rs]!=r[decode.rt]){

          //signed extension to 32 bits;
          int32_t tmp = decode.sai;
          //shift 2 bits to left
          tmp = tmp<<2;
          pc = pc+tmp+4;
          if(pc>=0x10000000&&pc<=0x11000000){

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
    }
    break;

    case 0b000001:{
    //BGEZ and BLTZ
      switch(decode.rt){
        case 0b00001:{
        //BEGZ

          int rs_tmp = r[decode.rs];

          if (ins_mem[count+1]==0){

            if(rs_tmp>=0){
              //change
              //signed extension to 32 bits;
              int32_t tmp = decode.sai;
              //shift 2 bits to left
              tmp = tmp<<2;
              pc = pc+tmp+4;
              if(pc>=0x10000000&&pc<=0x11000000){

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
          else{//delay slot
            compare_op(r, ins_mem[count+1], ins_mem, data_mem, hi, lo, pc, count);

            if(rs_tmp>=0){

              //signed extension to 32 bits;
              int32_t tmp = decode.sai;
              //shift 2 bits to left
              tmp = tmp<<2;
              pc = pc+tmp+4;
              if(pc>=0x10000000&&pc<=0x11000000){

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
        }
        break;

        case 0b00000:{
        //BLTZ

        int rs_tmp = r[decode.rs];

          if (ins_mem[count+1]==0){

            if(rs_tmp<0){

              //signed extension to 32 bits;
              int32_t tmp = decode.sai;
              //shift 2 bits to left
              tmp = tmp<<2;
              pc = pc+tmp+4;
              if(pc>=0x10000000&&pc<=0x11000000){

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
          else{//delay slot
            compare_op(r, ins_mem[count+1], ins_mem, data_mem, hi, lo, pc, count);

            if(rs_tmp<0){

              //signed extension to 32 bits;
              int32_t tmp = decode.sai;
              //shift 2 bits to left
              tmp = tmp<<2;
              pc = pc+tmp+4;
              if(pc>=0x10000000&&pc<=0x11000000){

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
        }
        break;

        case 0b10001:{
        //BGEZAL
        int rs_tmp = r[decode.rs];

          if(ins_mem[count+1]==0){

            if(rs_tmp>=0){

              r[31] = pc+8;
              //signed extension to 32 bits;
              int32_t tmp = decode.sai;
              //shift 2 bits to left
              tmp = tmp<<2;
              pc = pc+tmp+4;
              if(pc>=0x10000000&&pc<=0x11000000){

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
          else{//delay slot
            compare_op(r, ins_mem[count+1], ins_mem, data_mem, hi, lo, pc, count);

            if(rs_tmp>=0){

              r[31] = pc+8;
              //signed extension to 32 bits;
              int32_t tmp = decode.sai;
              //shift 2 bits to left
              tmp = tmp<<2;
              pc = pc+tmp+4;
              if(pc>=0x10000000&&pc<=0x11000000){

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
        }
        break;

        case 0b10000:{
        //BLTZAL
        int rs_tmp = r[decode.rs];

          if(ins_mem[count+1]==0){

            if(rs_tmp<0){

              r[31] = pc+8;
              //signed extension to 32 bits;
              int32_t tmp = decode.sai;
              //shift 2 bits to left
              tmp = tmp<<2;
              pc = pc+tmp+4;
              if(pc>=0x10000000&&pc<=0x11000000){

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
          else{//delay slot
            compare_op(r, ins_mem[count+1], ins_mem, data_mem, hi, lo, pc, count);

            if(rs_tmp<0){

              r[31] = pc+8;
              //signed extension to 32 bits;
              int32_t tmp = decode.sai;
              //shift 2 bits to left
              tmp = tmp<<2;
              pc = pc+tmp+4;
              if(pc>=0x10000000&&pc<=0x11000000){

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
        }
        break;


        default:
        exit(-12);

      }
    }
      break;

    case 0b000111:{
    //BGTZ
      int rs_tmp = r[decode.rs];

      if (ins_mem[count+1]==0){

        if(rs_tmp>0){

          //signed extension to 32 bits;
          int32_t tmp = decode.sai;
          //shift 2 bits to left
          tmp = tmp<<2;
          pc = pc+tmp+4;

          if(pc>=0x10000000&&pc<=0x11000000){

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
      else{//delay slot
        compare_op(r, ins_mem[count+1], ins_mem, data_mem, hi, lo, pc, count);

        if(rs_tmp>0){

          //signed extension to 32 bits;
          int32_t tmp = decode.sai;
          //shift 2 bits to left
          tmp = tmp<<2;
          pc = pc+tmp+4;

          if(pc>=0x10000000&&pc<=0x11000000){

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
    }
    break;

    case 0b000110:{
    //BLEZ
      int rs_tmp = r[decode.rs];

      if (ins_mem[count+1]==0){

        if(rs_tmp<=0){

          //signed extension to 32 bits;
          int32_t tmp = decode.sai;
          //shift 2 bits to left
          tmp = tmp<<2;
          pc = pc+tmp+4;

          if(pc>=0x10000000&&pc<=0x11000000){

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
      else{//delay slot
        compare_op(r, ins_mem[count+1], ins_mem, data_mem, hi, lo, pc, count);

        if(rs_tmp<=0){

          //signed extension to 32 bits;
          int32_t tmp = decode.sai;
          //shift 2 bits to left
          tmp = tmp<<2;
          pc = pc+tmp+4;

          if(pc>=0x10000000&&pc<=0x11000000){

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
    }
    break;

    case 0b100010:{
      //LWL
      uint32_t effaddr = decode.sai + r[decode.rs];

      //IO
      // if(effaddr<=0x30000003&&effaddr>=0x30000000){
      //   addr_getc();
      // }
      //
      // if(effaddr<=0x30000007&&effaddr>=0x30000004){
      //   exit(-21);
      // }

      if(effaddr>=(0x20000000+1)
          &&effaddr<=0x24000000){

        int32_t msig_byte = data_mem[effaddr-1];
        uint32_t lsig_byte = data_mem[effaddr];
        int32_t h_word = (msig_byte<<24) + (lsig_byte<<16);
        uint32_t tmp_rt = r[decode.rt];
        r[decode.rt] = (tmp_rt<<16>>16)+h_word;
      }
      else{
        exit(-11);
      }

      count++;
      pc=pc+4;}
    break;

    case 0b100110:{
      //LWR
      uint32_t effaddr = decode.sai + r[decode.rs];

      //IO
      // if(effaddr<=0x30000003&&effaddr>=0x30000000){
      //   addr_getc();
      // }
      //
      // if(effaddr<=0x30000007&&effaddr>=0x30000004){
      //   exit(-21);
      // }

      if(effaddr>=0x20000000&&
        effaddr<=(0x24000000-1)){
        uint32_t lsig_byte = data_mem[effaddr+1];
        uint32_t msig_byte = data_mem[effaddr];
        int32_t h_word = (msig_byte<<8) + lsig_byte;
        uint32_t tmp_rt = r[decode.rt];
        r[decode.rt] = (tmp_rt>>16<<16)+h_word;
      }
      else{
        exit(-11);
      }

      count++;
      pc=pc+4;}
    break;

    default:
    exit(-12);
  }
}
