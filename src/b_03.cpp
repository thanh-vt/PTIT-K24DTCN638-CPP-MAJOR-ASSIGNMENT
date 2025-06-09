#include <iostream>
#include "util.h"
#include "b_03.h"

int main() {
    using namespace std;
    cout << "b_03: TÍNH TỔNG GIAI THỪA" << endl;
    cout << "Nhập N:" << endl;
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
            return 2;
        }
        if (N > 20) {
            cerr << "N phải <= 20" << endl;
            return 2;
        }
        is_valid = true;
    } while (!is_valid);
    cout << "Kết quả:" << endl;
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
