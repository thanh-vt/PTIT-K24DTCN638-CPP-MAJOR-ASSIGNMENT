#include <complex>
#include <fstream>
#include <iostream>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT04.h"

int main() {
    std::string filename = "K24DTCN638_VuTatThanh_BT04.txt";
    std::ifstream file(filename); // Mở file để đọc
    if (!file) {
        std::cerr << "Khong the mo file input " << filename << std::endl;
        return 1;
    }

    std::string line;
    if (std::getline(file, line)) {
        // Xử lý dòng đọc được
        const int n = parse_int(line);
        if (n < 0) return 2;
        if (n > 20) {
            std::cerr << "N phai nho hon 20" << std::endl;
            return 2;
        }
        if (n % 2 == 0) {
            const int start = static_cast<int>(std::pow(10, n - 1));
            const int end = static_cast<int>(std::pow(10, n)) - 1;
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
            std::cerr << "N phai la so chan" << std::endl;
        }
    }

    file.close();

    return 0;
}

bool has_equal_odd_even_digits(int n) {
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