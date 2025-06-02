#include <fstream>
#include <iostream>
#include <string>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT27.h"

// CỬA SỔ TRƯỢT
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
    const int N = parse_int(line);
    if (N < 0) return 2;
    if (N <= 3) {
        std::cerr << "N phai lon hon 3" << std::endl;
        return 2;
    }
    if (N >= 100) {
        std::cerr << "N phai nho hon 100" << std::endl;
        return 2;
    }
    std::vector<std::vector<int>>A(N, std::vector<int>(N));
    for (int j = 0; j < N; ++j) {
        if (!std::getline(file, line)) {
            throw std::runtime_error("Khong co dong tiep theo");
        }
        const std::vector<int> arr = string_to_int_vector(line, N);
        for (int k = 0; k < N; ++k) {
            const int e = arr[k];
            if (e < 1) {
                std::cerr << "Phan tu cua ma tran A phai la so nguyen duong" << std::endl;
                return 2;
            }
            if (e > 1000) {
                std::cerr << "Phan tu cua ma tran A phai nho hon hoac bang 1000" << std::endl;
            }
            A[j][k] = e;
        }
    }
    if (!std::getline(file, line)) {
        std::cerr << "Khong co dong tiep theo" << std::endl;
        return 2;
    }
    const int M = parse_int(line);
    if (M < 0) return 2;
    if (M < 1) {
        std::cerr << "M phai lon hon 1" << std::endl;
        return 2;
    }
    if (M > 10) {
        std::cerr << "M phai nho hon 10" << std::endl;
        return 2;
    }
    std::vector<std::vector<int>>B(M, std::vector<int>(M));
    for (int j = 0; j < M; ++j) {
        if (!std::getline(file, line)) {
            throw std::runtime_error("Khong co dong tiep theo");
        }
        const std::vector<int> arr = string_to_int_vector(line, N);
        for (int k = 0; k < M; ++k) {
            const int e = arr[k];
            if (e < 0) {
                std::cerr << "Phan tu cua ma tran B phai lon hon hoac bang 0" << std::endl;
                return 2;
            }
            if (e > 20) {
                std::cerr << "Phan tu cua ma tran B phai nho hon hoac bang 20" << std::endl;
            }
            B[j][k] = e;
        }
    }
    file.close();
    const std::vector<std::vector<int>> result = print_convolution_matrix(A, B, M, N);
    // In ra ma trận kết quả
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << result[i][j];
            if (j < N - 1) std::cout << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}

std::vector<std::vector<int>> print_convolution_matrix(const std::vector<std::vector<int>> &A, const std::vector<std::vector<int>> &B, const int M, const int N) {
    // Tạo ma trận kết quả
    std::vector<std::vector<int>> result(N, std::vector<int>(N, 0));
    // Tính tích chập
    for (int i = 0; i <= N - M; i += M) {
        for (int j = 0; j <= N - M; j += M) {
            // Lặp qua các phần tử trong cửa sổ trượt MxM
            for (int k = 0; k < M; k++) {
                for (int l = 0; l < M; l++) {
                    // Tính tích của mỗi phần tử tương ứng trong A và B
                    result[i + k][j + l] = A[i + k][j + l] * B[k][l];
                }
            }
        }
    }
    return result;
}
