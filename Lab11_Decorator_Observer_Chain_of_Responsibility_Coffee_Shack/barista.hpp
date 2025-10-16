#ifndef BARISTA_HPP
#define BARISTA_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "drink.hpp"
#include "customer.hpp"

using String = std::string;

class Barista {
    public:
        Barista(Barista* higherPos=nullptr) : moreQualified(higherPos) {};
        virtual ~Barista() {
            for (auto customer : customers_) {
            delete customer;
            }
            for (auto drink : drinks_) {
            delete drink;
            }
        };

        bool hasOrders() const { 
            if (!drinks_.empty()) {
                return true;
            }
            if (moreQualified != nullptr) {
                return moreQualified->hasOrders();
            }
            return false;
        };
        void finishDrink() {
            std::vector<Drink*> tempV = collectAllDrinks();
            Drink* temp = tempV[rand()%tempV.size()];
            notifyCustomers(temp);
        };
        virtual void ticketDrink(Customer* customer, Drink* drink) {
            if (moreQualified != nullptr) {
                moreQualified->ticketDrink(customer, drink);
            } else {
                std::cout << "Nobody can handle this request!\n";
            }
        };

    protected:
        virtual void notifyCustomers(Drink* drink) {
            if (moreQualified != nullptr) {
                moreQualified->notifyCustomers(drink);
            }
        };
        std::vector<Drink*> collectAllDrinks() const {
            std::vector<Drink*> allDrinks = drinks_; // Start with the current barista's drinks
            if (moreQualified != nullptr) {
                std::vector<Drink*> higherDrinks = moreQualified->collectAllDrinks();
                allDrinks.insert(allDrinks.end(), higherDrinks.begin(), higherDrinks.end());
            }
            return allDrinks;
        };

        Barista* moreQualified;
        std::vector<Customer*> customers_;
        std::vector<Drink*> drinks_;
};

class JuniorBarista : public Barista {
    public:
        JuniorBarista(Barista* higherPos=nullptr) : Barista(higherPos) {};
        virtual void ticketDrink(Customer* customer, Drink* drink) override {
            if (drink->getIngredient() == "") {
                Barista::customers_.push_back(customer);
                Barista::drinks_.push_back(drink);
                std::cout << "Please Wait " + customer->getName() + " While a Junior Barista Handles Your Request!\n";
            } else {
                Barista::ticketDrink(customer, drink);
            }
        };

    protected:
        virtual void notifyCustomers(Drink* drink) override {
            auto it = std::find(drinks_.begin(), drinks_.end(), drink);
            if (it != drinks_.end()) {
                std::cout << drink->getName()+", your "+drink->getType()+" coffee with "+drink->getIngredient()+" is ready. It is prepared by a Junior Barista. It will be $"<<drink->getPrice()<<", please.\n";
                for (auto customer : customers_) {
                    if (customer->getName() == drink->getName()) {
                        customer->notify(drink);
                    }
                }
                drinks_.erase(it);
            } else {
                Barista::notifyCustomers(drink);
            }
        };
};

class SeniorBarista : public Barista {
    public:
        SeniorBarista(Barista* higherPos=nullptr) : Barista(higherPos) {};
        virtual void ticketDrink(Customer* customer, Drink* drink) override {
            if (drink->getIngredient().find("honey") == std::string::npos) {
                Barista::customers_.push_back(customer);
                Barista::drinks_.push_back(drink);
                std::cout << "Please Wait " + customer->getName() + " While a Senior Barista Handles Your Request!\n";
            } else {
                Barista::ticketDrink(customer, drink);
            }
        };

    protected:
        virtual void notifyCustomers(Drink* drink) override {
            auto it = std::find(drinks_.begin(), drinks_.end(), drink);
            if (it != drinks_.end()) {
                std::cout << drink->getName()+", your "+drink->getType()+" coffee with "+drink->getIngredient()+" is ready. It is prepared by a Senior Barista. It will be $"<<drink->getPrice()<<", please.\n";
                for (auto customer : customers_) {
                    if (customer->getName() == drink->getName()) {
                        customer->notify(drink);
                    }
                }
                drinks_.erase(it);
            } else {
                Barista::notifyCustomers(drink);
            }
        };
};

class Manager : public Barista {
    public:
        Manager(Barista* higherPos=nullptr) : Barista(higherPos) {};
        virtual void ticketDrink(Customer* customer, Drink* drink) override { 
            Barista::customers_.push_back(customer);
            Barista::drinks_.push_back(drink);
            std::cout << "Please Wait " + customer->getName() + " While a Manager Handles Your Request!\n";
        };

    protected:
        virtual void notifyCustomers(Drink* drink) override {
            auto it = std::find(drinks_.begin(), drinks_.end(), drink);
            std::cout << drink->getName()+", your "+drink->getType()+" coffee with "+drink->getIngredient()+" is ready. It is prepared by a Manager. It will be $"<<drink->getPrice()<<", please.\n";
            for (auto customer : customers_) {
                    if (customer->getName() == drink->getName()) {
                        customer->notify(drink);
                    }
                }
            drinks_.erase(it);
        };
};

#endif
