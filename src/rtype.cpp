#include<iostream>
#include<stdint.h>
#include<stdlib.h>
#include "rtype.hpp"
#include "comop.hpp"

using namespace std;

void r_type(int32_t (&r)[32], uint32_t ins,uint32_t *ins_mem,uint8_t *data_mem,
            int32_t &hi,int32_t &lo,
            uint32_t &pc, uint32_t &count){

  rtype decode;
  decode.rs = ins<<6>>27;
  //decode.rs = ins & (0x3F);
  //<<"decode.rs: "<<decode.rs<<endl;
  decode.rt = ins<<11>>27;
  //<<"decode.rt: "<<decode.rt<<endl;
  decode.rd = ins<<16>>27;
  //<<"decode.rd: "<<decode.rd<<endl;
  decode.shamt = ins<<21>>27;
  //<<"decode.shamt: "<<decode.shamt<<endl;
  decode.func = ins<<26>>26;
  //<<"decode.func"<<decode.func<<endl;

  if(decode.shamt!=0){
   //Shift amount is not zero
    switch (decode.func) {

      case 0b000000:{
      //SLL shift left logical
        //<<"sll: "<<endl;
        uint32_t tmp_rt = r[decode.rt];
        r[decode.rd] = tmp_rt<<decode.shamt;
        //<<"tmp_rt is "<<tmp_rt<<endl;
        //<<"shamt is "<<decode.shamt<<endl;
        //<<"rd inside sll is "<<r[decode.rd]<<endl;
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
           int64_t tmp1 = r[decode.rs];
           int64_t tmp2 = r[decode.rt];
           int64_t test = tmp1+tmp2;

          if(test>=-2147483648&&test<=2147483647){
            r[decode.rd] = r[decode.rs]+r[decode.rt];
          }
          else{
            exit(-10);
          }

          count++;
          pc=pc+4;}
        break;

        case 0b100010:{
        //sub
          int64_t tmp1 = r[decode.rs];
          int64_t tmp2 = r[decode.rt];
          int64_t test = tmp1-tmp2;

          if(test>=-2147483648&&test<=2147483647){
            r[decode.rd] = r[decode.rs]-r[decode.rt];
          }
          else{
            exit(-10);
          }

          count++;
          pc=pc+4;}
        break;

        case 0b100001:{
        //addu
          r[decode.rd] = (unsigned int)r[decode.rs]+(unsigned int)r[decode.rt];
          count++;
          pc=pc+4;}
        break;

        case 0b100011:{
        //subu
          r[decode.rd] = (unsigned int)r[decode.rs]-(unsigned int)r[decode.rt];
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
          //<<"sllv: "<<endl;
          r[decode.rd] = r[decode.rt]<<r[decode.rs];
          //<<"rt is "<<r[decode.rt]<<endl;
          //<<"rs is "<<r[decode.rs]<<endl;
          //<<"rd is "<<r[decode.rd]<<endl;
          count++;
          pc=pc+4;}
        break;

        case 0b000110:{
        //srlv
          uint32_t tmp_rt = r[decode.rt];
          r[decode.rd] = tmp_rt>>r[decode.rs];
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
          uint32_t tmp_rs = r[decode.rs];
          uint32_t tmp_rt = r[decode.rt];

          if(tmp_rs<tmp_rt){
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

          if(r[decode.rs]<r[decode.rt]){
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

          uint64_t a = (unsigned int)r[decode.rs];
          uint64_t b = (unsigned int)r[decode.rt];

          int64_t hilo = a*b;
          hi = (int64_t)(hilo>>32);
          lo = (int64_t)(hilo<<32>>32);

          count++;
          pc=pc+4;}
        break;

        case 0b011000:{
        //MULT
          uint64_t a = (int)r[decode.rs];
          uint64_t b = (int)r[decode.rt];
          int64_t hilo = a*b;
          //cout<<hilo<<endl;
          hi = hilo>>32;
          lo = hilo<<32>>32;

          count++;
          pc=pc+4;}
        break;

        case 0b011011:{
        //DIVU
          if(r[decode.rt] == 0){
            count++;
            pc=pc+4;
            return;
          }
          else{
            hi = ((unsigned int)r[decode.rs])%((unsigned int)r[decode.rt]);
            lo = ((unsigned int)r[decode.rs])/((unsigned int)r[decode.rt]);
          }

          count++;
          pc=pc+4;}
        break;

        case 0b011010:{
        //DIV
          if(r[decode.rt] == 0){
            count++;
            pc=pc+4;
            return;
          }
          else{
            hi = r[decode.rs]%r[decode.rt];
            lo = r[decode.rs]/r[decode.rt];
          }

          count++;
          pc=pc+4;}
        break;

        case 0b010000:{
        //MFHI
          //cout<<"hi in MFHI is "<<hi<<endl;
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

          compare_op(r, ins_mem[count+1], ins_mem, data_mem, hi, lo, pc, count);

          uint32_t addr = r[decode.rs];
          if(addr==0){
            pc = addr;
            return;
          }
          else{
            if((addr>=0x10000000&&addr<=0x11000000)&&(addr%4==0)){
              pc = addr;
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

          r[decode.rd] = pc+8;
          compare_op(r, ins_mem[count+1], ins_mem, data_mem, hi, lo, pc, count);

          if(r[decode.rs]==r[decode.rd]){
            exit(-12);
          }

          int addr = r[decode.rs];

          if((addr>=0x10000000&&addr<=0x11000000)&&(addr%4==0)){
            pc = addr;
            count =(pc-0x10000000)>>2;
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
}
