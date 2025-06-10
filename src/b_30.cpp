#include <iostream>
#include "util.h"
#include "b_30.h"

int main() {
    using namespace std;
    // cerr << "b_30: TÁCH CHỮ SỐ" << endl;
    string line;
    cerr << "Nhập số bộ test T:" << endl;
    bool is_valid = false;
    int T = 0;
    do {
        getline(cin, line);
        try {
            T = parse_int(line);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            continue;
        }
        if (T < 1) {
            cerr << "T phải >= 1" << endl;
            continue;
        }
        if (T > 100) {
            cerr << "T phải <= 100" << endl;
            continue;
        }
        is_valid = true;
    } while (!is_valid);
    vector<string> s_inputs(T);
    for (int i = 0; i < T; i++) {
        cerr << "Nhập bộ test " << i + 1 << " - Xâu S:" << endl;
        do {
            is_valid = false;
            getline(cin, line);
            if (line.size() > 100000) {
                cerr << "Length(S) phải <= 100000" << endl;
                continue;
            }
            try {
                const string S = validate_upper_alphanumeric(line);
                s_inputs[i] = S;
            } catch (const exception &e) {
                cerr << e.what() << endl;
                continue;
            }
            is_valid = true;
        } while (!is_valid);
    }
    // cerr << "Kết quả:" << endl;
    for (int i = 0; i < T; i++) {
        const string& S = s_inputs[i];
        cout << separate_alphabet_and_numeric(S) << endl;
    }
    return 0;
}

std::string separate_alphabet_and_numeric(const std::string &S) {
    using namespace std;
    string result;
    // Mảng để đếm số lần xuất hiện của các chữ cái 'A'..'Z'
    vector<int> count(26, 0);
    int sum_digits = 0;

    // Duyệt qua xâu S
    for (const char c : S) {
        if (isalpha(c)) {
            count[c - 'A']++;  // Đếm số lần xuất hiện của chữ cái
        } else if (isdigit(c)) {
            sum_digits += c - '0';  // Tính tổng các chữ số
        }
    }

    // In ra các chữ cái theo thứ tự alphabet
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < count[i]; j++) {
            result += static_cast<char>(i + 'A');
        }
    }
    // Thêm tổng các chữ số vào kết quả
    result += to_string(sum_digits);
    return result;
}
