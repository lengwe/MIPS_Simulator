#include<iostream>
#include<cstdlib>
#include<stdint.h>
#include<stdlib.h>
#include<fstream>
#include<string>
#include "jtype.hpp"
#include "rtype.hpp"
#include "itype.hpp"
#include "comop.hpp"
using namespace std;


int main(int argc, char*argv[]){

  int32_t r[32] = {0};
  uint32_t *ins_mem = new uint32_t[0x1000000>>2]();
  uint8_t *data_mem =  new uint8_t[0x4000008]();

  int32_t hi,lo;

  uint32_t pc = 0x10000000;
  uint32_t count  = 0;

  ifstream binstream;
  string filename = argv[1];
  binstream.open(filename, ios::binary|ios::in|ios::ate);
  if(!binstream.is_open()){
    cout<<"not valid"<<endl;
    exit(-21);
  }

  uint32_t len = binstream.tellg();
  if(len==0||(len%4!=0)){
    cout<<"invalid binary file"<<endl;
    exit(-21);
  }

  binstream.seekg(0,ios::beg);
  char* memblock = new char [len];
  binstream.read(memblock,len);

  binstream.close();

  uint32_t a,b,c,d;

  for(int i=0;i<=(len/4);i++){

      a = memblock[i*4];
      b = memblock[1+i*4];
      c = memblock[2+i*4];
      d = memblock[3+i*4];

      ins_mem[i]=(a<<24)+(b<<16)+(c<<8)+d;

  }


   while(count<len/4){

      //  r[1] = 1;
      //  cout<<"rs:"<<r[1]<<endl;
      //  r[2] = 1;
      //  cout<<"rt:"<<r[2]<<endl;
      //  r[3] = 3;
      // ins_mem[0] = 0b00000000000000000000000000000001;
      compare_op(r, ins_mem[count], ins_mem, data_mem, hi, lo, pc, count);
      // cout<<count<<endl;
      // cout<<pc<<endl;
      // cout<<"rd:"<<r[3]<<endl;
    }
  delete[]memblock;

  uint8_t finish = r[2]<<24>>24;
  exit(finish);
}
