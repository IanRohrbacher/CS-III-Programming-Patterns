// CS3 Lab 1
// Ian Rohrbacher
// 1/24/25


#include <iostream>
#include <fstream>

using std::cout; using std::endl; using std::string;

// returns the index at the difference or -1 if no difference
int findDiff(string fileOne, string fileTwo){
    int lenght = (fileOne.length() < fileTwo.length()) ? fileOne.length() : fileTwo.length();
    for(int i = 0; i <= lenght; i++){
        if(fileOne[i] != fileTwo[i]){
            return i;
        }
    }
    return -1;
}

int main(int argc, char* argv[]) {
    // check for correct number of arguments
    if(argc != 3) {
        cout << "Incorrect Amount of Files! Must be Two Inputs!\n";
        return 0;
    }

    // open the files
    std::ifstream fileOne(argv[1]);
    std::ifstream fileTwo(argv[2]);

    // check if the files failed to open
    if (!fileOne.is_open() || !fileTwo.is_open()) {
        cout << "Unable to Open a File!\n";
    }
    else {
        string fileName = argv[1];

        string lineOne;
        string lineTwo;
        int lineNum = 1;
        do {
            if (!fileOne.eof()) {
                std::getline(fileOne, lineOne);
            } else {
                lineOne = "";
            }
            if (!fileTwo.eof()) {
                std::getline(fileTwo, lineTwo);
            } else {
                lineTwo = "";
            }
            int buffer = findDiff(lineOne, lineTwo);
            if (buffer != -1) {
                string filler = ": " + std::to_string(lineNum) + ": ";
                cout << argv[1] << filler << lineOne << "\n";
                cout << argv[2] << filler << lineTwo << "\n";
                for(int j = 0; j < buffer + fileName.length() + filler.size(); j++) {
                    cout << " ";
                }
                cout << "^\n";
            }
            lineNum++;
        } while (!fileOne.eof() || !fileTwo.eof());
    }

    // exit gracefully
    if (fileOne.is_open()) {
        fileOne.close();
    }
    if (fileTwo.is_open()) {
        fileTwo.close();
    }
    return 0;
}