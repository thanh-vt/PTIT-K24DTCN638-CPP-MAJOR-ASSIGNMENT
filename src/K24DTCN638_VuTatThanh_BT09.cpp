#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT09.h"


int main() {
    std::string filename = "K24DTCN638_VuTatThanh_BT09.txt";
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
        if (!std::getline(file, line)) {
            std::cerr << "Khong co dong tiep theo" << std::endl;
            return 2;
        }
        const int n = parse_int(line);
        if (n < 0) return 2;
        if (n < 1) {
            std::cout << "N phai lon hon hoac bang 1" << std::endl;
            return 2;
        }
        if (n > 1000000) {
            std::cout << "N phai nho hon hoac bang 1000000" << std::endl;
            return 2;
        }
        if (!std::getline(file, line)) {
            std::cerr << "Khong co dong tiep theo" << std::endl;
            return 2;
        }
        const std::vector<int> A = string_to_int_vector(line, n);
        const int min_diff = find_min_diff(A);
        std::cout << min_diff << std::endl;
    }
    file.close();

    return 0;
}

int find_min_diff(std::vector<int> A) {
    sort(A.begin(), A.end());
    int min_diff = INT_MAX;
    for (int i = 0; i < A.size() - 1; i++) {
        const int diff = A[i+1] - A[i];
        if (diff < min_diff) {
            min_diff = diff;
        }
    }
    return min_diff;
}
