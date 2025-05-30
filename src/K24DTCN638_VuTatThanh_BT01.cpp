#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT01.h"

int main() {
    std::string filename = "K24DTCN638_VuTatThanh_BT01.txt";
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
        // Xử lý dòng đọc được
        if (!std::getline(file, line)) {
            std::cerr << "Khong co dong tiep theo" << std::endl;
            return 2;
        }
        const int n = parse_int(line);
        if (n < 0) {
            return 2;
        }
        if (n > 1000000000) {
            std::cerr << "N khong qua 1000000000" << std::endl;
            return 2;
        }
        std::cout << sum_1_to_n(n) << std::endl;
    }

    file.close();

    return 0;
}

int sum_1_to_n(const int n) {
    return (1 + n) * n / 2;
}
