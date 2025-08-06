#include "assignment5.h"
#include <iterator>
#include <fstream>
#include <stdexcept>
#include <algorithm> 
#include <string>  



// Task 1
/* 
    Write a function that opens a file (one word per line) and copies all words into an empty WordVec using std::copy
        - Open a file 
            - use std::ifstream 
            - handle file open errors by throwing std::runtime_error
            - use the istream iterator to define the begin and end 
        - extract the one word per file 
        - copy each word per line into a WordVec using ::copy 
            std::copy(begin, end, std::back inserter(words vector));.
            - return the words_vector 
*/

WordVec read_words_into_vector(const std::string& file_name) { 
    // function implementation     
    std::ifstream file(file_name); 

    if(!file) { 
         throw std::runtime_error("Failed to open the file.");
    }

    WordVec words_vector; 

    std::istream_iterator<std::string> begin(file); 
    std::istream_iterator<std::string> end; 

    // copy from stream into vector
    std::copy(begin, end, std::back_inserter(words_vector));

    return words_vector; 


}


// Task 2
/* 
   Counting word occurrences and inserting them into a map using for each lambda 
     -  iterate over using each 
     - using a lambda function to add the instance to the map object 
*/
WordMap map_and_count_words_using_lambda(const WordVec& wVec) {
    WordMap wMap;
    std::for_each(wVec.begin(), wVec.end(), 
                  [&wMap](const std::string& word) { ++wMap[word]; });
    return wMap;
}


// Task 3

/* 
    Counting word occurrences and inserting them into a map using for each functor 
     -  iterate over using each 
     - using a functor function to add the instance to the map object 
        - create a class to call the functor 
        - use the same class to keep track using a member state to keep track of the number of instances
        - return the map 
*/

class WordCountFunctor {
private:
    WordMap wMap;
public:
    void operator()(const std::string& word) {
        ++wMap[word];
    }
    WordMap getMap() const { return wMap; }
};

WordMap map_and_count_words_using_functor(const WordVec& wVec) {
    WordCountFunctor wcf;
    wcf = std::for_each(wVec.begin(), wVec.end(), wcf);
    return wcf.getMap();
}