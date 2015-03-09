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
of acceptable delimiters like ' ', ':', ',', '.', '/', \\', ';'.
The tokeized words are then sent to a counter to maintains a ordered map of the work to occurence mapping.

Tradeoffs - 
I optimzed for memory over processing time since this solution is supposed to run on a single machine. The ideal solution would 
have been to have multiple threads reading data from different files (total files divided among the number of threads) and 
tokenzing them independently and sending them over to the consumer threads which would would each maintain a map of words to number
of occurences. In order to facililate easy reduction, the trick would be to ensure that each word always goes to the same consumer thread.
After all the data has been read, a reduce thread would collate all the maps from invidual threads and write them to file.
This design becomes more expensive in the single server instance because of the need to maintain multiple maps and one large collated map
leading to more memory consumption (double the normal). Also, the merge of individual consumer map would have to be smart enough to  either
maintain the sort order (by assigning buckets of alphabets (become more complex to support unicode chars) to each thread and then iterate throug in order)  or sort them  after merge.

Hence, i opted to optimize for memory and simplicity, with a modular code allowing for easy refactor to a distributed scenario.
We maintian just one ordered map and iterate through the files a line at once. Have testing it on input of multiple 25GB files,
which it supports easily. since, the total number of words hardly reaches millions.

Running Median:
The my_running_median.cpp is the main entry point for calculating running median. I first capture all the files in the directory and then sort them alphabetically uppercase and then lower case. 
However i did not error check for different types of files. I assume files are mostly text files. 

After this i iterate through the sorted input files one by one and sends them to the ProcessAndUpdateMedian of Median class for processing, which reads a line at a time and tokenizes the line accordingly. 
I already have a set of acceptable delimiters like ' ', ':', ',', '.', '/', \\', ';' . I split the words/sentences according to these delimiters.
Once splitted , i collect the word count in each line and then send it for calculating median. I maintain a running median. 

I calculate the median using a min heap and max heap.
I use Max heap to represent elements that are less than running median, and a min heap to represent elements that are greater than running median.

After processing an incoming element, the number of elements in heaps differ utmost by 1 element. When both heaps contain same number of elements, i pick average of heap's root data as effective median. When the heaps are not balanced, i select effective median from the root of heap containing more elements.
