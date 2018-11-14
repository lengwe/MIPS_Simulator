#include<iostream>
#include<stdio.h>
#include<fstream.h>
#include<cstdlib>
#include<fstream>
#include<vector>
#include "jtype.hpp"
#include "rtype.hpp"
#include "itype.hpp"
#include "comop.hpp"
using namespace std;

uint32_t r[32];
uint32_t *ins_mem = new uint32_t[0x1000000];
uint8_t *data_mem =  new uint8_t[0x4000000];

uint64_t hilo;
unsigned int hi,lo;

int32_t *pc = ins_mem[0];

void initial(uint32_t &uint32_t reg[32]){
  for(int i=0;i<reg.size();i++){
    reg[i] = 0;
  }
}

int main(int argc, char*argv[]){
  //initial regfile
  initial(r[32]);

  ifstream binstream;
  std::string filename = argv[1];
  binstream.open(filename, ios_base::binary|ios_base::in|ios_base::ate);
  if(!binstream.is_open()){
    cout<<"not valid"<<endl;
    exit(EXIT_FAILURE);
  }

  int len = binstream.tellg();
  len =len -1;
  if(len==0&&len%4!=0){
    cout<<"invalid binary file"<<endl;
    exit(-21);
  }

  binstream.seekg(0);
  char b;

  for(int j=0; j<len/4;j++){
    uint32_t ins=0;
    int i=0;

    while(file.good()&&i<=3){
      file.get(b);
      ins = ins+(b<<(8*(3-i)));
      i++;
    }

    ins_mem[j]=a;
    compare_op(ins_mem[j]);
 }

  exit(0);
}
