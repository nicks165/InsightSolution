#include <iostream>
#include "ProcessText.h"
#include <string>
#include <vector>
#include <algorithm>
#include <dirent.h>
#include <list>
using namespace std;

bool myCompare(string a, string b) { return (a <b); }
int main(int argc, char** argv) {
   
   if(argc < 2)
      std::cerr<<" Input file not present! "<<endl;
  
   const char* ipath = argv[1]; //get the directory path.
   const char* opath = argv[2]; //get the path of the result
   //   cout << ipath << "\t" << opath  <<endl;
   /* get each file from directory and send it for reading */
   DIR *pDIR;
   Median md; //create word generator object.
   struct dirent *entry;
   std::list<string> files;
   if( pDIR=opendir(ipath) ){
      while(entry = readdir(pDIR)){ //if the file is valid.
         if( strcmp(entry->d_name, ".") != 0 && 
             strcmp(entry->d_name, "..") != 0 ) {
            //std::cout << entry->d_name << "\n";
            files.push_back(entry->d_name);
         }
      }
      files.sort();
      //std::sort(files.begin(), files.end(), myCompare);
      for(list<string>::iterator it = files.begin(); it != files.end();
          ++it) {
         //cout<< *it <<endl;
         std::string filename = std::string(ipath) + *it;
         md.readFile(filename.c_str()); 
      }
      md.writeToFile(opath);
      //md.displayData();
      closedir(pDIR);
   }
}
