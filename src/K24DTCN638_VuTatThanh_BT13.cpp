#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT13.h"


int main() {
    const std::string filename = "K24DTCN638_VuTatThanh_BT13.txt";
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
        if (n > 100) {
            std::cerr << "n phai nho hon hoac bang 100" << std::endl;
            return 2;
        }

        std::vector<std::vector<int> > A(n, std::vector<int>(n));
        if (!std::getline(file, line)) {
            std::cerr << "Khong co dong tiep theo" << std::endl;
            return 2;
        }
        const std::vector<int> arr = string_to_int_vector(line, n * n);
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                const int e = arr[j * n + k];
                if (e > 150) {
                    std::cerr << "Phan tu phai nho hon hoac bang 150" << std::endl;
                    return 2;
                }
                A[j][k] = e;
            }
        }
        print_matrix_borders(A, n);
    }
    file.close();

    return 0;
}

void print_matrix_borders(const std::vector<std::vector<int> > &A, const int n) {

    // In dòng đầu đầy đủ
    for (int j = 0; j < n; j++) {
        std::cout << A[0][j];
        if (j < n - 1) std::cout << " ";
    }
    std::cout << std::endl;

    // In các dòng giữa: phần tử đầu, 4 dấu cách, phần tử cuối
    for (int i = 1; i < n - 1; i++) {
        std::cout << A[i][0];
        std::cout << "    ";  // 4 dấu cách
        std::cout << A[i][n - 1] << std::endl;
    }

    // In dòng cuối đầy đủ
    for (int j = 0; j < n; j++) {
        std::cout << A[n - 1][j];
        if (j < n - 1) std::cout << " ";
    }
    std::cout << std::endl;
}
