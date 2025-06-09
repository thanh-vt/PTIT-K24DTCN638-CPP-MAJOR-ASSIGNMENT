#include <iostream>
#include "util.h"
#include "b_07.h"

int main() {
    using namespace std;
    cout << "b_07: ƯỚC SỐ NGUYÊN TỐ" << endl;
    string line;
    cout << "Nhập số bộ test T:" << endl;
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
        cout << "Nhập bộ test " << i + 1 << ":" << endl;
        do {
            is_valid = false;
            getline(cin, line);
            long N;
            try {
                N = parse_long(line);
            } catch(const exception &e) {
                cerr << e.what() << endl;
                continue;
            }
            if (N < 1) {
                cout << "N phải >= 1" << endl;
                continue;
            }
            if (N > 10000000000) {
                cout << "N phải <= 10000000000" << endl;
                continue;
            }
            is_valid = true;
            inputs[i] = N;
        } while (!is_valid);
    }
    cout << "Kết quả:" << endl;
    for (const int N: inputs) {
        print_factorization(N);
    }
    return 0;
}

void print_factorization(long n) {
    using namespace std;
    while (n % 2 == 0) {
        cout << 2 << " ";
        n /= 2;
    }

    for (long i = 3; i * i <= n; i += 2) {
        while (n % i == 0) {
            cout << i << " ";
            n /= i;
        }
    }

    if (n > 2) {
        cout << n;
    }

    cout << endl;
}
