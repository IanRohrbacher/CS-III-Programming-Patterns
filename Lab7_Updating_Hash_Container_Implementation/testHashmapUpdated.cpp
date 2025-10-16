// hashmap test file
// Mikhail Nesterenko,  Tsung-Heng Wu
// 3/6/2024

#include "hashmap.hpp"
#include <iostream>
#include <string>
#include <cassert>

using std::string;

int main() {

   //
   // <int, int> hashmap test
   //
   hashmap<int, int> myHash;
   
   // test inserts
   pair<const pair<const int, int>*, bool> result;

   result = myHash.insert(make_pair(4, 40));
   assert(result.second);
   assert(result.first->first == 4);
   assert(result.first->second == 40);

   result = myHash.insert(make_pair(105, 1050));
   assert(result.second);
   assert(result.first->first == 105);
   assert(result.first->second == 1050);

   result = myHash.insert(make_pair(6, 60));
   assert(result.second);
   assert(result.first->first == 6);
   assert(result.first->second == 60);

   result = myHash.insert(make_pair(107, 1070));
   assert(result.second);
   assert(result.first->first == 107);
   assert(result.first->second == 1070);

   result = myHash.insert(make_pair(90, 900));
   assert(result.second);
   assert(result.first->first == 90);
   assert(result.first->second == 900);

   result = myHash.insert(make_pair(95, 950));
   assert(result.second);
   assert(result.first->first == 95);
   assert(result.first->second == 950);

   result = myHash.insert(make_pair(6, 70)); // insert with a duplicate key
   assert(!result.second);
   assert(result.first->first == 6);
   assert(result.first->second == 60);


   // searching map
   // x will have type hashmap<int, int>::value_type*
   auto x = myHash.find(4);
   assert(x != nullptr);
   assert(x->second == 40);

   x = myHash.find(5);
   assert(x == nullptr);


   // test deletes
   result = myHash.erase(4); // delete with next element in same bucket
   assert(result.second);
   assert(result.first->first == 105);
   assert(result.first->second == 1050);

   result = myHash.erase(107); // delete the last element in a bucket
   assert(result.second);
   assert(result.first->first == 90);
   assert(result.first->second == 900);

   result = myHash.erase(6);
   assert(result.second);
   assert(result.first->first == 90);
   assert(result.first->second == 900);

   result = myHash.erase(105);
   assert(result.second);
   assert(result.first->first == 90);
   assert(result.first->second == 900);

   result = myHash.erase(95); // erase the last element in the container
   assert(result.second);
   assert(result.first== nullptr);

   result = myHash.erase(90); // erased all elements in container
   assert(result.second);
   assert(result.first == nullptr);

   result = myHash.erase(5); // erase key not in container
   assert(!result.second);
   // first is unspecified


   //
   // <integer, string> hashmap test
   //
   hashmap<int, string> employees;
   
   // add tests for insert using the <integer, string> hashmap
   employees.insert(make_pair(1, "John"));
   employees.insert(make_pair(27, "Jane"));
   employees.insert(make_pair(82, "Jim"));
   employees.insert(make_pair(13, "Jill"));

    // add tests for find using the <integer, string> hashmap
    auto employee = employees.find(27);
    assert(employee != nullptr);
    assert(employee->second == "Jane");

    auto employee2 = employees.find(82);
    assert(employee2 != nullptr);
    assert(employee2->second == "Jim");

    // add tests for erase using the <integer, string> hashmap
    employees.erase(27);
    employee = employees.find(27);
    assert(employee == nullptr);

    employees.erase(82);
    employee2 = employees.find(2);
    assert(employee2 == nullptr);

    // add tests for [] operator using the <integer, string> hashmap
    employees[17] = "paul";
    employees[4] = "peernar";
    employees[27] = "pluto";
    employees[90] = "phillip";

    assert(employees[1] == "John");
    assert(employees[4] == "peernar");
    assert(employees[13] == "Jill");
    assert(employees[17] == "paul");
    assert(employees[27] == "pluto");
    assert(employees[90] == "phillip");
    

    // add tests for rehash
    employees.rehash(10);

    
    // check the hashmap is still correct and all operations still work after rehash
    assert(employees.find(1)->second == "John");
    assert(employees.find(4)->second == "peernar");
    assert(employees.find(13)->second == "Jill");
    assert(employees.find(17)->second == "paul");
    assert(employees.find(27)->second == "pluto");
    assert(employees.find(90)->second == "phillip");

    std::cout << "Tests passed" << std::endl;
}
