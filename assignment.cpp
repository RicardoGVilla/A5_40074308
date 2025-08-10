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

// Task 4 

/* 
Removing duplicates from a specific vector while preserving the order of the elements
    - sort the vector
    - remove the duplicates
        -  remove starting from the last unique eleemtn to the end
    - return the new vector 
*/

WordVec remove_duplicates(const WordVec& words_vector) { 
    WordVec words = words_vector;   
    std::sort(words.begin(), words.end());
    words.erase(std::unique(words.begin(), words.end()), words.end());
    return words;
}

// Task 5
/*
    - check if the word is a palindrome
        - a word is a palindrome if it is the same forwards and backwards 
            - if the word is a palindrome, return true
            - if the word is not a palindrome, return false
    - return the result
*/

bool is_alphabetic(char c) { return std::isalpha(c); }

bool is_palindrome(const std::string& phrase) {
    std::string temp;
    std::remove_copy_if(phrase.begin(), phrase.end(), 
                       std::back_inserter(temp), 
                       [](char c) { return !is_alphabetic(c); });
    std::transform(temp.begin(), temp.end(), temp.begin(),
                  [](unsigned char c) { return std::tolower(c); });
    return std::equal(temp.begin(), temp.begin() + temp.size()/2, temp.rbegin());
}


// Task 6
/*
Count Strings by Length 
Implement three versions of counting how many strings in a WordVec have a given length n
Function prototypes:
   -  count_using_lambda
   - count_using_functor
   - count_using_free_func
*/

// count using lambda
int count_using_lambda(const WordVec& vec, int n) {
    return std::count_if(vec.begin(), vec.end(),
        [n](const std::string& word) { return word.size() == n; });
}

// functor version 
struct LengthIs {
    int n;
    LengthIs(int len) : n(len) {}
    bool operator()(const std::string& word) const {
        return word.size() == n;
    }
};

int count_using_functor(const WordVec& vec, int n) {
    return std::count_if(vec.begin(), vec.end(), LengthIs(n));
}

// free function version 
bool freeFunc(const std::string& str, int n) {
    return str.size() == n;
}

int count_using_free_func(const WordVec& vec, int n) {
    auto unaryFreeFunc = std::bind(freeFunc, std::placeholders::_1, n);
    return std::count_if(vec.begin(), vec.end(), unaryFreeFunc);
}


// Task 7 
/*
    Write a function that uses a std::multiset<std::string, MyComparator> to stored words sorted by increasing length and lexicographic order within each length
*/

// Custom comparator as a function object
struct MyComparator {
    bool operator()(const std::string& s1, const std::string& s2) const {
        if (s1.size() != s2.size())
            return s1.size() < s2.size(); // shorter comes first
        return s1 < s2; // same length → lexicographic
    }
};

void multisetUsingMyComparator(const WordVec& vec) {
    std::multiset<std::string, MyComparator> myset(vec.begin(), vec.end());

    std::copy(myset.begin(), myset.end(),
              std::ostream_iterator<std::string>(std::cout, " "));
    std::cout << '\n';
}

// Task 8 
/*
   Generate the fibonacci sequence with std:: generate.n 
     using std::generate_n to fill a vector with Fibonacci numbers without writing an explicit loop yourself
*/

std::vector<long> generate_Fibonacci(int n) {
    std::vector<long> fibs(n);
    long a = 0, b = 1; // starting values

    std::generate_n(fibs.begin(), n, [&, count = 0]() mutable -> long {
        if (count == 0) { count++; return a; }
        if (count == 1) { count++; return b; }
        long next = a + b;
        a = b;
        b = next;
        return next;
    });

    return fibs;
}

// Task 9
/*
    Write a function that checks if two strings are anagrams of each other
    - remove all non-alphabetic characters
    - convert to lowercase
    - check if the sorted strings are equal
    - return the result
*/
bool areAnagrams(const std::string& s1, const std::string& s2) {
    std::string filtered1, filtered2;

    // Step 1: copy only alphabetic chars
    std::copy_if(s1.begin(), s1.end(), std::back_inserter(filtered1),
                 [](unsigned char ch) { return std::isalpha(ch); });
    std::copy_if(s2.begin(), s2.end(), std::back_inserter(filtered2),
                 [](unsigned char ch) { return std::isalpha(ch); });

    // Step 2: transform to lowercase
    std::transform(filtered1.begin(), filtered1.end(), filtered1.begin(),
                   [](unsigned char ch) { return std::tolower(ch); });
    std::transform(filtered2.begin(), filtered2.end(), filtered2.begin(),
                   [](unsigned char ch) { return std::tolower(ch); });

    // Step 3: check lengths early
    if (filtered1.size() != filtered2.size()) {
        return false;
    }

    // Step 4: sort and compare
    std::sort(filtered1.begin(), filtered1.end());
    std::sort(filtered2.begin(), filtered2.end());

    return filtered1 == filtered2;
}