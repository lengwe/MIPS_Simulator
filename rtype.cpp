#include<iostream>
#include<stdint.h>
#include<stdlib.h>
#include "rtype.hpp"
#include "comop.hpp"

using namespace std;

void r_type(uint32_t r[32], uint32_t ins,uint32_t *ins_mem,uint8_t *data_mem,
            uint64_t &hilo,unsigned int &hi,unsigned int &lo,
            uint32_t &pc, uint32_t &count){

  rtype decode;
  decode.rs = ins<<6>>27;
  decode.rt = ins<<11>>27;
  decode.rd = ins<<16>>27;
  decode.shamt = ins<<21>>27;
  decode.func = ins<<26>>26;

  if(decode.shamt!=0){
   //Shift amount is not zero
    switch (decode.func) {

      case 0b000000:{
      //SLL shift left logical
        uint32_t tmp_rt = r[decode.rt];
        r[decode.rd] = tmp_rt<<decode.shamt;
        count++;
        pc = pc+4;}
      break;

      case 0b000010:{
      //SRL Shift right logical
        uint32_t tmp_rt = r[decode.rt];
        r[decode.rd] = tmp_rt>>decode.shamt;
        count++;
        pc=pc+4;}
      break;

      case 0b000011:{
      //SRA Shift right arithmetic
       int32_t reg_signed = r[decode.rt];
       r[decode.rd] = reg_signed>>decode.shamt;
       count++;
       pc=pc+4;}
      break;

      default:
      exit(-12);
    }
  }

  else{
      switch (decode.func) {

        case 0b100000:{
        //add
          double tmp1 = r[decode.rs];
          double tmp2 = r[decode.rt];

          if((tmp1+tmp2)>=-2147483648||(tmp1+tmp2)<=2147483647){
            r[decode.rd] = tmp1+tmp2;
          }
          else{
            exit(-10);
          }

          count++;
          pc=pc+4;}
        break;

        case 0b100010:{
        //sub
          double tmp1 = r[decode.rs];
          double tmp2 = r[decode.rt];

          if((tmp1-tmp2)>=-2147483648||(tmp1-tmp2)<=2147483647){
            r[decode.rd] = tmp1-tmp2;
          }
          else{
            exit(-10);
          }

          count++;
          pc=pc+4;}
        break;

        case 0b100001:{
        //addu
          r[decode.rd] = r[decode.rs]+r[decode.rt];
          count++;
          pc=pc+4;}
        break;

        case 0b100011:{
        //subu
          r[decode.rd] = r[decode.rs]-r[decode.rt];
          count++;
          pc=pc+4;}
        break;

        case 0b100100:{
        //AND
          r[decode.rd] = r[decode.rs]&r[decode.rt];
          count++;
          pc=pc+4;}
        break;

        case 0b100101:{
        //OR
          r[decode.rd] = r[decode.rs]|r[decode.rt];
          count++;
          pc=pc+4;}
        break;

        case 0b100110:{
        //XOR
          r[decode.rd] = r[decode.rs]^r[decode.rt];
          count++;
          pc=pc+4;}
        break;

        case 0b000100:{
        //sllv(min and max)
          r[decode.rd] = r[decode.rt]<<r[decode.rs];
          count++;
          pc=pc+4;}
        break;

        case 0b000110:{
        //srlv
          r[decode.rd] = r[decode.rt]>>r[decode.rs];
          count++;
          pc=pc+4;}
        break;

        case 0b000111:{
        //srav
          int32_t reg_signed = r[decode.rt];
          r[decode.rd] = reg_signed>>r[decode.rs];
          count++;
          pc=pc+4;}
        break;

        case 0b101011:{
        //SLTU
          if(r[decode.rs]<r[decode.rt]){
            r[decode.rd] = 1;
          }
          else{
            r[decode.rd] = 0;
          }

          count++;
          pc=pc+4;}
        break;

        case 0b101010:{
        //SLT
          int rs_tmp = r[decode.rs];
          int rt_tmp = r[decode.rt];

          if(rs_tmp<rt_tmp){
            r[decode.rd] = 1;
          }
          else{
            r[decode.rd] = 0;
          }

          count++;
          pc=pc+4;}
        break;

        case 0b011001:{
        //MULTU
          hilo = r[decode.rs]*r[decode.rt];
          hi = hilo>>32;
          lo = hilo<<32>>32;

          count++;
          pc=pc+4;}
        break;

        case 0b011000:{
        //MULT
          int rs_tmp = r[decode.rs];
          int rt_tmp = r[decode.rt];

          hilo = rs_tmp*rt_tmp;
          hi = hilo>>32;
          lo = hilo<<32>>32;

          count++;
          pc=pc+4;}
        break;

        case 0b011011:{
        //DIVU
          if(r[decode.rt] == 0){
            exit(-10);
          }
          else{
            hi = r[decode.rs]%r[decode.rt];
            lo = r[decode.rs]/r[decode.rt];
          }

          count++;
          pc=pc+4;}
        break;

        case 0b011010:{
        //DIV
          if(r[decode.rt] == 0){
            exit(-10);
          }
          else{
            int rs_tmp = r[decode.rs];
            int rt_tmp = r[decode.rt];
            hi = rs_tmp%rt_tmp;
            lo = rs_tmp/rt_tmp;
          }

          count++;
          pc=pc+4;}
        break;

        case 0b010000:{
        //MFHI
          r[decode.rd] = hi;

          count++;
          pc=pc+4;}
        break;

        case 0b010010:{
        //MFLO
          r[decode.rd] = lo;

          count++;
          pc=pc+4;}
        break;

        case 0b010001:{
        //MTHI
          hi = r[decode.rs];

          count++;
          pc=pc+4;}
        break;

        case 0b010011:{
        //MTLO
          lo = r[decode.rs];

          count++;
          pc=pc+4;}
        break;

        case 0b001000:{
        //JR
          if(ins_mem[count+1]==0){

            pc = r[decode.rs];
            if(pc>=0x10000000&&pc<=0x11000000){

              count =(pc-0x10000000)>>2;
            }
            else{
               exit(-11);
            }
          }

          else{

            compare_op(r, ins_mem[count+1], ins_mem, data_mem, hilo, hi, lo, pc, count);
            pc = r[decode.rs];

            if(pc>=0x10000000&&pc<=0x11000000){

              count =(pc-0x10000000)>>2;
            }
            else{
               exit(-11);
            }
          }
        }
        break;

        case 0b001001:{
        //JALR
          if(r[decode.rs]==r[decode.rd]){
            exit(-12);
          }

          if(ins_mem[count+1]==0){

            r[decode.rd] = pc+8;
            pc = r[decode.rs];

            if(pc>=0x10000000&&pc<=0x11000000){

              count =(pc-0x10000000)>>2;
            }
            else{
               exit(-11);
            }
          }
          else{

            compare_op(r, ins_mem[count+1], ins_mem, data_mem, hilo, hi, lo, pc, count);
            r[decode.rd] = pc+8;
            pc = r[decode.rs];

            if(pc>=0x10000000&&pc<=0x11000000){

              count =(pc-0x10000000)>>2;
            }
            else{
               exit(-11);
            }
          }
        }
        break;

        default:
        exit(-12);
      }

    }
}
