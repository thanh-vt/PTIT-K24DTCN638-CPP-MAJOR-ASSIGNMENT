#include <fstream>
#include <iostream>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT02.h"

int main() {
    std::string filename = "K24DTCN638_VuTatThanh_BT02.txt";
    std::ifstream file(filename); // Mở file để đọc
    if (!file) {
        std::cerr << "Khong the mo file input " << filename << std::endl;
        return 1;
    }

    std::string line;
    int total_tests = 0;
    while (std::getline(file, line)) {
        // Xử lý dòng đọc được
        if (total_tests == 0) {
            total_tests = parse_int(line);
            if (total_tests <= 1) {
                return 2;
            }
        } else {
            const char c = parse_char(line);
            if (c < 0) {
                return 2;
            }
            std::cout << convert_char(c) << std::endl;
        }
    }

    file.close();

    return 0;
}

char convert_char(const char c) {
    if (std::islower(c)) {
        return static_cast<char>(std::toupper(c));
    }
    if (std::isupper(c)) {
        return static_cast<char>(std::tolower(c));
    }
    return c;
}
