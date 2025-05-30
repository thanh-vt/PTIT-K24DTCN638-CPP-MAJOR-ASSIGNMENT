#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT15.h"

// ĐẾM SỐ PHẦN TỬ LẶP LẠI
int main() {
    const std::string filename = "K24DTCN638_VuTatThanh_BT15.txt";
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
        if (n > 1000000) {
            std::cerr << "n phai nho hon hoac bang 1000000" << std::endl;
            return 2;
        }

        if (!std::getline(file, line)) {
            std::cerr << "Khong co dong tiep theo" << std::endl;
            return 2;
        }
        const std::vector<int> A = string_to_int_vector(line, n);
        for (int j = 0; j < n; j++) {
            if (A[j] > 1000000) {
                std::cerr << "A[i] phai nho hon hoac bang 1000000" << std::endl;
                return 2;
            }
        }
        const int count = count_array_duplicated_elements(A, n);

        std::cout << count << std::endl;
    }

    file.close();

    return 0;
}

int count_array_duplicated_elements(const std::vector<int> &A, const int n) {
    std::unordered_map<int, int> freq;

    for (int i = 0; i < n; i++) {
        freq[A[i]]++;
    }

    int count = 0;
    for (const auto& p : freq) {
        if (p.second >= 2) count += p.second;
    }
    return count;
}
