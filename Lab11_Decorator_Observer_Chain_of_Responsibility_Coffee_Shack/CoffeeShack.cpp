#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>

#include "drink.hpp"
#include "barista.hpp"
#include "customer.hpp"

using String = std::string;

int main() {
    // setup
    std::srand(std::time(nullptr));
    
    String passingPhrase = "pass";
    
    Barista* worker = new Barista(new JuniorBarista(new SeniorBarista(new Manager())));
    Drink* coffee = nullptr;

    std::ifstream inputFile("input.txt"); // Open the input file
    std::istream* input = &std::cin;     // Default to standard input
    if (inputFile.is_open()) {
        input = &inputFile; // Use the file as the input stream initially
    }

    std::cout << "Coffee Shack Is Open! ctrl+c to close\n\n";
    while (true) {
        if (rand() % 2 == 0 || !worker->hasOrders()) {
            // ask customer for drink size
            String result;
            do {
                std::cout << "Welcome to Coffee Shack, can I get you [l]arge, [m]edium, or [s]mall coffee? m: ";
                getline(*input, result);
                if (input->eof()) { // If end of file is reached, switch to standard input
                    input = &std::cin;
                }
            } while (result != "l" && result != "m" && result != "s" && result != "large" && result != "medium" && result != "small" && result != passingPhrase);

            if (result == "l" || result == "large") {
                coffee = new Drink(DrinkType::large);
            } else if (result == "m" || result == "medium") {
                coffee = new Drink(DrinkType::medium);
            } else if (result == "s" || result == "small") {
                coffee = new Drink(DrinkType::small);
            }

            // ask customer for ingredients until [d]one
            while (result != "d" && result != "done" && result != passingPhrase) {
                std::cout << "Would you like to add [s]ugar, [c]ream, [h]oney, or [d]one? ";
                getline(*input, result);
                if (input->eof()) { // If end of file is reached, switch to standard input
                    input = &std::cin;
                }
                if (result == "s" || result == "sugar") {
                    coffee = new Sugar(coffee);
                } else if (result == "c" || result == "cream") {
                    coffee = new Cream(coffee);
                } else if (result == "h" || result == "honey") {
                    coffee = new Honey(coffee);
                }
            }

            // ask customer for name
            if(result != passingPhrase) {
                std::cout << "Can I get your name? ";
                getline(*input, result);
                if (input->eof()) { // If end of file is reached, switch to standard input
                    input = &std::cin;
                }
                coffee->setName(result);
    
                worker->ticketDrink(new Customer(result), coffee);
            }
        } else {
            worker->finishDrink();
        }
        std::cout << std::endl;
    }

    delete worker;
    delete coffee;
    return 0;
}