// needed for lab
// Mikhail Nesterenko
// 3/18/2022

#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <array>
#include "CarFactory.hpp"

using std::vector;
using std::cout; using std::endl; using std::string;

class CarLot{
public:
   CarLot();
   Car* testDriveCar() { car4saleIter_ = car4sale_.begin(); return *car4saleIter_; };

   // if a car is bought, requests a new one, limit of eight cars
   void buyCar() { car4sale_.erase(car4saleIter_); car4sale_.push_back(factories_[rand()%factories_.size()]->requestCar()); }; // if the car is bought, request a new one;
   int lotSize() const { return car4sale_.size(); }
   Car* nextCar() {car4saleIter_ = std::next(car4saleIter_); return *car4saleIter_;};

   void printLot() const { std::for_each(car4sale_.begin(), car4sale_.end(), [](Car* car) { cout << "Car in lot: " << car->getMake() << " " << car->getModel() << endl; }); }
		     
private:
   vector<Car*> car4sale_;
   vector<Car*>::iterator car4saleIter_;
   vector<CarFactory*> factories_;
};

CarLot::CarLot(){
   // creates 2 Ford factories and 2 Toyota factories 
   factories_.push_back(new FordFactory());   
   factories_.push_back(new ToyotaFactory());
   factories_.push_back(new FordFactory());
   factories_.push_back(new ToyotaFactory());

   // starts the lot with eight cars
   std::generate_n(std::back_inserter(car4sale_), 8, [this]() { return factories_[rand()%factories_.size()]->requestCar(); });
   // printLot();
}


CarLot *carLotPtr = nullptr; // global pointer instantiation


// test-drives a car
// buys it if Toyota
void toyotaLover(int id){
   // if (carLotPtr == nullptr)
   //    carLotPtr = new CarLot();

   // Car *toBuy = carLotPtr -> testDriveCar(); 

   // cout << "Jill Toyoter " << id << endl;
   // cout << "test driving " << toBuy->getMake() << " " << toBuy->getModel();

   // if (toBuy->getMake() == "Toyota"){
   //    cout << " love it! buying it!" << endl;
   //    carLotPtr -> buyCar();
   // } else
   //    cout << " did not like it!" << endl;
   
   if (carLotPtr == nullptr) {
      carLotPtr = new CarLot();
   }

   static const std::array<std::string, 5> models = {"Corolla", "Camry", "Prius", "4Runner", "Yaris"};
   string preferredModel = models[rand() % models.size()];
   Car* toBuy = carLotPtr -> testDriveCar();

   for (int i=0; i<carLotPtr->lotSize(); i++) {
      cout << "Jill Toyoter " << id << " wants a " << preferredModel << endl;
      cout << "test driving " << toBuy->getMake() << " " << toBuy->getModel();

      if (toBuy->getMake() == "Toyota" && toBuy->getModel() == preferredModel) {
         cout << " love it! buying it!" << endl;
         carLotPtr -> buyCar();
         break;
      } else
         cout << " did not like it!" << endl;
         toBuy = carLotPtr->nextCar();
   }

   // carLotPtr->printLot();
}

// test-drives a car
// buys it if Ford
void fordLover(int id){
   if (carLotPtr == nullptr) {
      carLotPtr = new CarLot();
   }

   static const std::array<std::string, 4> models = {"Focus", "Mustang", "Explorer", "F-150"};
   string preferredModel = models[rand() % models.size()];
   Car* toBuy = carLotPtr -> testDriveCar();

   for (int i=0; i<carLotPtr->lotSize(); i++) {
      cout << "Jack Fordman " << id << " wants a " << preferredModel << endl;
      cout << "test driving " << toBuy->getMake() << " " << toBuy->getModel();

      if (toBuy->getMake() == "Ford" && toBuy->getModel() == preferredModel) {
         cout << " love it! buying it!" << endl;
         carLotPtr -> buyCar();
         break;
      } else
         cout << " did not like it!" << endl;
         toBuy = carLotPtr->nextCar();
   }

}



int main() {
   srand(time(nullptr));

   const int numBuyers=20;
   for(int i=0; i < numBuyers; ++i) {
      if(rand()% 2 == 0)
         toyotaLover(i);
      else
         fordLover(i);
      cout << endl;
   }
}
