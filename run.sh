#!/usr/bin/env bash

#example of the run script for running the word count

# first I'll load all my dependencies
apt-get install g++
# next I'll make sure that all my programs (written in c++ in this example) have the proper permissions
chmod a+x my_word_count.cpp
chmod a+x my_running_median.cpp
chmod a+x ProcessTextLib.h
chmod a+x ProcessTextLib.cpp
# finally I'll execute my programs, with the input directory wc_input and output the files in the directory wc_output
g++ my_word_count.cpp ProcessTextLib.cpp -o my_word_count
chmod a+x my_word_count
my_word_count ./wc_input/ ./wc_output/wc_result.txt
g++ my_running_median.cpp ProcessTextLib.cpp -o my_running_median
chmod a+x my_running_median
my_running_median ./wc_input/ ./wc_output/med_result.txt


