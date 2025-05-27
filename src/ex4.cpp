#include "ex4.h"
#include <cmath>
#include <iostream>

Ex4::~Ex4() {
    std::cout << "Exercise 4 finished.\n";
}

bool Ex4::has_equal_odd_even_digits(int n) {
    int oddCount = 0, evenCount = 0;

    while (n > 0) {
        int digit = n % 10;
        if (digit % 2 == 0)
            evenCount++;
        else
            oddCount++;
        n /= 10;
    }

    return oddCount == evenCount;
}

void Ex4::process() {
    int n = getQuantityInput(std::string("Enter N:"));
    if (n % 2 == 0) {
        int start = static_cast<int>(std::pow(10, n - 1));
        int end = static_cast<int>(std::pow(10, n)) - 1;
        int count = 0;
        for (int num = start; num <= end; ++num) {
            if (has_equal_odd_even_digits(num)) {
                count ++;
                std::cout << num << " ";
                if (count % 10 == 0) {
                    std::cout << std::endl;
                }
            }
        }
        std::cout << std::endl;
    } else {
        std::cerr << "N must be even." << std::endl;
    }
}