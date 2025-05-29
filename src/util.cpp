#include "util.h"
#include <iostream>

char parse_char(const std::string &line) {
    if (line.size() != 1) {
        std::cerr << "Chuoi khong phai chu cai hop le\n";
        return -1;
    }
    const char c = line[0];
    if (isalpha(c)) {
        return c;
    }
    std::cerr << "Chuoi khong phai chu cai hop le\n";
    return -1;
}

int parse_int(const std::string &line) {
    try {
        return std::stoi(line);
    } catch (const std::invalid_argument &e) {
        std::cerr << "Chuoi khong phai so integer hop le\n";
    } catch (const std::out_of_range &e) {
        std::cerr << "So vuot qua pham vi integer\n";
    }
    return -1;
}

long parse_long(const std::string &line) {
    try {
        return std::stol(line);
    } catch (const std::invalid_argument &e) {
        std::cerr << "Chuoi khong phai so long hop le\n";
    } catch (const std::out_of_range &e) {
        std::cerr << "So vuot qua pham vi long\n";
    }
    return -1;
}

std::vector<int> string_to_int_vector(const std::string& s, const size_t size) {
    std::vector<int> result;
    std::istringstream iss(s);
    int number;
    while (result.size() < size && iss >> number) {
        result.push_back(number);
    }
    return result;
}
