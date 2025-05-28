#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include "util.h"

int sum_1_to_n(int n);

int main() {
    std::ifstream file("K24DTCN638_VuTatThanh_BT01.txt"); // Mở file để đọc
    if (!file) {
        std::cerr << "Khong the mo file input K24DTCN638_VuTatThanh_BT01.txt\n";
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
            const int n = parse_int(line);
            if (n < 0) {
                return 2;
            }
            std::cout << sum_1_to_n(n) << std::endl;
        }
    }

    file.close();

    return 0;
}

int sum_1_to_n(const int n) {
    return (1 + n) * n / 2;
}
