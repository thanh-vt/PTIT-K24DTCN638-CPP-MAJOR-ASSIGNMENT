#include "ex7.h"

#include <iostream>


Ex7::~Ex7() {
    std::cout << "Exercise 7 finished.\n";
}


void Ex7::process() {
    int n = getQuantityInput(std::string("Enter N:"));
    if (n <= 1) {
        std::cout << "N should be greater than 1." << std::endl;
        return;
    }
    if (n > 10000000000) {
        std::cout << "N should be less than 10000000000." << std::endl;
        return;
    }
    std::cout << "Prime factorization of " << n << ": ";

    while (n % 2 == 0) {
        std::cout << 2 << " ";
        n /= 2;
    }

    for (int i = 3; i * i <= n; i += 2) {
        while (n % i == 0) {
            std::cout << i << " ";
            n /= i;
        }
    }

    if (n > 2) {
        std::cout << n;
    }

    std::cout << std::endl;
}
