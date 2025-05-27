#include "ex1.h"

#include <iostream>
#include <ostream>
#include <string>


Ex1::~Ex1() {
    std::cout << "Exercise 1 finished.\n";
}

void Ex1::process() {
    const int n = getQuantityInput(std::string("Enter N:"));
    const int sum = (1 + n) * n / 2;
    std::cout << "S = 1 + 1.2 + 1.2.3 + ...+1.2.3...N = " << sum << std::endl;
}
