#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <cstdio>
#include <ctime>
#include <algorithm>
#include <map>

// for timed sleep
#include <thread>
#include <chrono>


using std::cout; using std::cin; using std::endl;
using std::string;


// abstract mediator
class Controller{
public:
   virtual void join(class Flight*)=0;
   virtual void leave(class Flight*)=0;
   virtual void broadcast() = 0;
   virtual void observe() = 0;
};


// concrete mediator
// tower, runway clearance
class Tower: public Controller{
public:
   void join(class Flight*) override; 
   void leave(class Flight*) override;
   void broadcast() override;
   void observe() override;
private:
   std::set<class Flight*> waiting_;
};

enum class FlightCompany {AIRFRANCE, KLM, AEROFLOT, LUFTHANSA, DELTA, ALASKAN, SPIRIT};
class Company {
    public:
        virtual string getCompany() = 0;
};
class AirFrance: public Company {
    public:
        string getCompany() override { return "AirFrance"; };
};
class KLM: public Company {
    public:
        string getCompany() override { return "KLM"; };
};
class Aeroflot: public Company {
    public:
        string getCompany() override { return "Aeroflot"; };
};
class Lufthansa: public Company {
    public:
        string getCompany() override { return "Lufthansa"; };
};
class Delta: public Company {
    public:
        string getCompany() override { return "Delta"; };
};
class Alaskan: public Company {
    public:
        string getCompany() override { return "Alaskan"; };
};
class Spirit: public Company {
    public:
        string getCompany() override { return "Spirit"; };
};
// factory
class planeFactory {
    public:
        static Company* getPlane(FlightCompany plane) {
            if(planes_.find(plane) == planes_.end()) {
                switch (plane) {
                    case FlightCompany::AIRFRANCE:
                        planes_[plane] = new AirFrance; break;

                    case FlightCompany::KLM:
                        planes_[plane] = new KLM; break;

                    case FlightCompany::AEROFLOT:
                        planes_[plane] = new Aeroflot; break;

                    case FlightCompany::LUFTHANSA:
                        planes_[plane] = new Lufthansa; break;

                    case FlightCompany::DELTA:
                        planes_[plane] = new Delta; break;

                    case FlightCompany::ALASKAN:
                        planes_[plane] = new Alaskan; break;

                    case FlightCompany::SPIRIT:
                        planes_[plane] = new Spirit; break;
                }
            }
            return planes_[plane];
        }
    private:
        static std::map<FlightCompany, Company*> planes_;
};
std::map<FlightCompany, Company*> planeFactory::planes_;


// abstract colleague
class Flight {
public:
    Flight(Controller *controller):controller_(controller), status_(Status::waiting){
        task_ = rand() % 2 ? Task::taxiing : Task::approaching;
        controller_->join(this);
    }
    void receive(const string &msg){
        if (msg.find(std::to_string(flightNo_)) != string::npos || msg.find("all") != string::npos) {
            if(msg.find("clear") != string::npos) {
                cout << flightName_->getCompany() << flightNo_ << " roger that, ";
                cout << (task_ == Task::taxiing ? "taking off" : "landing") << endl;
                status_ = Status::cleared;
            } else if(msg.find("status") != string::npos) {
                cout << flightName_->getCompany() << flightNo_ << (status_ == Status::waiting ? " waiting to " : " cleared to ") << (task_ == Task::taxiing ? "take off" : "land") << endl;
            } else {
                cout << "Tower, this is " << flightName_->getCompany() << flightNo_ << " please repeat." << endl;
            }
        }
    }
    bool isCleared() const {return status_ == Status::cleared;}
    void proceed(){
        std::this_thread::sleep_for(std::chrono::seconds(rand()%3+1)); // wait a while
        string temp = flightName_->getCompany();
        std::transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
        cout << "..." << temp << flightNo_ << (task_ == Task::taxiing ? " took off" : " landed") << "..." << endl; 
        controller_->leave(this);
    }

protected:
    int flightNo_;
    Company* flightName_;
    Controller *controller_;
    enum class Task {taxiing, approaching};  Task task_;
    enum class Status {waiting, cleared};    Status status_;
};

// concrete colleagues
class Airbus: public Flight{
    public:
        Airbus(Tower *tower): Flight(tower) {
            flightNo_ = rand() % 1000;
            switch (rand() % 4) {
                case 0: flightName_ = planeFactory::getPlane(FlightCompany::AIRFRANCE); break;
                case 1: flightName_ = planeFactory::getPlane(FlightCompany::KLM); break;
                case 2: flightName_ = planeFactory::getPlane(FlightCompany::AEROFLOT); break;
                case 3: flightName_ = planeFactory::getPlane(FlightCompany::LUFTHANSA); break;
            }
            cout << flightName_->getCompany() << flightNo_ << " requesting " << (task_ == Task::taxiing ? "takeoff" : "landing") << endl;
        }
};

class Boeing: public Flight{
    public:
        Boeing(Tower *tower): Flight(tower) {
            flightNo_ = rand() % 1000;
            switch (rand() % 3) {
                case 0: flightName_ = planeFactory::getPlane(FlightCompany::DELTA); break;
                case 1: flightName_ = planeFactory::getPlane(FlightCompany::ALASKAN); break;
                case 2: flightName_ = planeFactory::getPlane(FlightCompany::SPIRIT); break;
            }
            cout << flightName_->getCompany() << flightNo_ << " requesting " << (task_ == Task::taxiing ? "takeoff" : "landing") << endl;
        }
};

// member functions for Tower
void Tower::broadcast() {
    cout << "Tower: ";
    string msg;
    getline(cin,msg);
    if(!msg.empty())
        for(auto f: waiting_) f->receive(msg);
}


void Tower::observe() {
   auto findCleared = [](Flight *f){return f->isCleared();};
   
   auto toProceed = std::find_if(waiting_.begin(), waiting_.end(), findCleared);
   
    while (toProceed != waiting_.end()){ // found a cleared flight
        (*toProceed) -> proceed();
        toProceed = std::find_if(waiting_.begin(), waiting_.end(), findCleared);
        if(toProceed != waiting_.end())
            cout << "MAYDAY! MAYDAY! MAYDAY! " << endl; // more than a single flight cleared
    }
}


void Tower::join(Flight *f) {
    waiting_.insert(f);
}


void Tower::leave(Flight *f) {
    waiting_.erase(f);
    delete f;
}

int main(){
    srand(time(nullptr));
    Tower jfk;

    new Boeing(&jfk);
    new Airbus(&jfk);
    new Boeing(&jfk);
    new Airbus(&jfk);

    while(true){
        jfk.broadcast();
        jfk.observe();
        if(rand() % 2){
            if (rand() % 2)
            new Boeing(&jfk);
        else
            new Airbus(&jfk);
        }
    }
}
