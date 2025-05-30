#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include <set>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT14.h"

// LIỆT KÊ SỐ KHÁC NHAU
int main() {
    const std::string filename = "K24DTCN638_VuTatThanh_BT14.txt";
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
    const int n = parse_int(line);
    if (n < 0) return 2;
    if (n < 1) {
        std::cerr << "n phai lon hon hoac bang 1" << std::endl;
        return 2;
    }
    if (n > 100) {
        std::cerr << "n phai nho hon hoac bang 100" << std::endl;
        return 2;
    }

    if (!std::getline(file, line)) {
        std::cerr << "Khong co dong tiep theo" << std::endl;
        return 2;
    }
    const std::vector<int> A = string_to_int_vector(line, n);
    print_unique_element(A);

    file.close();

    return 0;
}

void print_unique_element(const std::vector<int> &A) {
    std::set<int> unique_numbers;
    for (const int x: A) {
        unique_numbers.insert(x);
    }

    bool first = true;
    for (const int num: unique_numbers) {
        if (!first) std::cout << " ";
        std::cout << num;
        first = false;
    }
    std::cout << std::endl;
}
