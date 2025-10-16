// jamming peaches
// non STL-algorithm code to be replaced by algorthms
// Mikhail Nesterenko
// 9/30/2021


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <numeric>
#include <functional>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector; using std::deque;

struct Peaches{
   double weight; // oz
   bool ripe;  // ripe or not
   void print() const { cout << (ripe?"ripe":"green") << ", " <<  weight << endl; }
};

Peaches fillBasket(double minWeight, double maxWeight) {
   Peaches peach;
   peach.ripe = rand() % 2 == 1;
   peach.weight = minWeight + static_cast<double>(rand())/RAND_MAX*(maxWeight - minWeight);
   return peach;
}

int main(){
   srand(time(nullptr));
   const double minWeight = 3.;
   const double maxWeight = 8.;

   cout << "Input basket size: ";
   int size;
   cin >> size;

   vector <Peaches> basket(size);

   // assign random weight and ripeness peaches in the basket
   // replace with generate()
   // for(auto it = basket.begin(); it != basket.end(); ++it){
   //    it->weight = minWeight + 
	//            static_cast<double>(rand())/RAND_MAX*(maxWeight - minWeight);
   //    it->ripe = rand() % 2;
   // }
   std::generate(basket.begin(), basket.end(), [&minWeight, &maxWeight](){return fillBasket(minWeight, maxWeight);});

   
   // for_each() possibly
   cout << "all peaches"<< endl;
   // for(const auto &e: basket) {
   //    e.print(); 
   // }
   std::for_each(basket.begin(), basket.end(), [](const Peaches &peaches){peaches.print();});
   cout << endl;


   // moving all the ripe peaches from basket to peck
   // remove_copy_if() with back_inserter()/front_inserter() or equivalents
   deque<Peaches> peck;
   // for(auto it=basket.begin(); it != basket.end();)
   //    if(it->ripe){
   //       peck.push_front(std::move(*it));
   //       it=basket.erase(it);
   //    }else
   //       ++it;
   std::remove_copy_if(basket.begin(), basket.end(), std::back_inserter(peck), [](Peaches &peaches){return !peaches.ripe;});
   // basket.erase(std::remove_if(basket.begin(), basket.end(), [](const Peaches &peaches){return peaches.ripe;}), basket.end());

   // for_each() possibly
   cout << "peaches remaining in the basket"<< endl;
   // for(const auto &e: basket) {
   //    e.print(); 
   // }
   std::for_each(basket.begin(), basket.end(), [](const Peaches &peaches){peaches.print();});
   cout << endl;


   // for_each() possibly
   cout << "peaches moved to the peck"<< endl;
   // for(const auto &e: peck) {
   //    e.print();
   // } 
   std::for_each(peck.begin(), peck.end(), [](const Peaches &peaches){peaches.print();});


   // prints every "space" peach in the peck
   const int space=3; 
   cout << "\nevery " << space << "\'d peach in the peck"<< endl;

   // replace with advance()/next()/distance()
   // no explicit iterator arithmetic
   // auto it=peck.cbegin(); int i = 1;   
   // while(it != peck.cend()){
   //    if(i == space){
	//  it->print();
	//  i=0;
   //    }
   //    ++i; 
   //    ++it;
   // }
   auto it = std::next(peck.cbegin(), space-1);
   for(int i=0; i < peck.size()/space; i++){
      it->print();
      std::advance(it, space);
   }


   // putting all small ripe peaches in a jam
   // use a binder to create a functor with configurable max weight
   // accumulate() or count_if() then remove_if()
   const double weightToJam = 10.0;
   // double jamWeight = 0; 
   // for(auto it=peck.begin(); it != peck.end();)
   //    if(it->weight < weightToJam){
	//  jamWeight += it->weight;
	//  it=peck.erase(it);
   //    }else
	//  ++it;
   
   // use a binder to create a functor with configurable max weight
   auto funct = std::bind(std::less<double>(), std::placeholders::_1, weightToJam);

   cout << "Weight of jam is: "
   << std::accumulate(peck.begin(), peck.end(), 0.0, [&weightToJam, &funct](double sum, const Peaches &peaches){return sum + (funct(peaches.weight) ? peaches.weight : 0.0);})
   << endl;
   peck.erase(std::remove_if(peck.begin(), peck.end(), [&weightToJam, &funct](const Peaches &peaches){return funct(peaches.weight);}), peck.end());
   cout << "peaches left in the peck"<< endl;
   std::for_each(peck.begin(), peck.end(), [](const Peaches &peaches){peaches.print();});
   cout << endl;
}

