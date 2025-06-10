#include <iostream>
#include <regex>
#include <string>
#include "util.h"
#include "b_22.h"

int main() {
    using namespace std;
    // cerr << "b_22: KHAI BÁO LỚP PHÂN SỐ" << endl;
    string line;
    bool is_valid = false;
    cerr << "Nhập tử số và mẫu số:" << endl;
    int numerator = 0, denominator = 0;
    do {
        getline(cin, line);
        static regex ws_re(" +");
        // tách chuỗi bởi khoảng trắng, static để tránh compile lại regex nhiều lần khi chạy chương trình
        const sregex_token_iterator iter(line.begin(), line.end(), ws_re, -1);
        const sregex_token_iterator end;
        vector<string> result(iter, end);
        if (result.size() != 2) {
            cerr << "Dòng nhập phải có 2 số" << endl;
            continue;
        }
        try {
            is_valid = false;
            numerator = parse_int(result.at(0));
            if (numerator <= 0) {
                cerr << "Tử số là số nguyên dương" << endl;
                continue;
            }
        } catch (const exception &e) {
            cerr << e.what() << endl;
            continue;
        }
        try {
            is_valid = false;
            denominator = parse_int(result.at(1));
            if (denominator <= 0) {
                cerr << "Mẫu số là số nguyên dương" << endl;
                continue;
            }
        } catch (const exception &e) {
            cerr << e.what() << endl;
            continue;
        }
        is_valid = true;
    } while (!is_valid);
    // cerr << "Kết quả:" << endl;
    const Fraction fraction(numerator, denominator);
    cout << fraction << endl;
    return 0;
}

Fraction::Fraction(const int numerator, const int denominator): numerator(numerator), denominator(denominator) {
    reduce();
}

// Hàm tìm ước chung lớn nhất (GCD) dùng thuật toán Euclid
int Fraction::gcd(int a, int b) {
    while (b != 0) {
        const int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

// Hàm rút gọn phân số
void Fraction::reduce() {
    const int ucln = gcd(numerator, denominator);
    numerator /= ucln;
    denominator /= ucln;
}

std::ostream &operator<<(std::ostream &os, const Fraction &ps) {
    os << ps.numerator << "/" << ps.denominator;
    return os;
}
