// Imports text files and counts the number of words in each file separateed by whitespace or punctuation marks
// Ian Rohrbacher
// 1/31/2025

#include <iostream>
#include <fstream>
#include <cctype>
#include "WordList.hpp" // class definitions

using std::cout; using std::endl; using std::string;

string getWord(std::ifstream& file);

int main() {
    string file_ = "file1.txt";

    std::ifstream openFile_(file_);
    if (!openFile_.is_open()) {
        cout << "Unable to Open a File!\n";
        return 0;
    }

    WordList list_;
    while(!openFile_.eof()) {
        string temp_ = getWord(openFile_);
        if (temp_ != "") {
            list_.addWord(temp_);
        }
    }

    list_.print();

    return 0;
}

string getWord(std::ifstream& file) {
    string final_ = "";
    char ch_;
    file.get(ch_);
    while (!file.eof() && (ispunct(ch_) == 0 && isspace(ch_) == 0)) {
        final_ += ch_;
        file.get(ch_);
    }
    return final_;
}