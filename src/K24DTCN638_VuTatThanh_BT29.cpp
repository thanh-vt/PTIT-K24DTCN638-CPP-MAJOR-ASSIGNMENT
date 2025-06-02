#include <cctype>
#include <fstream>
#include <iostream>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT29.h"

// TÍNH TỔNG CÁC SỐ TRONG XÂU
int main() {
    const std::string filename = "K24DTCN638_VuTatThanh_BT29.txt";
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
        if (line.size() > 100000) {
            std::cerr << "Length(S) phai nho hon hoac bang 100000" << std::endl;
            return 2;
        }
        const int sum = sum_of_numbers(line);
        std::cout << sum << std::endl;
    }
    file.close();

    return 0;
}

int sum_of_numbers(const std::string& S) {
    int totalSum = 0;
    int currentNumber = 0;
    
    for (const char c : S) {
        if (std::isdigit(c)) {
            // Nếu là chữ số, tích lũy vào số hiện tại
            currentNumber = currentNumber * 10 + (c - '0');
        } else {
            // Nếu gặp ký tự khác, cộng số hiện tại vào tổng (nếu có)
            totalSum += currentNumber;
            currentNumber = 0; // Reset số tạm thời
        }
    }

    // Cộng số còn lại nếu xâu kết thúc và có số chưa được cộng
    totalSum += currentNumber;
    
    return totalSum;
}
