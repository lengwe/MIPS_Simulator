#include<iostream>
#include<stdio.h>
#include<fstream.h>
#include<cstdlib>
#include<fstream>s
#include<vector>
using namespace std;

typedef unsigned int uint6_t[6];
typedef unsigned int uint5_t[5];
typedef unsigned int uint26_t[26];
typedef unsigned int uint28_t[28];
typedef int int18_t[18];


uint32_t r[32];
uint32_t memory[0x1FFFFFFF];
const r[0] = 0;
uint64_t hilo;
unsigned int hi,lo;
uint32_t data;
int* pc;
uint32_t *mem_add = NULL;
uint32_t *data_reg = NULL;
unsigned int count  = 0;

void simulate(&input_bin);
void compare_op(uint32_t reg);
void i_type(uint32_t reg);
void r_type(uint32_t reg);
void j_type(uint32_t reg);

struct rtype {
  uint6_t opcode, func;
  uint5_t rs,rt,rd,shamt;
};

struct itype{
  uint6_t opcode;
  uint5_t rs,rt;
  uint16_t ai;
  int16_t sai;
};

struct jtype{
  uint6_t opcode;
  uint26_t target;
};


void simulate(&input_bin){
  memory[count] = &input_bin;
  pc = &memory[count];//default
  data = *pc;

  //ALU
  compare_op(data);
}
//判断opcode
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

int main(int argc, char*argv[]){

  ifstream binstream;
  std::string filename = argv[1];
  binstream.open(filename, ios_base::binary|ios_base::in|ios_base::ate);
  if(!binstream.is_open()){
    cout<<"not valid"<<endl;
    exit(EXIT_FAILURE);
  }

  size_t size = binstream.tellg();
  binstream.seekg(0,ios::beg);
  std::vector<char> buffer;
  buffer.resize(size);
  binstream.read(input_buffer.data(),size);

  simulate(&input_buffer);

  exit(0);
}
