#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP

#include <iostream>
#include <string>

#include "drink.hpp"

using String = std::string;

class Customer {
    public:
        Customer(String name) : name_(name) {};
        ~Customer() { delete drink_; };

        String getName() {return name_;};
        
        void notify(Drink* drink) { 
            drink_ = drink; 
            std::cout << "This is "+name_+", I got my coffee, thank you!\n";
        };

    private:
        String name_;
        Drink* drink_;
};

#endif
