// potential security issue with a generic friend
// Mikhail Nesterenko
// 2/3/2021

#include <iostream>

using std::cout; using std::endl;


// specific friend definition avoids this problem
template <typename T>
class Myclass;


template <typename T>
bool equal(const Myclass<T>&, const Myclass<T>&);

template <typename T>
class Myclass{ 
public:
   Myclass(int, T, T);
   friend bool equal<T>(const Myclass<T>&, const Myclass<T>&);
private: 
   int a_; 
   T b_; 
   T *c_; 
};  


/*
template <typename T>
class Myclass{
public:
   Myclass(int, T, T);
   // defines friend to all instantiated classes
   template <typename U>
   friend bool equal(const Myclass<U>&, const Myclass<U>&);
private:
   int a_;
   T b_;
   T *c_;
};
*/

// constructor definition
template <typename T>
Myclass<T>::Myclass(int a, T b, T c): a_(a), b_(b), c_(new T(c)) {}


Myclass<double> ob2(1, 2.5, 3.45); // global object

// malicious friend function definition
// that accesses private members of unrelated template insantiation
template<typename X>
bool equal(const Myclass <X> &x, const Myclass<X> &y) {
   cout << "I can access things I probably should not: " << ob2.b_ << endl;
   return true;
}

int main(){
   Myclass<char> ob1(1, 'a', 'b');
   if(equal(ob1,ob1))
      cout << "checking friend" << endl; 
}
