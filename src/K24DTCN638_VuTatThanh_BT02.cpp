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
    if (!std::getline(file, line)) {
        std::cerr << "Khong co dong tiep theo" << std::endl;
        return 2;
    }
    int total_tests = parse_int(line);
    if (total_tests < 1 || total_tests > 100) {
        std::cerr << "T phai lon hon hoac bang 1 va nho hon hoac bang 100" << std::endl;
        return 2;
    }
    for (int i = 0; i < total_tests; i++) {
        // Xử lý dòng đọc được
        if (!std::getline(file, line)) {
            std::cerr << "Khong co dong tiep theo" << std::endl;
            return 2;
        }
        const char c = parse_char(line);
        if (c < 0) {
            return 2;
        }
        std::cout << convert_char(c) << std::endl;
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
