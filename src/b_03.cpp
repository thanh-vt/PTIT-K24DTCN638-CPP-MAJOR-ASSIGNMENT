#include <iostream>
#include "b_03.h"

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
int sum_products(const int n);

int main() {
    using namespace std;
    // cerr << "b_03: TÍNH TỔNG GIAI THỪA" << endl;
    // cerr << "Nhập N:" << endl;
    string line;
    getline(cin, line);
    int N;
    try {
        N = parse_int(line);
    } catch (const exception &e) {
        cerr << e.what() << endl;
        return 2;
    }
    if (N <= 0) {
        cerr << "N phải là số nguyên dương" << endl;
        return 2;
    }
    if (N > 20) {
        cerr << "N phải <= 20" << endl;
        return 2;
    }
    // cerr << "Kết quả:" << endl;
    cout << sum_products(N) << endl;
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

int sum_products(const int n) {
    int sum = 0;
    int product = 1;
    for (int i = 1; i <= n; i++) {
        product *= i;
        sum += product;
    }
    return sum;
}
