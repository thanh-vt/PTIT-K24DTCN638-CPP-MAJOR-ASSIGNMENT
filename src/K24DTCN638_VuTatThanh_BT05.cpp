#include <fstream>
#include <iostream>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT05.h"

int main() {
    std::string filename = "K24DTCN638_VuTatThanh_BT05.txt";
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
        // Xử lý dòng đọc được
        if (!std::getline(file, line)) {
            std::cerr << "Khong co dong tiep theo" << std::endl;
            return 2;
        }
        const int x = parse_int(line);
        if (x < 0) {
            return 2;
        }
        if (x > 999999999) {
            std::cerr << "x khong vuot qua 9 chu so" << std::endl;
            return 2;
        }
        std::cout << (x % 100 == 86) << std::endl;
    }

    file.close();

    return 0;
}
