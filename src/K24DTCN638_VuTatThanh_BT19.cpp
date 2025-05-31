#include <fstream>
#include <iostream>
#include <string>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT19.h"

// SẮP XẾP CHỮ SỐ
int main() {
    const std::string filename = "K24DTCN638_VuTatThanh_BT19.txt";
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
    const int total_tests = parse_int(line);
    if (total_tests < 1 || total_tests > 100) {
        std::cerr << "T phai lon hon hoac bang 1 va nho hon hoac bang 100" << std::endl;
        return 2;
    }
    for (int i = 0; i < total_tests; i++) {
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
        if (n > 10000000) {
            std::cerr << "n phai nho hon hoac bang 10000000" << std::endl;
            return 2;
        }

        if (!std::getline(file, line)) {
            std::cerr << "Khong co dong tiep theo" << std::endl;
            return 2;
        }
        const std::vector<long> A = string_to_long_vector(line, n);
        for (int j = 0; j < n; j++) {
            if (A[j] > 10000000000000000) {
                std::cerr << "A[i] phai nho hon hoac bang 1000000" << std::endl;
                return 2;
            }
        }
        std::set<int> digit_set = sort_digits_array(A, n);

        for (const int d: digit_set) {
            std::cout << d << " ";
        }
        std::cout << std::endl;
    }

    file.close();

    return 0;
}

std::set<int> sort_digits_array(const std::vector<long> &A, int n) {
    std::set<int> digits_set;
    for (int i = 0; i < n; ++i) {
        std::string s = std::to_string(A[i]);
        for (const char c: s) {
            if (std::isdigit(c)) {
                digits_set.insert(c - '0');
            }
        }
    }
    // set tự động sắp xếp
    return digits_set;
}
