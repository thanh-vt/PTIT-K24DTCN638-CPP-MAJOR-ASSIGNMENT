#include <fstream>
#include <iostream>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT20.h"


int main() {
    const std::string filename = "K24DTCN638_VuTatThanh_BT20.txt";
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
    std::string hoten = trim(line);
    if (line.size() > 50) {
        std::cerr << "Ho ten khong vuot qua 50 chu cai" << std::endl;
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
