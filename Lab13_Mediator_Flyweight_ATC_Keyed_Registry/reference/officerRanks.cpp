// flyweight example
// Mikhail Nesterenko
// 4/26/2022

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <map>
#include <set>
#include <vector>

using std::string;

enum class rank {lieutenant, captain, major, general};

// abstract flyweight
class Rank{
public:
   virtual string image() = 0;
};

// concrete flyweights
class Lieutenant: public Rank{
public:
   string image() override { return "*"; }
};


class Captain: public Rank{
   string image() override { return "**"; }
};

class Major: public Rank{
public:
   string image() override { return "***"; }
};

class General: public Rank{
public:
   string image() override { return "****"; }
};


// factory
class Academy{
public:
   static Rank *makeRank(rank r){
     // if officer rank not found
     if(ranks_.find(r) == ranks_.end())
	 switch(r){
	 case rank::lieutenant:
	    ranks_[r] = new Lieutenant; break;
	 case rank::captain:
	    ranks_[r] = new Captain; break;
	 case rank::major:
	    ranks_[r] = new Major; break;
	 case rank::general:
	    ranks_[r] = new General; break;
	 }
      return ranks_[r];
   }
private:
   static std::map<rank, Rank*> ranks_;
}; 

std::map<rank, Rank*> Academy::ranks_;


// client with extrinsic state
class Officer{
public:
   Officer(string name, rank r): name_(name){
      rank_ = Academy::makeRank(r);
   }
   void report() const {
      std::cout << name_ << ' ' << rank_ -> image() << std::endl;
   }
   void promote(rank r){
      rank_ = Academy::makeRank(r);
   }   
   // this is neded for std::set
   friend bool operator<(const Officer& lhs, const Officer& rhs){
      return lhs.name_ < rhs.name_;
   }
   
private:
   const string name_;
   Rank *rank_;
};

int main(){
   std::set<Officer> troops = {
      Officer("David Johnson", rank::lieutenant),
      Officer("Shirley Parker", rank::major),
      Officer("Derek Blake", rank::captain),
      Officer("Nick Allen", rank::lieutenant),
   };

   for(const auto &e: troops)
      e.report();

   std::cout << "\nPromote everyone\n";

   std::set<Officer> generals;
   
   std::transform(
      troops.begin(), troops.end(),
      std::inserter(generals, generals.end()),
      [](Officer o) {o.promote(rank::general); return o; }
   );

   for(const auto &e: generals)
      e.report();
}
