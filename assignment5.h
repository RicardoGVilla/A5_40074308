
#ifndef ASSIGNMENT5_H
#define ASSIGNMENT5_H


// Type aliases
using WordVec = std::vector<std::string>;
using WordList = std::list<std::string>;
using WordMap = std::map<std::string, size_t>;



// Task 1 Using std::copy to Extract Words from File
WordVec read_words_into_vector(const std::string& file_name);

// Task 2: Counting Word Occurrences with Lambda
WordMap map_and_count_words_using_lambda(const WordVec& wVec);


// Task 3: Counting Word Occurrences with Functor
WordMap map_and_count_words_using_functor(const WordVec& wVec);


#endif // ASSIGNMENT5_H