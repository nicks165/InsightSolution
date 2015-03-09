#ifndef __PROCESSTEXT_H__
#define __PROCESSTEXT_H__
#include <vector>
#include <string.h>
#include <map>
#include <queue>
#include <list>

//It does not need an instance. It is just a utility class.
class TextProcessor{

public: 
   std::vector<std::string> Tokenizer(std::string &line, std::vector<char>& delims); //split the words on delimiters, tokenize words.
   std::string toLowercase(std::string &data); //converts strings to lowercase.
   std::string concateDelimWords(std::string &words, char delim);
   //given two words seperateed by delimeter it concatenate it. It is here for making a hyphened word a single word.
   std::vector<char> getStandardDelims();
private:
   void split(std::string& s, char delim, std::vector<std::string> & elems);
   std::string concateWords(std::vector<std::string> &elems);
   std::vector<std::string> TokenizeLine(std::vector<std::string> &lines, char delim);
 
};

class Counter {
public:
   void updateWordCount(std::vector<std::string> &data);
   void displayTable();
   void writeToFile(const char* path);
private:
  //map, hashtable
   std::map<std::string, int> hTable;
};

class WordGenerator{
public:
   WordGenerator();
   ~WordGenerator();
   void ReadFile(const char* filename);
   void WriteToFile(const char* filename);
   void displayData();
   void updateWordCount(std::string& line); 
private:
   Counter *ct;
};

struct compare  
{  
   bool operator()(const double& l, const double& r)  
   {  
      return l > r;  
   }  
};

class Median {
public:
   void updateMedianForLine(std::string& line);
   double calculateMedian(double elem);
   void displayData();
   void readFile(const char* path);
   void processdir(const char* ipath, const char* opath);
   void writeToFile(const char* path);
   void updateMedian(int numelem);
private:
   int Signum(int a, int b);
   bool Greater(double a, double b);
   bool Smaller(double a, double b);
   double Average(double a, double b);
private:
   
  //map, hashtable
   double currmed;
   std::vector<double> runningMedian;
   std::priority_queue<double,std::vector<double>, compare > minHeap;
   std::priority_queue<double> maxHeap;
};
#endif// __PROCESSTEXT_H__
