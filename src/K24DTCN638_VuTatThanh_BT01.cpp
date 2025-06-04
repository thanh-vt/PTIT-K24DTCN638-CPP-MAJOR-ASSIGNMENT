#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT01.h"

// TÍNH TỔNG 1 ĐẾN N
int main() {
    using namespace std;
    const string filename = "K24DTCN638_VuTatThanh_BT01.txt";
    ifstream file(filename); // Mở file để đọc
    if (!file) {
        cerr << "Khong the mo file input " << filename << endl;
        return 1;
    }

    string line;
    if (!getline(file, line)) {
        cerr << "Khong co dong tiep theo" << endl;
        return 2;
    }
    const int total_tests = parse_int(line);
    if (total_tests < 1 || total_tests > 100) {
        cerr << "T phai lon hon hoac bang 1 va nho hon hoac bang 100" << endl;
        return 2;
    }
    for (int i = 0; i < total_tests; i++) {
        // Xử lý dòng đọc được
        if (!getline(file, line)) {
            cerr << "Khong co dong tiep theo" << endl;
            return 2;
        }
        const int n = parse_int(line);
        if (n <= 0) {
            cerr << "N la so nguyen duong" << endl;
            return 2;
        }
        if (n > 1000000000) {
            cerr << "N khong qua 1000000000" << endl;
            return 2;
        }
        cout << sum_1_to_n(n) << endl;
    }

    file.close();

    return 0;
}

int sum_1_to_n(const int n) {
    return (1 + n) * n / 2;
}
