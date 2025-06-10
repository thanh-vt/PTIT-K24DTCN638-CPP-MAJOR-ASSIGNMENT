#include <complex>
#include <iostream>
#include "util.h"
#include "b_04.h"

int main() {
    using namespace std;
    cerr << "b_04: CÂN BẰNG CHẴN LẺ" << endl;
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
        if (N <= 1) {
            cerr << "N phải > 1" << endl;
            continue;
        }
        if (N >= 7) {
            cerr << "N phải < 7" << endl;
            continue;
        }
        if (N % 2 != 0) {
            cerr << "N phải là số chẵn" << endl;
            continue;
        }
        is_valid = true;
    } while (!is_valid);
    cerr << "Kết quả:" << endl;
    const int start = static_cast<int>(pow(10, N - 1));
    const int end = static_cast<int>(pow(10, N)) - 1;
    int count = 0;
    for (int num = start; num <= end; ++num) {
        if (has_equal_odd_even_digits(num)) {
            count ++;
            cout << num << " ";
            if (count % 10 == 0) {
                cout << endl;
            }
        }
    }
    cout << endl;
    return 0;
}

bool has_equal_odd_even_digits(int n) {
    int oddCount = 0, evenCount = 0;

    while (n > 0) {
        const int digit = n % 10;
        if (digit % 2 == 0)
            evenCount++;
        else
            oddCount++;
        n /= 10;
    }

    return oddCount == evenCount;
}