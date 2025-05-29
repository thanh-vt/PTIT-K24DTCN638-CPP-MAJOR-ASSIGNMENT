#include <cmath>
#include <fstream>
#include <iostream>
#include <regex>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT06.h"

int main() {
    std::string filename = "K24DTCN638_VuTatThanh_BT06.txt";
    std::ifstream file(filename); // Mở file để đọc
    if (!file) {
        std::cerr << "Khong the mo file input " << filename << std::endl;
        return 1;
    }

    std::string line;
    if (std::getline(file, line)) {
        // Xử lý dòng đọc được
        std::regex ws_re(" +");  // ttách chuỗi bởi khoảng trắng
        std::sregex_token_iterator iter(line.begin(), line.end(), ws_re, -1);
        std::sregex_token_iterator end;
        std::vector<std::string> result(iter, end);
        if (result.size() != 2) {
            std::cerr << "Input phai co 2 so a, b" << std::endl;
            return 2;
        }
        int a = parse_int(result.at(0));
        int b = parse_int(result.at(1));
        if (a < 0 || b < 0) {
            return 2;
        }
        if (a > 1000000 || b > 1000000) {
            std::cerr << "a, b khong vuot qua 1000000.\n";
            return 2;
        }
        if (a > b) {
            std::swap(a, b); // Ensure a <= b
        }
        for (int i = a; i <= b; ++i) {
            if (is_prime(i)) {
                std::cout << i << " ";
            }
        }
        std::cout << std::endl;
    }

    file.close();

    return 0;
}

bool is_prime(const int n) {
    if (n < 2)
        return false;
    if (n == 2)
        return true;
    if (n % 2 == 0)
        return false;
    const int limit = static_cast<int>(std::sqrt(n));
    for (int i = 3; i <= limit; i += 2) {
        if (n % i == 0)
            return false;
    }
    return true;
}
