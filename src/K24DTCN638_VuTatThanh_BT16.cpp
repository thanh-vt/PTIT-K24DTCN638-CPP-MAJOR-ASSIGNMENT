#include <fstream>
#include <iostream>
#include <regex>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT16.h"

// NHỎ NHẤT - LỚN NHẤT
int main() {
    std::string filename = "K24DTCN638_VuTatThanh_BT16.txt";
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
    // Xử lý dòng đọc được
    std::regex ws_re(" +");  // ttách chuỗi bởi khoảng trắng
    std::sregex_token_iterator iter(line.begin(), line.end(), ws_re, -1);
    std::sregex_token_iterator end;
    std::vector<std::string> result(iter, end);
    if (result.size() != 2) {
        std::cerr << "Input phai co 2 so a, b" << std::endl;
        return 2;
    }
    int m = parse_int(result.at(0));
    int s = parse_int(result.at(1));
    if (m < 0 || s < 0) {
        return 2;
    }
    if (m > 100) {
        std::cerr << "m khong vuot qua 100\n";
        return 2;
    }
    if (s > 900) {
        std::cerr << "m khong vuot qua 900\n";
        return 2;
    }
    if (s == 0) {
        if (m == 1) std::cout << "0 0\n";
        else std::cout << "-1 -1\n";
        return 0;
    }

    if (s > 9 * m) {
        std::cout << "-1 -1\n";
        return 0;
    }
    std::cout << find_min(m, s) << " " << find_max(m, s) << std::endl;

    file.close();

    return 0;
}

std::string find_min(int m, int s) {
    int sum = s;
    std::string minNum(m, '0');
    for (int i = 0; i < m; i++) {
        for (char d = (i == 0 ? '1' : '0'); d <= '9'; d++) {
            int digit = d - '0';
            int maxPossible = 9 * (m - i - 1);
            if (sum - digit <= maxPossible) {
                minNum[i] = d;
                sum -= digit;
                break;
            }
        }
    }
    return minNum;
}

std::string find_max(int m, int s) {
    int sum = s;
    std::string maxNum(m, '0');
    for (int i = 0; i < m; i++) {
        for (char d = '9'; d >= '0'; d--) {
            int digit = d - '0';
            if (sum - digit >= 0) {
                maxNum[i] = d;
                sum -= digit;
                break;
            }
        }
    }
    return maxNum;
}