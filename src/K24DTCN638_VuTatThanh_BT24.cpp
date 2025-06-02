#include <fstream>
#include <iosfwd>
#include <iostream>
#include "K24DTCN638_VuTatThanh_BT24.h"

// SAO CHÉP TỆP TIN
int main() {
    using namespace std;
    ifstream in_file("PTIT.in");      // Mở tệp nguồn để đọc
    ofstream out_file("PTIT.out");    // Mở tệp đích để ghi

    // Kiểm tra tệp có mở thành công không
    if (!in_file) {
        cerr << "Khong the mo file PTIT.in" << endl;
        return 1;
    }

    if (!out_file) {
        cerr << "Khong the tao file PTIT.out" << endl;
        return 1;
    }

    string line;
    while (getline(in_file, line)) {
        out_file << line << endl;
    }

    in_file.close();
    out_file.close();

    return 0;
}
