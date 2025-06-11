#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include "b_01.h"

int main() {
    using namespace std;
    // cerr << "b_01: TÍNH TỔNG 1 ĐẾN N" << endl;
    string line;
    // cerr << "Nhập số bộ test T:" << endl;
    getline(cin, line);
    int T;
    try {
        T = parse_int(line);
    } catch(const exception &e) {
        cerr << e.what() << endl;
        return 2;
    }
    if (T < 1) {
        cerr << "T phải >= 1" << endl;
        return 2;
    }
    if (T > 10) {
        cerr << "T phải <= 100" << endl;
        return 2;
    }
    vector<int> inputs(T);
    for (int i = 0; i < T; i++) {
        // cerr << "Nhập bộ test " << i + 1 << ":" << endl;
        getline(cin, line);
        int N;
        try {
            N = parse_int(line);
        } catch(const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
        if (N <= 0) {
            cerr << "N la so nguyen duong" << endl;
            return 2;
        }
        if (N > 1000000000) {
            cerr << "N khong qua 1000000000" << endl;
            return 2;
        }
        inputs[i] = N;
    }
    // cerr << "Kết quả:" << endl;
    for (const int n : inputs) {
        cout << sum_1_to_n(n) << endl;
    }
    return 0;
}

// Function definitions
int parse_int(const std::string &line) {
    using namespace std;
    try {
        size_t pos;
        const int x = stoi(line, &pos);
        if (pos != line.size()) {
            throw exit_code_exception(2, "Chuỗi nhập có chứa các ký tự không hợp lệ");
        }
        return x;
    } catch (const invalid_argument &e) {
        throw exit_code_exception(2, "Chuỗi nhập không phải số kiểu integer hợp lệ");
    } catch (const out_of_range &e) {
        throw exit_code_exception(2, "Số vượt quá phạm vi kiểu integer");
    }
}

int sum_1_to_n(const int n) {
    return (1 + n) * n / 2;
}
