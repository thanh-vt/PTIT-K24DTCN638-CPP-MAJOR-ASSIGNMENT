#include <cmath>
#include <iostream>
#include <regex>
#include "b_06.h"

class exit_code_exception : public std::exception {
    int code;
    std::string message;
public:
    explicit exit_code_exception(const int c, std::string m) : code(c), message(std::move(m)) {}
    int getCode() const { return code; }
    const char* what() const noexcept override {
        return message.c_str();
    }
};

// Function declarations
int parse_int(const std::string &line);
bool is_prime(const int n);

int main() {
    using namespace std;
    // cerr << "b_06: LIỆT KÊ SỐ NGUYÊN TỐ - 1" << endl;
    string line;
    // cerr << "Nhập 2 số nguyên dương a và b:" << endl;
    getline(cin, line);

    static regex ws_re(" +"); // tách chuỗi bởi khoảng trắng, static để tránh compile lại regex nhiều lần khi chạy chương trình
    const sregex_token_iterator iter(line.begin(), line.end(), ws_re, -1);
    const sregex_token_iterator end;
    vector<string> result(iter, end);
    if (result.size() != 2) {
        cerr << "Chuỗi nhập phải có đúng 2 số a, b" << endl;
        return 2;
    }
    int a, b;
    try {
        a = parse_int(result.at(0));
    } catch (const exception &e) {
        cerr << e.what() << endl;
        return 2;
    }
    try {
        b = parse_int(result.at(1));
    } catch (const exception &e) {
        cerr << e.what() << endl;
        return 2;
    }
    if (a < 1) {
        cerr << "a phải là số nguyên dương" << endl;
        return 2;
    }
    if (a < 1 || b < 1) {
        // cerr << "b  phải là số nguyên dương" << endl;
        return 2;
    }
    if (a > 1000000) {
        cerr << "a phải <= 1000000" << endl;
        return 2;
    }
    if (b > 1000000) {
        // cerr << "b phải <= 1000000" << endl;
        return 2;
    }
    if (a > b) {
        swap(a, b); // nếu a > b thì đảo 2 số
    }
    // cerr << "Kết quả:" << endl;
    for (int i = a; i <= b; ++i) {
        if (is_prime(i)) {
            cout << i << " ";
        }
    }
    cout << endl;
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
