// vector and list algorithms
// Mikhail Nesterenko
// 3/11/2014

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move;

// reading a list from a fileName
void readRoster(list<string>& roster, string fileName);  

// printing a list out
void printRoster(const list<string>& roster);


// add class to student
void addClass(list<string>& roster, string fileName);

// merge names with classes
void mergeStudents(list<string>& roster);

// remove student from roster
void removeStudent(list<string>& roster, string student);


int main(int argc, char* argv[]){
   
   if (argc <= 1){ 
      cout << "usage: " << argv[0] 
      << " list of courses, dropouts last" 
      << endl;
      exit(1);
   }
   
   bool printOut = ("1" == string(argv[1]));


   // vector of courses of students
   vector <list<string>> courseStudents; 

   for(int i=2; i < argc-1; ++i){
      list<string> roster;
      readRoster(roster, argv[i]);
      addClass(roster, argv[i]);
      if (printOut) {
         cout << "\n\n" << argv[i] << "\n";  
         printRoster(roster);
      }
      courseStudents.push_back(move(roster));
   }

  
   // reading in dropouts
   list<string> dropouts; 
   readRoster(dropouts, argv[argc-1]); 
   if (printOut) {
      cout << "\n\ndropouts\n";
      printRoster(dropouts);
   }

   // master list of students
   list<string> allStudents;  

   for(auto& lst : courseStudents) 
     allStudents.splice(allStudents.end(), lst);

   if (printOut) {
      cout << "\n\n all students unsorted \n"; 
      printRoster(allStudents);
   }

   
   // sorting master list
   allStudents.sort();
   if (printOut) {
      cout << "\n\n all students sorted \n"; 
      printRoster(allStudents);
   }
   
   // merging duplicates
   mergeStudents(allStudents); 
   if (printOut) {
      cout << "\n\n all students, merged \n"; 
      printRoster(allStudents);
   }

   // removing individual dropouts
   for (const string& str : dropouts)
      removeStudent(allStudents, str);
   if (printOut) {
      cout << "\n\n all students, dropouts removed \n"; 
      printRoster(allStudents);
   } else {
      cout << "all students, dropouts removed and sorted\nfirst name last name: courses enrolled\n"; 
      printRoster(allStudents);
   }
   
}

// reading in a file of names into a list of strings
void readRoster(list<string>& roster, string fileName){
   ifstream course(fileName);
   string first, last;
   while(course >> first >> last)
      roster.push_back(move(first) + ' ' + move(last));
   course.close();
}

// printing a list out
void printRoster(const list<string>& roster){
   for(const string& str : roster)
      cout << str << ' ' << endl;
}

// add class to student
void addClass(list<string>& roster, string fileName) {
   for(string& str : roster)
      str += ':' + fileName.substr(0, fileName.find('.'));
}

// merge names with classes
void mergeStudents(list<string>& roster) {
   for(auto it = roster.begin(); it != roster.end();) {
      auto next = it;
      next++;
      if(next != roster.end() && it->substr(0, it->find(':')) == next->substr(0, next->find(':'))) {
         *it += ' ' + next->substr(next->find(':') + 1);
         roster.erase(next);
      } else {
         it++;
      }
   }
}

void removeStudent(list<string>& roster, string student) {
   for(auto it = roster.begin(); it != roster.end(); it++) {
      if(it->substr(0, it->find(':')) == student) {
         roster.erase(it);
         break;
      }
   }
}