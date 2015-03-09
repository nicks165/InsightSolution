# InsightSolution
Word counter and Median generator

Language : C++
Developed and test using g++ on Suse Linux  

This repo contains the classes and sample input/output files to parse a set of input files in directory (e.g. "wc_input") and output
two result files in the output directory (e.g. "wc_output") -
1) wc_result.txt : Contains alphabatically sorted word to number of occurences per line.
2) med_result.txt : Contains the running median of the number of words per line in all the files in the input directory when 
parsed in alphabetical order.

System requirements - 
C++ compiler, preferably g++ on a linux environment

To compile -
g++ my_word_count.cpp ProcessText.cpp -o my_word_count
g++ my_running_median.cpp ProcessText.cpp -o my_running_median

To execute -
chmod a+x my_word_count
my_word_count ./wc_input/ ./wc_output/wc_result.txt

chmod a+x my_running_median
my_running_median ./wc_input/ ./wc_output/med_result.txt

where, the input params are the input directory and the resulting output file respectivily.

Design -

Word counter : 
The my_word_count.cpp is the main entry point for word counter. It iterates through the input files in the input directory
one by one and sends them to the WordCounter for processing. The WordCounter reads a line and tokenizes the line accorsing to a list
of acceptable dimiliters like ' ', ':', ',', '.', '/', \\', ';'.
The tokeized words are then sent to a counter to maintains a ordered map of the work to occurence mapping.

Running Median:
The my_running_median.cpp is the main entry point for calculating running median. It iterates through the input files in the input directory
one by one and sends them to the WordCounter for processing. The WordCounter reads a line and tokenizes the line accorsing to a list
of acceptable dimiliters like ' ', ':', ',', '.', '/', \\', ';'.
The tokeized words are then sent to a counter to maintains a ordered map of the work to occurence mapping.
