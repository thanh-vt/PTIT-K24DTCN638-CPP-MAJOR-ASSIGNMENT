#include <fstream>
#include <iostream>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT05.h"

// SỐ MAY MẮN
int main() {
    using namespace std;
    const string filename = "K24DTCN638_VuTatThanh_BT05.txt";
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
    if (total_tests < 1 || total_tests > 20) {
        cerr << "T phai lon hon hoac bang 1 va nho hon hoac bang 20" << endl;
        return 2;
    }
    for (int i = 0; i < total_tests; i++) {
        // Xử lý dòng đọc được
        if (!getline(file, line)) {
            cerr << "Khong co dong tiep theo" << endl;
            return 2;
        }
        const int X = parse_int(line);
        if (X >= 1000000000) {
            cerr << "X khong vuot qua 9 chu so" << endl;
            return 2;
        }
        cout << (X % 100 == 86) << endl;
    }

    file.close();

    return 0;
}
