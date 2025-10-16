// vector and list algorithms with objects in containers
// Mikhail Nesterenko
// 9/10/2018

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <map>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector; using std::map;
using std::cout; using std::endl;
using std::move;


class Student{
   public:
      Student(string firstName, string lastName): 
         firstName_(firstName), lastName_(lastName) {}
   
      // move constructor, not really needed, generated automatically
      Student(Student && org) noexcept:
         firstName_(move(org.firstName_)),
         lastName_(move(org.lastName_))
      {}
   
      // force generation of default copy constructor
      Student(const Student & org) = default;
      
      string print() const {return firstName_ + ' ' + lastName_;}

      // needed for unique() and for remove()
      friend bool operator== (Student left, Student right){
         return left.lastName_ == right.lastName_ &&
         left.firstName_ == right.firstName_;
      }

      // needed for sort()
      friend bool operator< (Student left, Student right){
         return left.firstName_ < right.firstName_ ||
         (left.firstName_ == right.firstName_ && 
            left.lastName_ < right.lastName_);
      }
   private:
      string firstName_;
      string lastName_;
};




// reading a list from a fileName
void readRoster(map<Student, list<string>>& map, string fileName);  

// printing a list out
void printMap(const map<Student, list<string>>& map); 

// removes all students who are enrolled in 'dropouts'
void removeRoster(map<Student, list<string>>& map, string fileName); 


int main(int argc, char* argv[]){

   if (argc <= 1){cout << "usage: " << argv[0] << " list of courses, dropouts last" << endl; exit(1);}
   bool printOut = ("1" == string(argv[1]));

   map<Student, list<string>> studentMap;

   // read in all courses and dropouts
   for(int i=2; i < argc; ++i){
      readRoster(studentMap, argv[i-1]);  
      if (printOut) {cout << "\n\n" << argv[i] << "\n"; printMap(studentMap);}
   }
    
   if (printOut) {cout << "\n\n all students sorted \n"; printMap(studentMap);}
   
   removeRoster(studentMap, argv[argc-1]);
   if (printOut) {cout << "\n\n all students, dropouts removed \n"; printMap(studentMap);}
   else {cout << "all students, dropouts removed and sorted\nfirst name last name: courses enrolled\n"; printMap(studentMap);}
}


// reading a list from a fileName
void readRoster(map<Student, list<string>>& map, string fileName){
   ifstream course(fileName);
   string first, last;
   while(course >> first >> last)
      map[Student(first, last)].push_back(fileName.substr(0, fileName.find('.')));
   course.close();
}

// printing a list out
void printMap(const map<Student, list<string>>& map){
   for (const auto& item : map) {
      cout << item.first.print() << ":";
      for (const auto& course : item.second)
         cout << course << ' ';
      cout << endl;
   }
}

// removes all students who are enrolled in 'dropouts'
void removeRoster(map<Student, list<string>>& map, string fileName) {
   ifstream course(fileName);
   string first, last;
   while(course >> first >> last) {
      Student student(first, last);
      map.erase(student);
   }
   course.close();
}