#include <iostream>
#include "ProcessText.h"
#include <string>
#include <vector>
#include <dirent.h>
using namespace std;

int main(int argc, char** argv) {
   
   if(argc < 2)
      std::cerr<<" Input file not present! "<<endl;
  
   const char* ipath = argv[1]; //get the directory path.
   const char* opath = argv[2]; //get the path of the result
   //   cout << ipath << "\t" << opath  <<endl;
   /* get each file from directory and send it for reading */
   DIR *pDIR;
   WordGenerator wd; //create word generator object.
   struct dirent *entry;
   if( pDIR=opendir(ipath) ){
      while(entry = readdir(pDIR)){
         if( strcmp(entry->d_name, ".") != 0 && 
             strcmp(entry->d_name, "..") != 0 ) { //if input file is valid.
            std::cout << entry->d_name << "\n";
            std::string filename = std::string(ipath) + entry->d_name;
            wd.ReadFile(filename.c_str()); //read the input file and generate word count. store it in  atable
         }
      }
      //      wd.displayData(); //display the word count.
      wd.WriteToFile(opath); //write it to a theoutput file.
      closedir(pDIR);
   }

}
