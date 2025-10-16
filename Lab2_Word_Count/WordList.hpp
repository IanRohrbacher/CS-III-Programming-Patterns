#ifndef WORDLIST_HPP_
#define WORDLIST_HPP_

#include <string>

using std::string;

class WordOccurrence {
    public:
        WordOccurrence(const string& word="", int num=0) : word_(word), num_(num) {};
        bool matchWord(const string & rhs) {return word_ == rhs;}; // returns true if word matches stored
        void increment() {num_++;}; // increments number of occurrences
        string getWord() const {return word_;}; 
        int getNum() const {return num_;};

    private:
        string word_;
        int num_;
};

class WordList{
    public:
        // add copy constructor, destructor, overloaded assignment
        WordList() : size_(0), wordArray_(new WordOccurrence[size_]) {};
        WordList(const WordList&);
        ~WordList() {delete[] wordArray_;};

        WordList& operator=(WordList rhs) {swap(rhs); return *this;};
        
        // implement comparison as friend
        friend bool equal(const WordList&, const WordList&);

        void swap(WordList&);
        void addWord(const string &); // returns true if word is already in list
        void print();

        // Only use for testing purposes
        WordOccurrence * getWords() const {return wordArray_;};
        int getSize() const {return size_;};
    private:
        WordOccurrence *wordArray_; // a dynamically allocated array of WordOccurrences
                                    // may or may not be sorted
        int size_;
};


#endif
