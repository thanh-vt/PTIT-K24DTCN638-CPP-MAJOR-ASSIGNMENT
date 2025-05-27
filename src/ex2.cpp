#include "ex2.h"

#include <iostream>

Ex2::~Ex2() {
    std::cout << "Exercise 2 finished.\n";
}

void Ex2::process() {
    std::cout << "Enter a character:" << std::endl;
    char c;
    std::cin >> c;
    if (std::islower(c)) {
        char upper_char = std::toupper(c);
        std::cout << "Uppercase equivalent: " << upper_char << std::endl;
    } else if (std::isupper(c)) {
        char lower_char = std::tolower(c);
        std::cout << "Lower case equivalent: " << lower_char << std::endl;
    } else {
        std::cerr << "Invalid character." << std::endl;
    }
}