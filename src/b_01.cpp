#include <iostream>
#include <ostream>
#include <string>
#include "util.h"
#include "b_01.h"

int main() {
    using namespace std;
    cerr << "b_01: TÍNH TỔNG 1 ĐẾN N" << endl;
    string line;
    cerr << "Nhập số bộ test T:" << endl;
    bool is_valid = false;
    int T = 0;
    do {
        getline(cin, line);
        try {
            T = parse_int(line);
        } catch(const exception &e) {
            cerr << e.what() << endl;
            continue;
        }
        if (T < 1) {
            cerr << "T phải >= 1" << endl;
            continue;
        }
        if (T > 10) {
            cerr << "T phải <= 100" << endl;
            continue;
        }
        is_valid = true;
    } while (!is_valid);
    vector<int> inputs(T);
    for (int i = 0; i < T; i++) {

        cerr << "Nhập bộ test " << i + 1 << ":" << endl;
        do {
            is_valid = false;
            getline(cin, line);
            int N;
            try {
                N = parse_int(line);
            } catch(const exception &e) {
                cerr << e.what() << endl;
                continue;
            }
            if (N <= 0) {
                cerr << "N la so nguyen duong" << endl;
                continue;
            }
            if (N > 1000000000) {
                cerr << "N khong qua 1000000000" << endl;
                continue;
            }
            is_valid = true;
            inputs[i] = N;
        } while (!is_valid);
    }
    cerr << "Kết quả:" << endl;
    for (const int n : inputs) {
        cout << sum_1_to_n(n) << endl;
    }
    return 0;
}

int sum_1_to_n(const int n) {
    return (1 + n) * n / 2;
}
