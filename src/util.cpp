#include "util.h"

#include <iostream>

int parse_int(std::string line) {
    try {
        return std::stoi(line);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Chuoi khong phai so hop le\n";
    } catch (const std::out_of_range& e) {
        std::cerr << "So vuot qua pham vi integer\n";
    }
    return -1;
}
