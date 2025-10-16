// adding/removing lines of text, demos Memento Design Pattern
// Mikhail Nesterenko
// 11/8/2024

#include <iostream>
#include <vector>
#include <string>

using std::vector; using std::string;
using std::cout; using std::cin; using std::endl;

// originator
class Document {
public:
   Document(vector <string> lines={}): lines_(lines){}

   void insert(int line, const string &str) {
      int index = line-1;
      if (index <= lines_.size()+1)
	 lines_.insert(lines_.begin()+index, str); 
      else
	 cout << "line out of range" << endl; 
   }

   void remove(int line) {
      int index = line-1;
      if(index < lines_.size())
	 lines_.erase(lines_.begin()+index); 
      else
	 cout << "line out of range" << endl; 
   } 

   void show() const {
      for(int i = 0; i < lines_.size(); ++i)
	 cout << i + 1 << ". " << lines_[i] << endl; 
   }

   class Memento *checkpoint() const;  
   void rollback(const class Memento *); 

private:
   vector<string> lines_; 
}; 

class Memento {
public:
   Memento(const Document& doc): doc_(doc) {}
   const Document& getState() const {return doc_;}  
private:
   const Document doc_;
};
 
Memento *Document::checkpoint() const {
   return new Memento(*this); // copying the Document itself
}

void Document::rollback(const Memento *mem){
   *this = mem->getState();  // copying back
}

// client and caretaker
int main() {
   Document doc({
         "Lorem Ipsum is simply dummy text of the printing and typesetting",
         "industry. Lorem Ipsum has been the industry's standard dummy text",
         "ever since the 1500s, when an unknown printer took a galley of",
	 "type and scrambled it to make a type specimen book. It has",
	 "survived five centuries."
   });

   char option;
   
   do{
      static Memento *safeState = nullptr;

      doc.show();
      cout << endl;

     cout << "Enter option (i)nsert line, (e)rase line, (c)heckpoint, (r)ollback: ";
      cin >> option;

      int line; string str; 
      switch(option) {
      case 'i':
         cout << "line number to insert: ";
         cin >> line;
         cout << "line to insert: ";
	 cin.get();
         getline(cin, str);
         doc.insert(line, str);
         break;
      case 'e':
         cout << "line number to remove: ";
         cin >> line;
         doc.remove(line);
         break;
      case 'c':
	 safeState = doc.checkpoint();
	 break;
      case 'r':
	 if (safeState != nullptr){
	    doc.rollback(safeState);
	    delete safeState;
	    safeState = nullptr;
	 }else
	    cout << "No checkpoint created" << endl;
         break;
      }
   }while(option == 'i' || option == 'e' || option == 'c' || option == 'r');
}
