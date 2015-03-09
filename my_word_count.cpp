#include <iostream>
#include "ProcessTextLib.h"
#include <string>
#include <dirent.h>
using namespace std;

int main(int argc, char** argv) {
   
   if(argc < 2)
      std::cerr<<" Invalid Invocation "
         "Need to Specify both Input output directory "
               "my_word_count ./wc_input/ ./wc_output/wc_result.txt "<<endl;
  
   const char* ipath = argv[1]; //get the directory path.
   const char* opath = argv[2]; //get the path of the result

   /* get each file from directory and send it for reading */
   DIR *pDIR;
   WordCounter wCounter; //create word counter object.
   struct dirent *entry;

   cout<<"Calculating word count " << endl;

   if( pDIR = opendir(ipath) ){
      while(entry = readdir(pDIR)){
         if( strcmp(entry->d_name, ".") != 0 && 
             strcmp(entry->d_name, "..") != 0 ) { //if input file is valid.

            std::string filename = std::string(ipath) + entry->d_name;
            wCounter.ProcessFileAndUpdateCount(filename.c_str()); //read the input file and generate word count. store it in  atable
         }
      }

      wCounter.WriteCountToFile(opath); //write it to a theoutput file.
      closedir(pDIR);
   }

}
