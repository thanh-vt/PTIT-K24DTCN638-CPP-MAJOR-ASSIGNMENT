#include <string>
#include <iostream>
#include <unordered_map>
#include "util.h"
#include "b_15.h"

int main() {
    using namespace std;
    // cerr << "b_15: ĐẾM SỐ PHẦN TỬ LẶP LẠI" << endl;
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
                cerr << "n phải >= 1" << endl;
                continue;
            }
            if (N > 1000000) {
                cerr << "n phải <= 1000000" << endl;
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
                static const function<string(int, int)> validate_func = [](const int pos, const int value) {
                    if (value < 0) {
                        return "A[" + to_string(pos) + "] phải >= 0";
                    }
                    if (value > 1000000) {
                        return "A[" + to_string(pos) + "] phải <= 1000000";
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
    for (int i = 0; i < T; i++) {
        const vector<int>& A = v_inputs[i];
        const int count = count_array_duplicated_elements(A);
        cout << count << endl;
    }
    return 0;
}

int count_array_duplicated_elements(const std::vector<int> &A) {
    using namespace std;
    const size_t n = A.size();
    unordered_map<int, int> freq;

    for (size_t i = 0; i < n; i++) {
        freq[A[i]]++;
    }

    int count = 0;
    for (const pair<const int, int>& p : freq) {
        if (p.second >= 2) count += p.second;
    }
    return count;
}
