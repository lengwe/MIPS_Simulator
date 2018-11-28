#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>

using namespace std;


struct output{

      string id;
      string instruction;
      string status;
      string author;
      string print(){
      return output::id+","+instruction+","+status+","+author;
      }

};


int main(int argc, char* argv[]){

   vector<output> csv;
   vector<string> ref;
   vector<string> testout;

   ifstream incsv(argv[1]);
   if(!incsv.is_open()){
     cerr<<"failed to open csv file"<<endl;
     exit(EXIT_FAILURE);
   }

   ifstream reference(argv[2]);
   if(!reference.is_open()){
     cerr<<"failed to open reference.txt"<<endl;
     exit(EXIT_FAILURE);
   }

   ifstream testoutput(argv[3]);
   if(!testoutput.is_open()){
     cerr<<"failed to open testoutput.txt"<<endl;
     exit(EXIT_FAILURE);
   }


   output tempcsv;
   string tmp;

   while(incsv>>tempcsv.id,incsv>>tmp,
         incsv>>tempcsv.instruction,incsv>>tmp,
         incsv>>tempcsv.status,incsv>>tmp,
         incsv>>tempcsv.author){

       csv.push_back(tempcsv);
   }

   while(reference>>tmp){
     ref.push_back(tmp);
   }

   while(testoutput>>tmp){
     testout.push_back(tmp);
   }


   ofstream myfile;
   myfile.open("testoutput.csv");

   for(int i=0;i<csv.size();i++){

    if(testout[i]==ref[i]){
           csv[i].status ="pass";
    }
    else{
        csv[i].status = "fail";
    }

    cout<<csv[i].print()<<endl;

    myfile<<csv[i].id<<","<<csv[i].instruction<<","<<csv[i].status<<","<<csv[i].author<<endl;


   }




 return 0;
}
