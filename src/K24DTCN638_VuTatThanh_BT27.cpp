#include <fstream>
#include <iostream>
#include <string>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT27.h"



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
        std::unique_ptr<std::vector<std::vector<int>>>A = read_and_validate_matrix(file, n);
        if (A == nullptr) return 2;
        if (!std::getline(file, line)) {
            std::cerr << "Khong co dong tiep theo" << std::endl;
            return 2;
        }
        int m = parse_int(line);
        if (m < 0) return 2;
        if (m < 3) {
            std::cerr << "n phai lon hon 3" << std::endl;
            return 2;
        }
        if (m > 100) {
            std::cerr << "n phai nho hon 100" << std::endl;
            return 2;
        }
        std::unique_ptr<std::vector<std::vector<int>>>B = read_and_validate_matrix(file, m);
        if (B == nullptr) return 2;
        print_convolution_matrix(A, B, n, m);
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

std::unique_ptr<std::vector<std::vector<int>>> read_and_validate_matrix(std::ifstream file, int size) {
    std::string line;
    std::unique_ptr<std::vector<std::vector<int>>>matrix(new std::vector<std::vector<int>>(size, std::vector<int>(size)));
    for (int j = 0; j < size; ++j) {
        if (!std::getline(file, line)) {
            std::cerr << "Khong co dong tiep theo" << std::endl;
            return nullptr;
        }
        const std::vector<int> arr = string_to_int_vector(line, size);
        for (int k = 0; k < size; ++k) {
            const int e = arr[k];
            if (e > 1000) {
                std::cerr << "Phan tu phai nho hon hoac bang 1000" << std::endl;
                return nullptr;
            }
            (*matrix)[j][k] = e;
        }
    }
    return matrix;
}

void print_convolution_matrix(const std::vector<std::vector<int>> &A, const std::vector<std::vector<int>> &B, const int M, const int N) {
    int step = N / M; // Số lần trượt theo hàng và cột

    // Duyệt qua từng khung MxM của A
    for (int i = 0; i < N; i += M) {
        for (int j = 0; j < N; j += M) {
            int sum = 0;

            // Tính tích chập giữa khung MxM và B
            for (int x = 0; x < M; ++x)
                for (int y = 0; y < M; ++y)
                    sum += A[i + x][j + y] * B[x][y];

            std::cout << sum << " ";
        }
        std::cout << std::endl;
    }
}
