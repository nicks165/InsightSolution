#ifndef __PROCESSTEXT_H__
#define __PROCESSTEXT_H__
#include <vector>
#include <string.h>
#include <map>
#include <queue>
#include <list>
#include <fstream>

/*
  It is a utility class for doing basic string processing like tokenizing, splitting by using some standard delimetes, making a word to lowercase etc.
 */

class TextProcessor {

public: 
   //split the words on delimiters provided and then tokenize words.
   std::vector<std::string> Tokenizer(std::string &line, 
                                      std::vector<char>& delims); 
   //converts strings to lowercase.
   std::string toLowercase(std::string &data); 

   //given two words seperateed by delimeter it concatenates it. 
   //It is present here for making a hyphened word a single word. 
   std::string concateDelimWords(std::string &words, char delim);
   
   //Kept a standard list of delimeters. We can update it as per our need.
   std::vector<char> getStandardDelims();

private:
   //Toeknizer calls this. This is used for actual splititng each sentence or words on the given delimeter.
   void split(std::string& s, char delim, std::vector<std::string> & elems);

   std::string concateWords(std::vector<std::string> &elems);
   
   std::vector<std::string> TokenizeLine(std::vector<std::string> &lines, char delim);
 
};

/* A word counter class which will keep a count of all the unique words streamed to it.
*/

class WordCounter {

public:
   WordCounter();
   ~WordCounter();
   void ProcessFileAndUpdateCount(const char* filename);
   void WriteCountToFile(const char* filename);
   void displayData();
   
private:
   void updateWordCount(std::string& line); 
   void updateWordCount(std::vector<std::string> &data);

private:
   //map, hashtable
   std::map<std::string, int> *hTable;
};


/* Class to calculate the running median of a stream of words specially from a file.
*/
struct compare { //comparision for min heap used in median class.
   bool operator()(const double& l, const double& r) {
      return l > r;
   }
};

class Median {

public:
  
   //This is the main method called which will mostly process stream of data and update the median.
   void ProcessFileAndUpdateMedian(const char* path);
   void writeRunningMedToFile(const char* path);


private:
   void updateMedian(int numelem);
   //Updates the median for each line read from a file.
   void updateMedianForLine(std::string& line);

   // main algorithm which calculates the median. Used min heap and max heap approach to calculate median.
   double calculateMedian(double elem);

   //Utility functions for calculating median.
   int Signum(int a, int b);
   bool Greater(double a, double b);
   bool Smaller(double a, double b);
   double Average(double a, double b);

private:
  //map, hashtable
   double currmed;
   std::priority_queue<double,std::vector<double>, compare > minHeap;
   std::priority_queue<double> maxHeap;
   std::ofstream myRunningMedFile;
};
#endif// __PROCESSTEXT_H__
