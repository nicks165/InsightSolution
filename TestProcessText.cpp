#include <iostream>
#include "ProcessText.h"
#include <string>
#include <vector>
using namespace std;

void TestTokenizer() {
   string str = "123 Abc";
   TextProcessor Tp;
   std::cout<< Tp.toLowercase(str) <<std::endl;
   string str2 = "abc-abc";
   std::cout<< Tp.concateDelimWords(str2, '-') <<std::endl;
   string text = "anuruPa sa:rMa,anx        anu anu anu";
   vector<char> delims;
   delims.push_back(' ');
   delims.push_back(':');
   delims.push_back(',');
   vector<string> vec = Tp.Tokenizer(text, delims);
   for(vector<string>::iterator it = vec.begin(); it != vec.end(); ++it) {
      cout<<*it<<endl;
   }
}
void TestCounter() {
   TextProcessor Tp;
   string test = " ancAN :abb, fd   fd fd gui gui";
   vector<char> delims;
   delims.push_back(' ');
   delims.push_back(':');
   delims.push_back(',');
   std::vector<string> str = Tp.Tokenizer(test, delims);
   Counter ct;
   ct.updateWordCount(str);
   ct.displayTable();
}
int main(int argc, char** argv) {
   WordGenerator fd;
   if(argc < 2)
      std::cerr<<" Input file not present! "<<endl;
   const char* ipath = argv[1];
   const char* opath = argv[2];
   cout << ipath << "\t" << opath  <<endl;
   fd.ProcessDir(ipath,opath);
   //fd.ReadFile(path);

}
