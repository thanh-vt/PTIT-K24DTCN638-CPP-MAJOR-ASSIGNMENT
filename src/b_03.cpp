#include <iostream>
#include "util.h"
#include "b_03.h"

int main() {
    using namespace std;
    // cerr << "b_03: TÍNH TỔNG GIAI THỪA" << endl;
    cerr << "Nhập N:" << endl;
    string line;
    bool is_valid = false;
    int N = 0;
    do {
        getline(cin, line);
        try {
            N = parse_int(line);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            continue;
        }
        if (N <= 0) {
            cerr << "N phải là số nguyên dương" << endl;
            continue;
        }
        if (N > 20) {
            cerr << "N phải <= 20" << endl;
            continue;
        }
        is_valid = true;
    } while (!is_valid);
    // cerr << "Kết quả:" << endl;
    cout << sum_products(N) << endl;
    return 0;
}

int sum_products(const int n) {
    int sum = 0;
    int product = 1;
    for (int i = 1; i <= n; i++) {
        product *= i;
        sum += product;
    }
    return sum;
}
