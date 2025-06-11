#include <iostream>
#include <regex>
#include <string>
#include <sstream>
#include <functional>
#include "b_23.h"

int main() {
    using namespace std;
    // cerr << "b_23: TÍNH TỔNG HAI ĐỐI TƯỢNG PHÂN SỐ" << endl;
    string line;
    // cerr << "Nhập 2 cặp tử số và mẫu số:" << endl;
    getline(cin, line);
    static regex ws_re(" +");
    // tách chuỗi bởi khoảng trắng, static để tránh compile lại regex nhiều lần khi chạy chương trình
    const sregex_token_iterator iter(line.begin(), line.end(), ws_re, -1);
    const sregex_token_iterator end;
    vector<string> result(iter, end);
    if (result.size() != 4) {
        cerr << "Dòng nhập phải có 4 số" << endl;
        return 2;
    }
    int numerator1;
    try {
        numerator1 = parse_int(result.at(0));
        if (numerator1 <= 0) {
            cerr << "Tử số 1 là số nguyên dương" << endl;
            return 2;
        }
    } catch (const exception &e) {
        cerr << e.what() << endl;
        return 2;
    }
    int denominator1;
    try {
        denominator1 = parse_int(result.at(1));
        if (denominator1 <= 0) {
            cerr << "Mẫu số 1 là số nguyên dương" << endl;
            return 2;
        }
    } catch (const exception &e) {
        cerr << e.what() << endl;
        return 2;
    }
    int numerator2;
    try {
        numerator2 = parse_int(result.at(2));
        if (numerator2 <= 0) {
            cerr << "Tử số 2 là số nguyên dương" << endl;
            return 2;
        }
    } catch (const exception &e) {
        cerr << e.what() << endl;
        return 2;
    }
    int denominator2;
    try {
        denominator2 = parse_int(result.at(3));
        if (denominator2 <= 0) {
            cerr << "Mẫu số 2 là số nguyên dương" << endl;
            return 2;
        }
    } catch (const exception &e) {
        cerr << e.what() << endl;
        return 2;
    }
    // cerr << "Kết quả:" << endl;

    const Fraction fraction1(numerator1, denominator1);
    const Fraction fraction2(numerator2, denominator2);
    const Fraction fraction = fraction1 + fraction2;
    cout << fraction << endl;
    return 0;
}

// Function definitions
int parse_int(const std::string &line) {
    using namespace std;
    try {
        size_t pos;
        const int x = stoi(line, &pos);
        if (pos != line.size()) {
            throw exit_code_exception(2, "Chuỗi nhập có chứa các ký tự không hợp lệ");
        }
        return x;
    } catch (const invalid_argument &e) {
        throw exit_code_exception(2, "Chuỗi nhập không phải số kiểu integer hợp lệ");
    } catch (const out_of_range &e) {
        throw exit_code_exception(2, "Số vượt quá phạm vi kiểu integer");
    }
}

Fraction::Fraction(const std::string &numeratorStr, const std::string &denominatorStr): Fraction(parse_int(numeratorStr), parse_int(denominatorStr)) {
}

Fraction::Fraction(const int numerator, const int denominator): numerator(numerator), denominator(denominator) {
    using namespace std;
    reduce();
}

Fraction Fraction::operator+(const Fraction &other) const {
    const int newNumerator = numerator * other.denominator + other.numerator * denominator;
    const int newDenominator = denominator * other.denominator;
    return Fraction {newNumerator, newDenominator};
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

std::ostream & operator<<(std::ostream &os, const Fraction &ps) {
    os << ps.numerator << "/" << ps.denominator;
    return os;
}