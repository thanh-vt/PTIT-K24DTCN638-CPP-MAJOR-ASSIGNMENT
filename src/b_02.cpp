#include <fstream>
#include <iostream>
#include "util.h"
#include "b_02.h"

int main() {
    using namespace std;
    cerr << "b_02: CHỮ HOA – CHỮ THƯỜNG" << endl;
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
        is_valid = true;
    } while (!is_valid);
    vector<char> inputs(T);
    for (int i = 0; i < T; i++) {
        // Xử lý dòng đọc được
        cerr << "Nhập bộ test " << i + 1 << ":" << endl;
        do {
            is_valid = false;
            getline(cin, line);
            char c;
            try {
                c = parse_char(line);
            } catch (const exception &e) {
                cerr << e.what() << endl;
                continue;
            }
            is_valid = true;
            inputs[i] = c;
        } while (!is_valid);
    }
    cerr << "Kết quả:" << endl;
    for (const char c: inputs) {
        cout << convert_char(c) << endl;
    }
    return 0;
}

char convert_char(const char c) {
    if (islower(c)) {
        return static_cast<char>(toupper(c));
    }
    if (isupper(c)) {
        return static_cast<char>(tolower(c));
    }
    return c;
}
