#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT12.h"

int main() {
    const std::string filename = "K24DTCN638_VuTatThanh_BT12.txt";
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
        std::regex ws_re(" +"); // ttách chuỗi bởi khoảng trắng
        std::sregex_token_iterator iter(line.begin(), line.end(), ws_re, -1);
        std::sregex_token_iterator end;
        std::vector<std::string> result(iter, end);
        if (result.size() != 2) {
            std::cerr << "Dong phai co 2 so n, m" << std::endl;
            return 2;
        }
        int n = parse_int(result[0]);
        if (n < 0) return 2;
        if (n < 1) {
            std::cerr << "n phai lon hon hoac bang 1" << std::endl;
            return 2;
        }
        if (n > 100) {
            std::cerr << "n phai nho hon hoac bang 100" << std::endl;
            return 2;
        }
        const int m = parse_int(result[1]);
        if (m < 0) return 2;
        if (m < 1) {
            std::cerr << "m phai lon hon hoac bang 1" << std::endl;
            return 2;
        }
        if (m > 100) {
            std::cerr << "m phai nho hon hoac bang 100" << std::endl;
            return 2;
        }

        std::vector<std::vector<int> > A(n, std::vector<int>(m));
        for (int j = 0; j < n; ++j) {
            if (!std::getline(file, line)) {
                std::cerr << "Khong co dong tiep theo" << std::endl;
                return 2;
            }
            const std::vector<int> arr = string_to_int_vector(line, m);
            A[j] = arr;
        }
        print_modified_matrix(A, n, m);
    }
    file.close();

    return 0;
}

void print_modified_matrix(std::vector<std::vector<int> > A, const int n, const int m) {
    std::vector<bool> row_flag(n, false);
    std::vector<bool> col_flag(m, false);

    // Tìm hàng và cột có phần tử = 1
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (A[i][j] == 1) {
                row_flag[i] = true;
                col_flag[j] = true;
            }
        }
    }

    // Biến đổi ma trận theo row_flag và col_flag
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (row_flag[i] || col_flag[j]) {
                A[i][j] = 1;
            }
        }
    }

    // In ra kết quả theo yêu cầu: mỗi test trên 1 dòng, in nối các phần tử
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << A[i][j];
            if (i != n - 1 || j != m - 1) std::cout << " ";
        }
        std::cout << std::endl;
    }
}
