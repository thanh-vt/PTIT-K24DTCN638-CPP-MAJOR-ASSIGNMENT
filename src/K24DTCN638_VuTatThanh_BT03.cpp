#include <fstream>
#include <iostream>

#include "util.h"
#include "K24DTCN638_VuTatThanh_BT03.h"

int main() {
    std::string filename = "K24DTCN638_VuTatThanh_BT03.txt";
    std::ifstream file(filename); // Mở file để đọc
    if (!file) {
        std::cerr << "Khong the mo file input " << filename << std::endl;
        return 1;
    }

    std::string line;
    if (std::getline(file, line)) {
        // Xử lý dòng đọc được
        const int n = parse_int(line);
        if (n < 0) return 2;
        if (n > 20) {
            std::cerr << "n phai nho hon 20" << std::endl;
            return 2;
        }
        std::cout << sum_products(n) << std::endl;
    }

    file.close();

    return 0;
}

int sum_products(const int n) {
    int sum = 0;
    int product = 1;
    for (int i = 1; i <= n; i++) {
        product *= i;
        sum += product;
    }
    return sum;
}
