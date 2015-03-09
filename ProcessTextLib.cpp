#include <algorithm>
#include <iostream>
#include <functional>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <string>
#include <iomanip>
#include "ProcessTextLib.h"

//memeber functions of textprocessor class

std::string
TextProcessor::toLowercase(std::string& data) {

   std::string result; 
   std::transform(data.begin(), data.end(), data.begin(), ::tolower);
   return data;
}

std::string
TextProcessor::concateWords(std::vector<std::string>& elems) {

   std::string result;
   for(std::vector<std::string>::iterator it = elems.begin(); it != elems.end(); ++it) {
      result += *it;
   }
   return result;
}
std::string
TextProcessor::concateDelimWords(std::string & word, char delim) {

   std::stringstream ss(word);
   std::string item, result;
   std::vector<std::string> elems;
   while(std::getline(ss, item, delim)) {
      elems.push_back(item);
   }
   if(elems.size() > 1)
      result = concateWords(elems);
   return result;
}

void
TextProcessor::split(std::string &s, char delim, std::vector<std::string>& elems) {
   std::stringstream ss(s);
   std::string item;
   while(std::getline(ss, item, delim)) {
      
      elems.push_back(item);
   }
}
 
std::vector<std::string>  
TextProcessor::TokenizeLine(std::vector<std::string> &text, char delim) {

   std::vector<std::string> elems;
   for(std::vector<std::string>::iterator it= text.begin(); it!= text.end(); ++it) {
      split(*it,delim, elems);
      
   }
  
   return elems;
}

std::vector<std::string>
TextProcessor::Tokenizer(std::string& line, std::vector<char>& delims) {

   std::vector<std::string> inputseed;
   inputseed.push_back(line);
   std::vector<std::string> results;
   for(std::vector<char>::iterator it = delims.begin(); it != delims.end(); ++it) {
      results = TokenizeLine(inputseed, *it);
      inputseed.clear();
      inputseed= results;
   } 
   
   return results;
}
std::vector<char> 
TextProcessor::getStandardDelims() {

   std::vector<char> delims;
   delims.push_back(' ');
   delims.push_back(':');
   delims.push_back(',');
   delims.push_back('.');
   delims.push_back('/');
   delims.push_back('\\');
   delims.push_back(';');
   return delims;
}

//member fucntions word generator class
WordCounter::WordCounter() {
   
   hTable = new std::map<std::string, int >();
}

WordCounter::~WordCounter() {

   if(hTable != NULL)
      delete hTable;
}

void 
WordCounter::updateWordCount(std::vector<std::string> &data) {
   
   std::map<std::string, int>::iterator tableIt;

   for(std::vector<std::string>::iterator it = data.begin(); it != data.end(); ++it) {
      tableIt = hTable->find(*it);
      if(tableIt == hTable->end()) {
         hTable->insert(std::pair<std::string, int>(*it, 1) );
      }
      else
         (*hTable)[*it] +=1;
   }
}

void
WordCounter::updateWordCount(std::string& line) {
   
   std::vector<char> delims;
   TextProcessor Tp;
   delims = Tp.getStandardDelims();
   std::vector<std::string> tokens = Tp.Tokenizer(line, delims);
   for(std::vector<std::string>::iterator it = tokens.begin();
       it != tokens.end(); ++it) {
      Tp.toLowercase(*it);
   }
   updateWordCount(tokens);
}

void 
WordCounter::ProcessFileAndUpdateCount(const char* filename) {
   
   std::ifstream myfile (filename);
   std::string line;
   if(myfile.is_open ()) {
      while( getline(myfile, line) ) {
         //std::cout<<line <<std::endl;
         updateWordCount(line);
      }
      myfile.close();
   }
   else
      std::cout<<"Cannot open file!" << filename << std::endl;
   return;
}

void
WordCounter::WriteCountToFile(const char* filename) {
   
   std::ofstream myfile(filename);
   
   if (myfile.is_open()) {
      for(std::map<std::string, int>::iterator it = hTable->begin(); it != hTable->end(); ++it) {
        std::pair<std::string, int> mPair = *it;
        //std::cout<< mPair.first <<"\t" << mPair.second <<"\n";
        myfile << mPair.first <<"\t" << mPair.second << "\n";
      }
   }
   else
      std::cerr<<"cannot write to file "<< filename << std::endl;
}

void
WordCounter::displayData() {

   for(std::map<std::string, int>::iterator it = hTable->begin(); it != hTable->end(); ++it) {
      std::pair<std::string, int> mPair = *it;
      std::cout<< mPair.first << "\t" << mPair.second << std::endl;
   }
}

//member functions of median class
int 
Median::Signum(int a, int b) {
   
   if( a == b )
        return 0;
 
    return a < b ? -1 : 1;
}

// Greater and Smaller are used as comparators
bool 
Median::Greater(double a, double b) {
   
   return a > b;
}
 
bool 
Median::Smaller(double a, double b) {

    return a < b;
}
 
double 
Median::Average(double a, double b) {

    return (a + b) / 2;
}

double
Median::calculateMedian(double e) {

   if(maxHeap.size() == 0 && minHeap.size() ==0)
      currmed = (double)e;
   int sig = Signum(maxHeap.size(), minHeap.size());
   switch(sig) {
   case 1: // There are more elements in max heap
      
      if( e < currmed ) // current element fits in max heap
         {
            // Remore top element from max heap and
            // insert into min heap
            minHeap.push(maxHeap.top());
            maxHeap.pop();
            // current element fits in max heap
            maxHeap.push(e);
         }
        else
           {
              // current element fits in min heap
              minHeap.push(e);
           }
 
      // Both heaps are balanced
      currmed = Average(maxHeap.top(), minHeap.top());
      
      break;
   case 0: // The max and min heaps contain same number of elements
      
    if( e < currmed ) // current element fits in max heap
       {
          maxHeap.push(e);
          currmed = maxHeap.top();
       }
    else
       {
          // current element fits in min heap
          minHeap.push(e);
          currmed = minHeap.top();
       }
    
    break;
   case -1: // There are more elements in min heap
      
    if( e < currmed ) // current element fits in max heap
       {
          maxHeap.push(e);
       }
    else
       {
          // Remove top element from min heap and
          // insert into max heap
          maxHeap.push(minHeap.top());
          minHeap.pop();
 
          // current element fits in min heap
          minHeap.push(e);
       }
    
    // Both heaps are balanced
    currmed = Average(maxHeap.top(), minHeap.top());
    
    break;
   }
   return currmed;
}
 
void
Median::updateMedian(int numelem) {

   double m = calculateMedian(numelem);
   myRunningMedFile << std::setprecision(2) << m << "\n";
}

void 
Median::updateMedianForLine(std::string& line) {

   TextProcessor Tp;
   std::vector<char> delims;
   delims = Tp.getStandardDelims();
   std::vector<std::string> wrds = Tp.Tokenizer(line, delims);
   updateMedian(wrds.size());
}

void 
Median::writeRunningMedToFile(const char* filename) {

   myRunningMedFile.open(filename);
   if (myRunningMedFile.is_open()) {
      std::cout<<"Opening output file named \"" << filename << 
         "\" for streaming running median " << std::endl;
   }
}

void 
Median::ProcessFileAndUpdateMedian(const char* filename) {
   
   std::ifstream myfile (filename);
   std::string line;
   if(myfile.is_open ()) {
      while( getline(myfile, line) ) {
         //std::cout<<line <<std::endl;
         updateMedianForLine(line);
      }
      myfile.close();
   }
   else
      std::cout<<"Cannot open file!" << filename <<std::endl;
   return;
}
