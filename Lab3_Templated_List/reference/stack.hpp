// templated stack implementation
// demonstrates non-type parameter use
// Mikhail Nesterenko
// 8/30/2024

#ifndef STACK_HPP_
#define STACK_HPP_

template<typename T=int, int Size=52>
class Stack {
public:
    Stack():top_(-1){}
    void push(T);
    T pop();
    bool full() const;
    bool empty() const;
private:
    T items_[Size];
    int top_;
};

template<typename T, int Size>
bool Stack<T,Size>::full() const{  
   return top_ + 1 == Size; 
}

template<typename T, int Size>
bool Stack<T,Size>::empty() const{  
   return top_ == -1; 
}


template<typename T, int Size>
void Stack<T,Size>::push(T i){  
   if(!full())  items_[++top_] = i;
}

template<typename T, int Size>
T Stack<T,Size>::pop(){
   // if(!empty()) return items_[top_--]; 
   return !empty() ? items_[top_--] : T(); 
}


#endif // STACK_HPP_
