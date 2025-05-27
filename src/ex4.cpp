//
// Created by thanhvt on 27/05/2025.
//

#include "ex4.h"
#include <iostream>

Ex4::~Ex4() {
    std::cout << "Exercise 4 finished.\n";
}

void Ex4::process() {
    const int n = getQuantityInput(std::string("Enter N:"));
    if (n % 2 == 0) {

    } else {
        std::cerr << "N must be even.\n";
    }
}