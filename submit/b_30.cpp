#include <iostream>
#include <string>
#include <sstream>
#include <functional>
#include <vector>
#include "b_30.h"

int main() {
    using namespace std;
    // cerr << "b_30: TÁCH CHỮ SỐ" << endl;
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
            const string S = validate_upper_alphanumeric(line);
            s_inputs[i] = S;
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
    }
    // cerr << "Kết quả:" << endl;
    for (int i = 0; i < T; i++) {
        const string& S = s_inputs[i];
        cout << separate_alphabet_and_numeric(S) << endl;
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

std::string validate_upper_alphanumeric(const std::string &line) {
    for (char c : line) {
        if (!std::isupper(c) && !std::isdigit(c)) {
            throw exit_code_exception(2, "Xâu chỉ được chứa chữ hoa và số");
        }
    }
    return line;
}

std::string separate_alphabet_and_numeric(const std::string &S) {
    using namespace std;
    string result;
    vector<int> count(26, 0);
    int sum_digits = 0;
    for (const char c : S) {
        if (isalpha(c)) {
            count[c - 'A']++;
        } else if (isdigit(c)) {
            sum_digits += c - '0';
        }
    }
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < count[i]; j++) {
            result += static_cast<char>(i + 'A');
        }
    }
    result += to_string(sum_digits);
    return result;
}
