#include <iostream>
#include <algorithm>
#include "WordList.hpp"

WordList::WordList(const WordList &rhs) {
    size_ = rhs.getSize();
    wordArray_ = new WordOccurrence[size_];
    for(int i = 0; i < size_; i++) {
        wordArray_[i] = rhs.getWords()[i];
    }
}

void WordList::swap(WordList &rhs) {
    WordOccurrence* temp = wordArray_;
    wordArray_ = rhs.wordArray_;
    rhs.wordArray_ = temp;

    int tempSize = size_;
    size_ = rhs.size_;
    rhs.size_ = tempSize;
}

void WordList::addWord(const string &word) {
    bool flag_ = true;
    for (int i = 0; i < size_; i++) {
        if (wordArray_[i].matchWord(word)) {
            wordArray_[i].increment();
            flag_ = false;
            break;
        }
    }
    if (flag_) {
        WordOccurrence* temp = new WordOccurrence[size_ + 1];
        for(int i = 0; i < size_; i++) {
            temp[i] = wordArray_[i];
        }
        temp[size_] = WordOccurrence(word, 1);
        delete[] wordArray_;
        wordArray_ = temp;
        size_++;
    }
    std::sort(wordArray_, wordArray_ + size_, [](WordOccurrence a, WordOccurrence b)
                {return a.getNum() < b.getNum() || (a.getNum() == b.getNum() && a.getWord() < b.getWord());});
}

void WordList::print() {
    for(int i = 0; i < size_; i++) {
        std::cout << wordArray_[i].getWord() << " " << wordArray_[i].getNum() << "\n";
    }
}

bool equal(const WordList &lhs, const WordList &rhs) {
    if(lhs.getSize() != rhs.getSize()) {
        return false;
    }
    for(int i = 0; i < lhs.getSize(); i++) {
        if(lhs.getWords()[i].getWord() != rhs.getWords()[i].getWord() || lhs.getWords()[i].getNum() != rhs.getWords()[i].getNum()) {
            return false;
        }
    }
    return true;
}