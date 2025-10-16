// selecting oranges
// converting vectors to multimaps
// Mikhail Nesterenko
// 9/26/2022


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>
#include <map>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector;

enum class Variety {orange, pear, apple};
vector<string> colors = {"red", "green", "yellow"};

// struct Fruit{
//    Variety v;
//    string color; // red, green or yellow
// };


int main(){
   srand(time(nullptr));
   // vector <Fruit> tree(rand()%100+1);
   int size = rand() % 100 + 1;
   std::multimap <Variety, string> tree;

   // random fruit and color selection
   // for(auto f=tree.begin(); f!=tree.end(); ++f){
   //    f->v = static_cast<Variety>(rand() % 3);
   //    f->color = colors[rand()%3];
   // }
   for(int i = 0; i < size; i++) {
      Variety v = static_cast<Variety>(rand() % 3);
      string color = colors[rand() % 3];
      tree.emplace(v, color);
   }


   // printing colors of oranges
   // cout << "Colors of the oranges: ";
   // for(auto f=tree.begin(); f!=tree.end(); ++f)
   //    if(f->v == Variety::orange) cout << f->color << ", ";
   // cout << endl;
   cout << "Colors of the oranges: ";
   for(auto it = tree.lower_bound(Variety::orange); it != tree.upper_bound(Variety::orange); it++) {
      cout << it->second << ", ";
   }
   cout << endl;
}

