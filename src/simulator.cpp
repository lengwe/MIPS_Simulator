#include<iostream>
#include<sys/stat.h>
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
    cerr<<"not valid"<<endl;
    exit(-21);
  }

  uint32_t len = binstream.tellg();

  if(len==0||(len%4!=0)){
    cerr <<"invalid binary file"<<endl;
    exit(-21);
  }

  binstream.seekg(0,ios::beg);
  char *memblock = new char [len]();
  binstream.read(memblock,len);


  uint32_t a,b,c,d;

  a=0;
  b=0;
  c=0;
  d=0;

  for(int i=0;i<(len/4);i++){

      a = memblock[i*4];
      b = memblock[1+i*4];
      c = memblock[2+i*4];
      d = memblock[3+i*4];

      ins_mem[i]=(a<<24)+(b<<24>>8)+(c<<24>>16)+(d<<24>>24);
  
  }

  // cerr << "print ins memory" << '\n';
  // for (int i=0;i<20;i++){
  //   cerr << hex << ins_mem[i] << '\n';
  // }


   while(pc!=0){
        compare_op(r, ins_mem[count], ins_mem, data_mem, hi, lo, pc, count);

      }
  delete[]memblock;
  uint8_t finish = r[2]<<24>>24;
  exit(finish);
}
