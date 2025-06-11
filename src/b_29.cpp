#include <cctype>
#include <iostream>
#include <string>
#include <sstream>
#include <functional>
#include <vector>
#include "b_29.h"

int main() {
    using namespace std;
    // cerr << "b_29: TÍNH TỔNG CÁC SỐ TRONG XÂU" << endl;
    string line;
    // cerr << "Nhập số bộ test T:" << endl;
    getline(cin, line);
    int T;
    try {
        T = parse_int(line);
        if (T < 1) {
            cerr << "T phải >= 1" << endl;
            return 2;
        }
        if (T > 100) {
            cerr << "T phải <= 100" << endl;
            return 2;
        }
    } catch (const exception &e) {
        cerr << e.what() << endl;
        return 2;
    }
    vector<string> s_inputs(T);
    for (int i = 0; i < T; i++) {
        // cerr << "Nhập bộ test " << i + 1 << " - Xâu S:" << endl;
        getline(cin, line);
        if (line.size() > 100000) {
            cerr << "Length(S) phải <= 100000" << endl;
            return 2;
        }
        try {
            const string S = validate_lower_alphanumeric(line);
            s_inputs[i] = S;
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
    }
    // cerr << "Kết quả:" << endl;
    for (int i = 0; i < T; i++) {
        const string& S = s_inputs[i];
        cout << sum_of_numbers(S) << endl;
    }
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

std::string validate_lower_alphanumeric(const std::string &line) {
    for (char c : line) {
        if (!std::islower(c) && !std::isdigit(c)) {
            throw exit_code_exception(2, "Xâu chỉ được chứa chữ thường và số");
        }
    }
    return line;
}

int sum_of_numbers(const std::string& S) {
    int totalSum = 0;
    int currentNumber = 0;
    for (const char c : S) {
        if (isdigit(c)) {
            currentNumber = currentNumber * 10 + (c - '0');
        } else {
            totalSum += currentNumber;
            currentNumber = 0;
        }
    }
    totalSum += currentNumber;
    return totalSum;
}
