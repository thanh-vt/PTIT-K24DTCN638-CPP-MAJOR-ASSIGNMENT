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
    int total_tests = 0;
    while (std::getline(file, line)) {
        // Xử lý dòng đọc được
        if (total_tests == 0) {
            total_tests = parse_int(line);
            if (total_tests <= 1) {
                return 2;
            }
            if (total_tests > 20) {
                std::cerr << "So luong test khong vuot qua 20" << std::endl;
                return 2;
            }
        } else {
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
    }

    file.close();

    return 0;
}
