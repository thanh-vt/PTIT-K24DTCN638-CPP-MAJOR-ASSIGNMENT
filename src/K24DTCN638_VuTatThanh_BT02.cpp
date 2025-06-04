#include <fstream>
#include <iostream>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT02.h"

// CHỮ HOA – CHỮ THƯỜNG
int main() {
    using namespace std;
    const string filename = "K24DTCN638_VuTatThanh_BT02.txt";
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
        const char c = parse_char(line);
        cout << convert_char(c) << endl;
    }

    file.close();

    return 0;
}

char convert_char(const char c) {
    if (islower(c)) {
        return static_cast<char>(toupper(c));
    }
    if (isupper(c)) {
        return static_cast<char>(tolower(c));
    }
    return c;
}
