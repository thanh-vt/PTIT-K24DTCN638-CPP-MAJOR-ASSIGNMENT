#include <cmath>
#include <iostream>
#include <regex>
#include "util.h"
#include "b_06.h"

int main() {
    using namespace std;
    // cerr << "b_06: LIỆT KÊ SỐ NGUYÊN TỐ - 1" << endl;
    string line;
    cerr << "Nhập 2 số nguyên dương a và b:" << endl;
    bool is_valid = false;
    int a, b;
    do {
        getline(cin, line);

        static regex ws_re(" +"); // tách chuỗi bởi khoảng trắng, static để tránh compile lại regex nhiều lần khi chạy chương trình
        const sregex_token_iterator iter(line.begin(), line.end(), ws_re, -1);
        const sregex_token_iterator end;
        vector<string> result(iter, end);
        if (result.size() != 2) {
            cerr << "Chuỗi nhập phải có đúng 2 số a, b" << endl;
            continue;
        }
        try {
            a = parse_int(result.at(0));
        } catch (const exception &e) {
            cerr << e.what() << endl;
            continue;
        }
        try {
            b = parse_int(result.at(1));
        } catch (const exception &e) {
            cerr << e.what() << endl;
            continue;
        }
        if (a < 1) {
            cerr << "a phải là số nguyên dương" << endl;
            continue;
        }
        if (a < 1 || b < 1) {
            // cerr << "b  phải là số nguyên dương" << endl;
            continue;
        }
        if (a > 1000000) {
            cerr << "a phải <= 1000000" << endl;
            continue;
        }
        if (b > 1000000) {
            // cerr << "b phải <= 1000000" << endl;
            continue;
        }
        if (a > b) {
            swap(a, b); // nếu a > b thì đảo 2 số
        }
        is_valid = true;
    } while (!is_valid);
    // cerr << "Kết quả:" << endl;
    for (int i = a; i <= b; ++i) {
        if (is_prime(i)) {
            cout << i << " ";
        }
    }
    cout << endl;
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
