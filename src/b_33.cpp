#include <iostream>
#include <string>
#include <algorithm>
#include "util.h"
#include "b_33.h"

// SẮP XẾP XEN KẼ - 2
int main() {
    using namespace std;
    cerr << "b_32: HỢP VÀ GIAO CỦA HAI DÃY SỐ -2" << endl;
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
    vector<vector<int> > A_inputs(T);
    for (int i = 0; i < T; i++) {
        cerr << "Nhập bộ test " << i + 1 << " - Số n:" << endl;
        int n = 0, m = 0;
        do {
            is_valid = false;
            getline(cin, line);
            try {
                n = parse_int(line);
                if (n < 1) {
                    cerr << "n phải >= 1" << endl;
                    continue;
                }
                if (n > 1000) {
                    cerr << "n phải <= 1000" << endl;
                    continue;
                }
            } catch (const exception &e) {
                cerr << e.what() << endl;
                continue;
            }
            is_valid = true;
        } while (!is_valid);
        cerr << "Nhập bộ test " << i + 1 << " - Dãy A[] gồm " << n << " phần tử:" << endl;
        do {
            is_valid = false;
            getline(cin, line);
            try {
                // hàm lambda validate từng phần tử đọc được
                static const function<string(int, int)> validate_func = [](const int pos, const long value) {
                    if (value < 1) {
                        return "A[" + to_string(pos) + "] phải >= 0";
                    }
                    if (value > 1000) {
                        return "A[" + to_string(pos) + "] phải <= 1000";
                    }
                    static string oke_msg;
                    return oke_msg;
                };
                const vector<int> A = string_to_int_vector(line, n, validate_func);
                A_inputs[i] = A;
            } catch (const exception &e) {
                cerr << e.what() << endl;
                continue;
            }
            is_valid = true;
        } while (!is_valid);

    }
    cerr << "Kết quả:" << endl;
    for (int i = 0; i < T; i++) {
        vector<int> &A = A_inputs[i];
        vector<int> result = sort_alternating(A);
        for (const int x : result) cout << x << " ";
        cout << endl;
    }
    return 0;
}

std::vector<int> sort_alternating(std::vector<int>& a) {
    using namespace std;
    sort(a.begin(), a.end()); // Sắp xếp tăng dần
    size_t i = a.size() - 1;     // chỉ số lớn nhất
    int j = 0;                // chỉ số nhỏ nhất
    vector<int> result;

    while (j <= i) {
        result.push_back(a[i--]); // chèn số lớn nhất còn lại
        if (j <= i) {
            result.push_back(a[j++]); // chèn số nhỏ nhất còn lại
        }
    }
    return result;
}