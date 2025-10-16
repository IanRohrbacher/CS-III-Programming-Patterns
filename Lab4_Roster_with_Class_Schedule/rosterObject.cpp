// vector and list algorithms with objects in containers
// Mikhail Nesterenko
// 9/10/2018

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

bool printOut;

class Student{
   public:
      Student(string firstName, string lastName, string course): 
         firstName_(firstName), lastName_(lastName)
         {courseList_.push_back(course);}
   
      // move constructor, not really needed, generated automatically
      Student(Student && org) noexcept:
         firstName_(move(org.firstName_)),
         lastName_(move(org.lastName_)),
         courseList_(move(org.courseList_))
      {if(printOut) cout << "move\n";}
   
      // force generation of default copy constructor
      Student(const Student & org) = default;

      void addCourse(string course){courseList_.push_back(course);}
      string getCourse() const {return courseList_.back();}
      
      string print() const {
         string result = firstName_ + ' ' + lastName_ + ":";
         for(const auto& str : courseList_)
            result += str + ' ';
         return result;
      }

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
      list<string> courseList_;
};




// reading a list from a fileName
void readRoster(list<Student>& roster, string fileName);  

// printing a list out
void printRoster(const list<Student>& roster); 


// merge names with classes
void mergeStudents(list<Student>& roster);

// remove student from roster
void removeStudent(list<Student>& roster, Student student);

int main(int argc, char* argv[]){

   if (argc <= 1){ cout << "usage: " << argv[0] 
      << " list of courses, dropouts last" << endl; exit(1);}

   printOut = ("1" == string(argv[1]));


   // vector of courses of students
   vector <list<Student>> courseStudents; 

   for(int i=2; i < argc-1; ++i){
      list<Student> roster;
      readRoster(roster, argv[i]);  
      if (printOut) {
         cout << "\n\n" << argv[i] << "\n";  
         printRoster(roster);
      }
      courseStudents.push_back(move(roster)); 
   }


   // reading in dropouts
   list<Student> dropouts; 
   readRoster(dropouts, argv[argc-1]); 
   if (printOut) {
      cout << "\n\n dropouts \n"; printRoster(dropouts);
   }

   list<Student> allStudents;  // master list of students
 
   for(auto& lst : courseStudents) 
     allStudents.splice(allStudents.end(),lst);

   if (printOut) {
      cout << "\n\n all students unsorted \n"; 
      printRoster(allStudents);
   }

   allStudents.sort(); // sorting master list
   if (printOut) {
      cout << "\n\n all students sorted \n"; printRoster(allStudents);
   }

   mergeStudents(allStudents); // merging duplicates
   if (printOut) {
      cout << "\n\n all students, duplicates removed \n"; printRoster(allStudents);
   }

   for (const Student& str : dropouts)  // removing individual dropouts
      removeStudent(allStudents, str);
   if (printOut) {
      cout << "\n\n all students, dropouts removed \n"; printRoster(allStudents);
   } else {
      cout << "all students, dropouts removed and sorted\nfirst name last name: courses enrolled\n"; 
      printRoster(allStudents);
   }
}


void readRoster(list<Student>& roster, string fileName){
   ifstream course(fileName);
   string first, last;
   while(course >> first >> last)
      roster.push_back(move(Student(first, last, fileName.substr(0, fileName.find('.')))));
   course.close();
}

// printing a list out
void printRoster(const list<Student>& roster){
   for(const auto& student : roster)
      cout << student.print() << endl;
}


// merge names with classes
void mergeStudents(list<Student>& roster) {
   for(auto it = roster.begin(); it != roster.end();) {
      auto next = it;
      next++;
      if(next != roster.end() && *it == *next) {
         it->addCourse(next->getCourse());
         roster.erase(next);
      } else {
         it++;
      }
   }
}

// remove student from roster
void removeStudent(list<Student>& roster, Student student) {
   for(auto it = roster.begin(); it != roster.end(); it++) {
      if(*it == student) {
         roster.erase(it);
         break;
      }
   }
}