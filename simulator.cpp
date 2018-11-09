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

typedef unsigned int uint28_t[28];
typedef int int18_t[18];

uint32_t r[32];
//uint32_t memory[0x1FFFFFFF];
uint *ins_mem = new uint32_t[0x1000000];
uint *data_mem =  new uint32_t[0x4000000];
const r[0] = 0;

uint64_t hilo;
unsigned int hi,lo;

int *pc = ins_mem[0];
int *ptr_data = data_mem[0];
//int* pc = memory[0];
//uint32_t *mem_add = NULL;
//uint32_t *data_reg = NULL;


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
