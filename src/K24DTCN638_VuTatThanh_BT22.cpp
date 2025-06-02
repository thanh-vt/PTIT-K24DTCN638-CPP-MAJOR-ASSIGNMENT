#include "K24DTCN638_VuTatThanh_BT22.h"

#include <fstream>
#include <iostream>
#include <regex>
#include <string>

#include "util.h"

// KHAI BÁO LỚP PHÂN SỐ
int main() {
    using namespace std;
    const string filename = "K24DTCN638_VuTatThanh_BT22.txt";
    ifstream file(filename); // Mở file để đọc
    if (!file) {
        cerr << "Khong the mo file input " << filename << endl;
        return 1;
    }
    string line;
    string numeratorStr, denominatorStr;
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
        cerr << "Input phai co 2 so nguyen duong" << endl;
        return 2;
    }
    numeratorStr = result.at(0);
    denominatorStr = result.at(1);
    file.close();
    try {
        Fraction fraction(numeratorStr, denominatorStr);
        cout << fraction << endl;
    } catch (const exception &ex) {
        cerr << ex.what() << endl;
        return 2;
    }

    return 0;
}

Fraction::Fraction(const std::string &numeratorStr, const std::string &denominatorStr): Fraction(parse_int(numeratorStr), parse_int(denominatorStr)) {
}

Fraction::Fraction(const int numerator, const int denominator): numerator(numerator), denominator(denominator) {
    using namespace std;
    if (numerator < 0) {
        throw invalid_argument("Tu so phai la so nguyen duong");
    }
    if (denominator < 0) {
        throw invalid_argument("Mau so phai la so nguyen duong");
    }
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

std::ostream & operator<<(std::ostream &os, const Fraction &ps) {
    os << ps.numerator << "/" << ps.denominator;
    return os;
}
