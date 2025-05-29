#include <fstream>
#include <iostream>
#include <string>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT11.h"

#include <regex>


int main() {
    const std::string filename = "K24DTCN638_VuTatThanh_BT11.txt";
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
        std::regex ws_re(" +");  // ttách chuỗi bởi khoảng trắng
        std::sregex_token_iterator iter(line.begin(), line.end(), ws_re, -1);
        std::sregex_token_iterator end;
        std::vector<std::string> result(iter, end);
        if (result.size() != 2) {
            std::cerr << "Dong phai co 2 so n, d" << std::endl;
            return 2;
        }
        int n = parse_int(result[0]);
        if (n < 0) return 2;
        if (n < 1) {
            std::cerr << "n phai lon hon hoac bang 1" << std::endl;
            return 2;
        }
        if (n > 1000000) {
            std::cerr << "n phai nho hon hoac bang 1000000" << std::endl;
            return 2;
        }
        const int d = parse_int(result[1]);
        if (d < 0) return 2;
        if (d < 1) {
            std::cerr << "d phai lon hon hoac bang 1" << std::endl;
            return 2;
        }
        if (d > 1000000) {
            std::cerr << "d phai nho hon hoac bang 1000000" << std::endl;
            return 2;
        }
        if (d >= n) {
            std::cerr << "d phai nho hon hoac bang n" << std::endl;
            return 2;
        }
        if (!std::getline(file, line)) {
            std::cerr << "Khong co dong tiep theo" << std::endl;
            return 2;
        }
        const std::vector<int> A = string_to_int_vector(line, n);
        print_rotated_vector(A, n, d);
    }
    file.close();

    return 0;
}

void print_rotated_vector(const std::vector<int>& A, const int n, const int d) {
    std::vector<int> rotated(n);
    // Copy từ A[d..n-1]
    for (int i = 0; i < n - d; i++) {
        rotated[i] = A[i + d];
    }
    // Copy từ A[0..d-1]
    for (int i = n - d; i < n; i++) {
        rotated[i] = A[i - (n - d)];
    }

    for (int i = 0; i < n; i++) {
        std::cout << rotated[i];
        if (i < n - 1) std::cout << " ";
    }
    std::cout << std::endl;
}
