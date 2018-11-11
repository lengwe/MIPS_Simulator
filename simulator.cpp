#include<iostream>
#include<stdio.h>
#include<fstream.h>
#include<cstdlib>
#include<fstream>
#include<vector>
#include "jtype.hpp"
#include "rtype.hpp"
#include "itype.hpp"
using namespace std;

uint32_t r[32];
uint *ins_mem = new uint32_t[0x1000000];
uint *data_mem =  new uint8_t[0x4000000];

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

  size_t size = binstream.tellg();
  binstream.seekg(0,ios::beg);
  std::vector<uint32_t> buffer;
  buffer.resize(size);
  binstream.read(buffer.data(),size);

  //simulate(&buffer);

  exit(0);
}
