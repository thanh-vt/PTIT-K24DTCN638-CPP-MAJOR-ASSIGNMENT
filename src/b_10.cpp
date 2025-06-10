#include <iostream>
#include <string>
#include "util.h"
#include "b_10.h"

int main() {
    using namespace std;
    // cerr << "b_10: SỐ NHỎ NHẤT CHƯA XUẤT HIỆN" << endl;
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
    vector<vector<int> > v_inputs(T);
    for (int i = 0; i < T; i++) {
        cerr << "Nhập bộ test " << i + 1 << " - Số N:" << endl;
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
                cerr << "N phải >= bang 1" << endl;
                continue;
            }
            if (N > 1000000) {
                cerr << "N phải <= 1000000" << endl;
                continue;
            }
            is_valid = true;
        } while (!is_valid);
        cerr << "Nhập bộ test " << i + 1 << " - Dãy số A[] gồm " << N << " phần tử:" << endl;

        do {
            is_valid = false;
            getline(cin, line);
            vector<int> A;
            try {
                // hàm lambda validate từng phần tử đọc được
                static const function<string(int, int)> validate_func = [](const int pos, const long value) {
                    if (value < -1000000000) {
                        return "A[" + to_string(pos) + "] phải >= -1000000000";
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
    // cerr << "Kết quả:" << endl;
    for (const vector<int> &A: v_inputs) {
        cout << find_smallest_missing_positive(A) << endl;
    }
    return 0;
}

size_t find_smallest_missing_positive(const std::vector<int>& arr) {
    using namespace std;
    const size_t n = arr.size();
    vector<bool> present(n + 2, false); // đánh dấu số từ 1 đến n+1

    for (const int x : arr) {
        if (x >= 1 && x <= n + 1) {
            present[x] = true;
        }
    }

    for (int i = 1; i <= n + 1; i++) {
        if (!present[i]) return i;
    }
    return n + 1; // trường hợp này ít xảy ra vì đã kiểm tra hết
}
