#include<iostream>
#include<cstdlib>
#include<fstream>
#include<string>
#include "jtype.hpp"
#include "rtype.hpp"
#include "itype.hpp"
#include "comop.hpp"
using namespace std;

uint32_t r[32];
uint32_t *ins_mem = new uint32_t[0x1000000>>2];
uint8_t *data_mem =  new uint8_t[0x4000008];
char get;

uint64_t hilo;
unsigned int hi,lo;

//int32_t *pc = ins_mem[0];
uint32_t pc = 0x10000000;
uint32_t count  = 0;

int32_t addr_getc(){

  getchar();
  if(data_mem[addr]!=EOF){

  }
  else{

  }
}

void addr_putc(int val){
  if(pc==0x30000004){
    if(val==-1||val==-2){
      exit(-21);
    }
    putchar(get);
  }
}

void initial(){
  for(int i=0;i<reg.size();i++){
    reg[i] = 0;
  }
}

int main(int argc, char*argv[]){
  //initial regfile
  initial();

  ifstream binstream;
  string filename = argv[1];
  binstream.open(filename, ios_base::binary|ios_base::in|ios_base::ate);
  if(!binstream.is_open()){
    cout<<"not valid"<<endl;
    exit(EXIT_FAILURE);
  }

  size_t len = binstream.tellg();
  if(len==0||len%4!=0){
    cout<<"invalid binary file"<<endl;
    exit(-21);
  }

  binstream.seekg(0,ios::beg);
  char* memblock = new char [len];
  binstream.read(memblock,len);

  binstream.close();

  uint32_t a,b,c,d;

  for(int i=0;i<=len/4;i++){

    if(i=len/4){
      ins_mem[i]=0;
    }
    else{
      a = memblock[i*4];
      b = memblock[1+i*4];
      c = memblock[2+i*4];
      d = memblock[3+i*4];

      ins_mem[i]=(a<<24)+(b<<16)+(c<<8)+d;
    }

//需要改
  //  int32_t val=-2;
    //val=addr_getc();
    //addr_putc(val);
  }


  while(count<len/4){
    compare_op(r[32], ins_mem[count], ins_mem, data_mem, hilo, hi, lo, pc, count);
  }
  delete[]memblock;

  uint8_t finish = r[2]<<24>>24;
  exit(finish);
}
