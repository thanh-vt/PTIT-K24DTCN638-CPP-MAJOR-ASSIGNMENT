#include <string>
#include <fstream>
#include <iostream>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT28.h"

// ĐỔI CHỖ CHỮ SỐ
int main() {
    const std::string filename = "K24DTCN638_VuTatThanh_BT28.txt";
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
        if (n > 100000) {
            std::cerr << "n phai nho hon hoac bang 100000" << std::endl;
            return 2;
        }
        const int swap_count = find_largest_smaller_number(n);
        std::cout << swap_count << std::endl;
    }
    file.close();

    return 0;
}

int find_largest_smaller_number(const int n) {
    std::string N = std::to_string(n);
    const int len = N.length();
    int swap1 = -1, swap2 = -1;

    // Tìm vị trí có thể hoán đổi
    for (int i = len - 2; i >= 0; i--) {
        for (int j = len - 1; j > i; j--) {
            if (N[j] < N[i]) {
                // Tìm vị trí hoán đổi
                if (swap1 == -1 || N[j] > N[swap2]) {
                    swap1 = i;
                    swap2 = j;
                }
            }
        }
    }

    if (swap1 == -1) return -1; // Không thể hoán đổi

    // Hoán đổi các chữ số tại swap1 và swap2
    std::swap(N[swap1], N[swap2]);
    return parse_int(N);
}
