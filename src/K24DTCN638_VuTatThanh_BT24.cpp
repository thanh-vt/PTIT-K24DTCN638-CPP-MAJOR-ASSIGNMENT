#include <fstream>
#include <iosfwd>
#include <iostream>
#include "K24DTCN638_VuTatThanh_BT24.h"


int main() {
    std::ifstream in_file("PTIT.in");      // Mở tệp nguồn để đọc
    std::ofstream out_file("PTIT.out");    // Mở tệp đích để ghi

    // Kiểm tra tệp có mở thành công không
    if (!in_file) {
        std::cerr << "Khong the mo file PTIT.in" << std::endl;
        return 1;
    }

    if (!out_file) {
        std::cerr << "Khong the tao file PTIT.out" << std::endl;
        return 1;
    }

    std::string line;
    while (getline(in_file, line)) {
        out_file << line << std::endl;
    }

    in_file.close();
    out_file.close();

    return 0;
}
