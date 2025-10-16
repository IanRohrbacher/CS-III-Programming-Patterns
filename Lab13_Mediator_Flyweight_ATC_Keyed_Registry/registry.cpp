// Registry. Review the registry-based implementation for Observer and Prototype.
// Note that in the classic Registry Design Pattern, the entry is looked up by
// key rather than by pointer. In the Prototype implementation, the lookup is by
// key. In the Observer implementation, the lookup is by pointer. Using the Prototype
// implementation as an example, modify the Observer implementation of the registry
// so that the observers may subscribe to and unsubscribe from messages in subjects
// by the subject's names rather than pointers. Modify the demonstration code in
// main() to showcase this behavior.

#include <set>
#include <map>
#include <iostream>
#include <string>
#include <algorithm>

using std::cout; using std::endl;
using std::map; using std::set;
using std::string;

class Observer;
class Subject;

class EventRegistry{
public:
   static void registerObserver(string, Observer*);
   static void deregisterObserver(string, Observer*);
   static void handleMessage(string);
private:
   static map<string, set<Observer*>> observerMap_;
};

// initialize the static map
map<string, set<Observer*>> EventRegistry::observerMap_;


class Observer{
public:
   Observer(const string &name): name_(name) {}
   string getName() const {return name_;}
   void subscribe(string s) {EventRegistry::registerObserver(s, this);}
   void unsubscribe(string s){EventRegistry::deregisterObserver(s, this);}
   void handleMessage(string);
private:
   string name_;
};

class Subject{
public:
   Subject(const string &name): name_(name) {}
   string getName() const {return name_;}
   void generateMessage(){
      cout << name_ << " sent a message" << endl;
      EventRegistry::handleMessage(name_);}
private:
   string name_;
};

void EventRegistry::registerObserver(string s, Observer* o){
   observerMap_[s].insert(o);
   cout << o->getName() << " subscribed to " << s << endl;
}

void EventRegistry::deregisterObserver(string s, Observer* o){
   observerMap_[s].erase(o);
   cout << o->getName() << " unsubscribed from " << s << endl;
}

void EventRegistry::handleMessage(string s){
   for (auto e: observerMap_[s])
      e->handleMessage(s);
}

void Observer::handleMessage(string s) {
   cout << name_ << " received message from " << s << endl;
}


int main() {
   Subject  sue("Sue"),  steve("Steve");
   Observer oswald("Oswald"), olga("Olga");


   oswald.subscribe("Sue"); oswald.subscribe("Steve");
   olga.subscribe("Sue");

   cout << endl;

   

   sue.generateMessage();
   steve.generateMessage();
   cout << endl;
   

   olga.unsubscribe("Sue");
   sue.generateMessage();   

}
