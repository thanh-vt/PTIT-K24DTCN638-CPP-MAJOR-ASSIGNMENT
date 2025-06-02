#include <fstream>
#include <iostream>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT05.h"

// SỐ MAY MẮN
int main() {
    using namespace std;
    string filename = "K24DTCN638_VuTatThanh_BT05.txt";
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
        const int x = parse_int(line);
        if (x < 0) {
            return 2;
        }
        if (x > 999999999) {
            cerr << "x khong vuot qua 9 chu so" << endl;
            return 2;
        }
        cout << (x % 100 == 86) << endl;
    }

    file.close();

    return 0;
}
