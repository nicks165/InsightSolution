#include <iostream>
#include "ProcessTextLib.h"
#include <string>
#include <dirent.h>
#include <list>
using namespace std;

bool myCompare(string a, string b) { 
   return (a <b); 
}

int main(int argc, char** argv) {
   
   if(argc < 2)
      std::cerr<<" Invalid Invocation "
         "Need to Specify both Input output directory "
         "my_running_median ./wc_input/ ./wc_output/med_result.txt "<<endl;
  
   //get the directory path.
   const char* ipath = argv[1];
   
   //get the path of the result
   const char* opath = argv[2]; 
   
   // get each file from directory and send it for reading 
   DIR *pDIR;

   //create instance of median class.
   Median md; 
   struct dirent *entry;
   std::list<string> files;

   std::cout<< "Calculating Running Median of words on files " << endl;

   if( pDIR = opendir(ipath) ) {
      while(entry = readdir(pDIR)) { //if the file is valid.
         if( strcmp(entry->d_name, ".") != 0 && 
             strcmp(entry->d_name, "..") != 0 ) {

            files.push_back(entry->d_name);
         }
      }

      //sort the files in the directory.
      files.sort();

      //keep the output file open for streaming in the running median directly in file.
      md.writeRunningMedToFile(opath);

      //std::sort(files.begin(), files.end(), myCompare);
      for(list<string>::iterator it = files.begin(); it != files.end();
          ++it) {
         
         std::string filename = std::string(ipath) + *it;
         //Do processing of each file for updating the median.
         md.ProcessFileAndUpdateMedian(filename.c_str()); 
      }

      closedir(pDIR);
   }
}
