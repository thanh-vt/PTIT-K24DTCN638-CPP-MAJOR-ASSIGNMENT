#include <fstream>
#include <iosfwd>
#include <iostream>
#include "b_24.h"

int main() {
    using namespace std;
    cout << "b_23: SAO CHÉP TỆP TIN" << endl;
    ifstream in_file("PTIT.in");      // Mở tệp nguồn để đọc
    ofstream out_file("PTIT.out");    // Mở tệp đích để ghi

    // Kiểm tra tệp có mở thành công không
    if (!in_file) {
        cerr << "Không thê mở file PTIT.in" << endl;
        return 1;
    }

    if (!out_file) {
        cerr << "Không thể tạo file PTIT.out" << endl;
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
