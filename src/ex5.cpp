#include "ex5.h"
#include <iostream>

Ex5::~Ex5() {
    std::cout << "Exercise 5 finished.\n";
}

void Ex5::process() {
    const int x = getQuantityInput(std::string("Enter X:"));
    if (x > 999999999) {
        std::cerr << "X length must be less than 10";
        return;
    }
    std::cout << (x % 100 == 86) << std::endl;
}
