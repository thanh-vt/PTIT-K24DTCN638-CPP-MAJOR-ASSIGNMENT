#include <iostream>
#include <string>
#include "util.h"
#include "b_19.h"

int main() {
    using namespace std;
    cout << "b_19: SẮP XẾP CHỮ SỐ" << endl;
    string line;
    cout << "Nhập số bộ test T:" << endl;
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
    vector<vector<long>> v_inputs(T);
    for (int i = 0; i < T; i++) {
        cout << "Nhập bộ test " << i + 1 << " - Số N:" << endl;
        int N = 0;
        do {
            is_valid = false;
            getline(cin, line);
            try {
                N = parse_int(line);
            } catch (const exception &e) {
                cerr << e.what() << endl;
                continue;
            }
            if (N < 1) {
                cerr << "N phải >= 1" << endl;
                continue;
            }
            if (N > 10000000) {
                cerr << "N phải <= 10000000" << endl;
                return 2;
            }
            is_valid = true;
        } while (!is_valid);
        cout << "Nhập bộ test " << i + 1 << " - Dãy số A[] gồm " << N << " phần tử:" << endl;
        vector<long> A;
        do {
            is_valid = false;
            getline(cin, line);
            try {
                // hàm lambda validate từng phần tử đọc được
                static const function<string(int, long)> validate_func = [](const int pos, const long value) {
                    if (value < 0) {
                        return "A[" + to_string(pos) + "] phải >= 0";
                    }
                    if (value > 10000000000000000) {
                        return "A[" + to_string(pos) + "] phải <= 10000000000000000";
                    }
                    static string oke_msg;
                    return oke_msg;
                };
                A = string_to_long_vector(line, N, validate_func);
            } catch (const exception &e) {
                cerr << e.what() << endl;
                continue;
            }
            is_valid = true;
            v_inputs[i] = A;
        } while (!is_valid);
    }
    cout << "Kết quả:" << endl;
    for (int i = 0; i < T; i++) {
        const vector<long>& A = v_inputs[i];
        set<int> digit_set = sort_digits_array(A);
        for (const int d: digit_set) {
            cout << d << " ";
        }
        cout << endl;
    }
    return 0;
}

std::set<int> sort_digits_array(const std::vector<long> &A) {
    using namespace std;
    const size_t n = A.size();
    set<int> digits_set;
    for (size_t i = 0; i < n; ++i) {
        string s = to_string(A[i]);
        for (const char c: s) {
            if (isdigit(c)) {
                digits_set.insert(c - '0');
            }
        }
    }
    // set tự động sắp xếp
    return digits_set;
}
