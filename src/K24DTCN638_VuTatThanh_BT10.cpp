#include <fstream>
#include <iostream>
#include <string>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT10.h"


int main() {
    const std::string filename = "K24DTCN638_VuTatThanh_BT10.txt";
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
        std::cout << find_smallest_missing_positive(A, n) << std::endl;
    }
    file.close();

    return 0;
}

int find_smallest_missing_positive(const std::vector<int>& arr, const int n) {
    std::vector<bool> present(n + 2, false); // đánh dấu số từ 1 đến n+1

    for (const int x : arr) {
        if (x >= 1 && x <= n + 1) {
            present[x] = true;
        }
    }

    for (int i = 1; i <= n + 1; i++) {
        if (!present[i]) return i;
    }
    return n + 1; // trường hợp này ít xảy ra vì đã kiểm tra hết
}
