#include <cmath>
#include <fstream>
#include <iostream>
#include <regex>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT06.h"

// LIỆT KÊ SỐ NGUYÊN TỐ - 1
int main() {
    using namespace std;
    const string filename = "K24DTCN638_VuTatThanh_BT06.txt";
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
    // Xử lý dòng đọc được
    regex ws_re(" +");  // ttách chuỗi bởi khoảng trắng
    sregex_token_iterator iter(line.begin(), line.end(), ws_re, -1);
    sregex_token_iterator end;
    vector<string> result(iter, end);
    if (result.size() != 2) {
        cerr << "Input phai co 2 so a, b" << endl;
        return 2;
    }
    int a = parse_int(result.at(0));
    int b = parse_int(result.at(1));
    if (a < 1 || b < 1) {
        cerr << "a, b la so nguyen duong" << endl;
        return 2;
    }
    if (a > 1000000 || b > 1000000) {
        cerr << "a, b khong vuot qua 1000000" << endl;
        return 2;
    }
    if (a > b) {
        swap(a, b); // Ensure a <= b
    }
    for (int i = a; i <= b; ++i) {
        if (is_prime(i)) {
            cout << i << " ";
        }
    }
    cout << endl;

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
    const int limit = static_cast<int>(sqrt(n));
    for (int i = 3; i <= limit; i += 2) {
        if (n % i == 0)
            return false;
    }
    return true;
}
