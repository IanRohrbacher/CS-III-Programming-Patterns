// Prints a table of the character manipulation functions output
// Author: Sean McCulloch
// Date 6/9/97

#include <iostream>
#include <cctype>

using std::cout; using std::cin; using std::endl;

int main(){

  char c; // The character to manipulate
  do{
    cout << "Enter the Character(n to stop): ";
    cin >> c;


    cout 
      << "Function" << "   Result" << endl
      << "-------------------" << endl

      // the functions return non-zero value if true
      << "isalnum" << "  " << isalnum(c) << endl
      << "isalpha" << "  " << isalpha(c) << endl
      << "iscntrl" << "  " << iscntrl(c) << endl
      << "isdigit" << "  " << isdigit(c) << endl
      << "isgraph" << "  " << isgraph(c) << endl
      << "islower" << "  " << islower(c) << endl
      << "isprint" << "  " << isprint(c) << endl
      << "ispunct" << "  " << ispunct(c) << endl
      << "isspace" << "  " << isspace(c) << endl
      << "isupper" << "  " << isupper(c) << endl

      // the functions return integers, we use
      // type casting (char) to have it printed
      // in character representation
      << "tolower" << "  " << char(tolower(c)) << endl
      << "toupper" << "  " << char(toupper(c)) << endl;
  }while(c!='n');

}
