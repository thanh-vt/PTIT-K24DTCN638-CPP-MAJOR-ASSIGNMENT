#include <iostream>
#include "util.h"
#include "b_05.h"

int main() {
    using namespace std;
    cerr << "b_05: SỐ MAY MẮN" << endl;
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
        if (T > 100) {
            cerr << "T phải <= 100" << endl;
            continue;
        }
        is_valid = true;
    } while (!is_valid);
    vector<int> inputs(T);
    for (int i = 0; i < T; i++) {
        // Xử lý dòng đọc được
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
            if (N >= 1000000000) {
                cerr << "N không vượt quá 9 chữ số" << endl;
                continue;
            }
            is_valid = true;
            inputs[i] = N;
        } while (!is_valid);
    }
    cerr << "Kết quả:" << endl;
    for (const int N: inputs) {
        cout << ends_with(N, 86) << endl;
    }
    return 0;
}

bool ends_with(const int value, const int suffix) {
    return abs(value % 100) == suffix;
}
