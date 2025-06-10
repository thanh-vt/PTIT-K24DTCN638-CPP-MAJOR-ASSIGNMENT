#include <cctype>
#include <iostream>
#include "util.h"
#include "b_29.h"

int main() {
    using namespace std;
    cerr << "b_29: TÍNH TỔNG CÁC SỐ TRONG XÂU" << endl;
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
                string S = validate_lower_alphanumeric(line);
                s_inputs.push_back(S);
            } catch (const exception &e) {
                cerr << e.what() << endl;
                continue;
            }
            is_valid = true;
        } while (!is_valid);
    }
    cerr << "Kết quả:" << endl;
    for (int i = 0; i < T; i++) {
        const string& S = s_inputs[i];
        cout << sum_of_numbers(S) << endl;
    }
    return 0;
}

int sum_of_numbers(const std::string& S) {
    int totalSum = 0;
    int currentNumber = 0;
    
    for (const char c : S) {
        if (isdigit(c)) {
            // Nếu là chữ số, tích lũy vào số hiện tại
            currentNumber = currentNumber * 10 + (c - '0');
        } else {
            // Nếu gặp ký tự khác, cộng số hiện tại vào tổng (nếu có)
            totalSum += currentNumber;
            currentNumber = 0; // Reset số tạm thời
        }
    }

    // Cộng số còn lại nếu xâu kết thúc và có số chưa được cộng
    totalSum += currentNumber;
    
    return totalSum;
}
