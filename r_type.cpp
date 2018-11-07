#include<iostream>
#include "r_type.h"
using namespace std;

void r_type(uint32_t reg){
  rtype decode;
  decode.rs = reg<<6>>27;
  decode.rt = reg<<11>>27;
  decode.rd = reg<<16>>27;
  decode.shamt = reg<<21>>27;
  decode.func = reg<<26>>26;

  if(decode.shamt!=0){
   //Shift amount is not zero
    switch (decode.func) {
      case 0b000000:
      //SLL shift left logical
      if(decode.shamt){
        r[decode.rd] = r[decode.rt]<<decode.shamt;
      }
      else{

      }
      break;

      case 0b000010:
      //SRL Shift right logical
        r[decode.rd] = r[decode.rt]>>decode.shamt;
      break;

      case 0b000011:
      //SRA Shift right arithmetic
      int32_t reg_signed = r[decode.rt];
      r[decode.rd] = reg_signed>>decode.shamt;
      break;

      default:
      exit(-20);
    }
  }

  else{
      switch (decode.func) {
        case 0b100000:
        //add
        int tmp1 = r[decode.rs];
        int tmp2 = r[decode.rt];
        if(-2147483648<=tmp1+tmp2<=2147483647){
          r[decode.rd] = tmp1+tmp2;
        }
        else{
          exit(-10);
        }
        break;

        case 0b100010:
        //sub
        int tmp1 = r[decode.rs];
        int tmp2 = r[decode.rt];
        if(-2147483648<=tmp1-tmp2<=2147483647){
          r[decode.rd] = tmp1-tmp2;
        }
        else{
          exit(-10);
        }
        break;

        case 0b100001:
        //addu
        r[decode.rd] = r[decode.rs]+r[decode.rt];
        break;

        case 0b100011:
        //subu
        r[decode.rd] = r[decode.rs]-r[decode.rt];
        break;

        case 0b100100:
        //AND
        r[decode.rd] = r[decode.rs]&r[decode.rt];
        break;

        case 0b100101:
        //OR
        r[decode.rd] = r[decode.rs]|r[decode.rt];
        break;

        case 0b100110:
        //XOR
        r[decode.rd] = r[decode.rs]^r[decode.rt];
        break;

        case 0b000100:
        //sllv(min and max)
        if(0<=r[decode.rs]<32){
        r[decode.rd] = r[decode.rt]<<r[decode.rs];
        }
        else{
          //报错
        }

        case 0b000110:
        //srlv
        if(0<=r[decode.rs]<32){
        r[decode.rd] = r[decode.rt]>>r[decode.rs];
        }
        else{
          //报错
        }

        case 0b000111:
        //srav
        if(0<=r[decode.rs]<32){
        int32_t reg_signed = r[decode.rt];
        r[decode.rd] = reg_signed>>r[decode.rs]
        }
        else{
          //报错
        }

        case 0b101011:
        //SLTU
        if(r[decode.rs]<r[decode.rt]){
          r[decode.rd] = 1;
        }
        else{
          r[decode.rd] = 0;
        }
        break;

        case 0b101010:
        //SLT
        int rs_tmp = r[decode.rs];
        int rt_tmp = r[decode.rt];

        if(rs_tmp<rt_tmp){
          r[decode.rd] = 1;
        }
        else{
          r[decode.rd] = 0;
        }
        break;

        case 0b011001:
        //MULTU
        hilo = r[decode.rs]*r[decode.rt];
        hi = hilo>>32;
        lo = hilo<<32>>32;
        break;

        case 0b01000:
        //MULT
        int rs_tmp = r[decode.rs];
        int rt_tmp = r[decode.rt];

        hilo = rs_tmp*rt_tmp;
        hi = hilo>>32;
        lo = hilo<<32>>32;
        break;

        case 0b011011:
        //DIVU
        hi = r[decode.rs]%r[decode.rt];
        lo = r[decode.rs]/r[decode.rt];
        break;

        case 0b011010:
        //DIV
        int rs_tmp = r[decode.rs];
        int rt_tmp = r[decode.rt];
        hi = rs_tmp%rt_tmp;
        lo = rs_tmp/rt_tmp;
        break;

        case 0b010000:
        //MFHI
        r[decode.rd] = hi;
        break;

        case 0b010010:
        //MFLO
        r[decode.rd] = lo;
        break;

        case 0b010001:
        //MTHI
        hi = r[decode.rs];
        break;

        case 0b010011:
        //MTLO
        lo = r[decode.rs];
        break;

        case 0b001000:
        //JR
        count = r[decode.rs];
        pc = &memory[count];
        break;

        case 0b001001:
        //JALR
        break;


        default:
        exit(-20);
      }

    }
}
