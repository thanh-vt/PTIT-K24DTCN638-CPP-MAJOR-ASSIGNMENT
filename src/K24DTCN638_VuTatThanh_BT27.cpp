//
// Created by pysga1996 on 01/06/2025.
//

#include "K24DTCN638_VuTatThanh_BT27.h"

#include <fstream>
#include <iostream>
#include <string>

#include "util.h"

int main() {
    const std::string filename = "K24DTCN638_VuTatThanh_BT27.txt";
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
        int n = parse_int(line);
        if (n < 0) return 2;
        if (n < 3) {
            std::cerr << "n phai lon hon 3" << std::endl;
            return 2;
        }
        if (n > 100) {
            std::cerr << "n phai nho hon 100" << std::endl;
            return 2;
        }

        std::vector<std::vector<int> > A(n, std::vector<int>(m));

        if (!std::getline(file, line)) {
            std::cerr << "Khong co dong tiep theo" << std::endl;
            return 2;
        }
        const std::vector<int> arr = string_to_int_vector(line, n * n);
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < m; ++k) {
                const int e = arr[j * m + k];
                if (e > 100000) {
                    std::cerr << "Phan tu phai nho hon hoac bang 100000" << std::endl;
                    return 2;
                }
                A[j][k] = e;
            }
        }
        rotate_matrix(A, n, m);
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < m; ++k) {
                std::cout << A[j][k] << " ";
            }
        }
        std::cout << std::endl;
    }
    file.close();

    return 0;
}
