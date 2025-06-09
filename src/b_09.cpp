#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include "util.h"
#include "b_09.h"

int main() {
    using namespace std;
    cout << "b_09: CHÊNH LỆCH NHỎ NHẤT" << endl;
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
        if (T > 10) {
            cerr << "T phải <= 10" << endl;
            continue;
        }
        is_valid = true;
    } while (!is_valid);
    vector<vector<int> > v_inputs(T);
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
                cout << "N phải >= 1" << endl;
                continue;
            }
            if (N > 1000000) {
                cout << "N phải <= 1000000" << endl;
                continue;
            }
            is_valid = true;
        } while (!is_valid);
        cout << "Nhập bộ test " << i + 1 << " - Dãy số A[] gồm " << N << " phần tử:" << endl;
        do {
            is_valid = false;
            getline(cin, line);
            vector<int> A;
            try {
                // hàm lambda validate từng phần tử đọc được
                static const function<string(int, int)> validate_func = [](const int pos, const long value) {
                    if (value < 0) {
                        return "A[" + to_string(pos) + "] phải >= 0";
                    }
                    if (value > 1000000000) {
                        return "A[" + to_string(pos) + "] phải <= 1000000000";
                    }
                    static string oke_msg;
                    return oke_msg;
                };
                A = string_to_int_vector(line, N, validate_func);
            } catch (const exception &e) {
                cerr << e.what() << endl;
                continue;
            }
            is_valid = true;
            v_inputs[i] = A;
        } while (!is_valid);
    }
    cout << "Kết quả:" << endl;
    for (const vector<int> &A: v_inputs) {
        cout << find_min_diff(A) << endl;
    }
    return 0;
}

int find_min_diff(std::vector<int> A) {
    sort(A.begin(), A.end());
    int min_diff = INT_MAX;
    for (int i = 0; i < A.size() - 1; i++) {
        const int diff = A[i + 1] - A[i];
        if (diff < min_diff) {
            min_diff = diff;
        }
    }
    return min_diff;
}
