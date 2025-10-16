// vector and list algorithms with objects in containers
// Mikhail Nesterenko
// 9/10/2018

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <set>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector; using std::set;
using std::cout; using std::endl;
using std::move;

bool printOut;

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
void readRoster(set<Student>& studentSet, string fileName);  

// printing a list out
void printMap(const set<Student>& studentSet); 

// removes all students who are enrolled in 'dropouts'
void removeRoster(set<Student>& studentSet, const set<Student>& removeInSet); 


int main(int argc, char* argv[]){

   if (argc <= 1){cout << "usage: " << argv[0] << " list of courses, dropouts last" << endl; exit(1);}
   bool printOut = ("1" == string(argv[1]));

   set<Student> studentSet;
   set<Student> dropouts;

   // read in all courses and dropouts
   for(int i=2; i < argc-1; ++i){
      readRoster(studentSet, argv[i-1]);  
      if (printOut) {cout << "\n\n" << argv[i] << "\n"; printMap(studentSet);}
   }
   readRoster(dropouts, argv[argc-1]);  
   if (printOut) {cout << "\n\n" << argv[argc-1] << "\n"; printMap(studentSet);}   

   // read in all courses and dropouts
   removeRoster(studentSet, dropouts);
   if (printOut) {cout << "\n\n all students, dropouts removed \n"; printMap(studentSet);}
   else {cout << "Currently Enrolled Students\n"; printMap(studentSet);}
}


// reading a list from a fileName
void readRoster(set<Student>& studentSet, string fileName){
   ifstream course(fileName);
   string first, last;
   while(course >> first >> last)
      studentSet.insert(Student(first, last));
   course.close();
}

// printing a list out
void printMap(const set<Student>& studentSet){
   for (const auto& item : studentSet) {
      cout << item.print() << endl;
   }
}

// removes all students who are enrolled in 'dropouts'
void removeRoster(set<Student>& studentSet, const set<Student>& removeInSet) {
   for (const auto& dropout : removeInSet) {
      studentSet.erase(dropout);
   }
}