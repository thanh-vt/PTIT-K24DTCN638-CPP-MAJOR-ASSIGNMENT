#include "ex5.h"
#include <iostream>

Ex5::~Ex5() {
    std::cout << "Exercise 5 finished.\n";
}

void Ex5::process() {
    const int n = getQuantityInput(std::string("Enter N:"));
    int sum = 0;
    int product = 1;
    for (int i = 1; i <= n; i++) {
        product *= i;
        sum += product;
    }
    std::cout << "S = 1 + 1.2 + 1.2.3 + ...+ 1.2.3...N = " << sum << std::endl;
}