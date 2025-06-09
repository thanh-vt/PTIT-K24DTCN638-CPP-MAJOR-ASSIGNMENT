#include <iostream>
#include <vector>
#include "util.h"
#include "b_08.h"

int main() {
    using namespace std;
    cout << "b_08: LIỆT KÊ SỐ CÓ BA ƯỚC SỐ" << endl;
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
    // Dùng thuật toán sàng nguyên tố Eratosthenes để tìm các số nguyên tố đến 1000 (vì 1000^2 = 1,000,000)
    const vector<int> squares = sieve(1000);
    for (int i = 0; i < T; i++) {
        // Xử lý dòng đọc được
        cout << "Nhập bộ test " << i + 1 << ":" << endl;
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
            if (N < 1) {
                cout << "N phải >= 1" << endl;
                continue;
            }
            if (N > 1000000) {
                cout << "N phải <= 1000000" << endl;
                continue;
            }
            is_valid = true;
            inputs[i] = N;
        } while (!is_valid);
    }
    cout << "Kết quả:" << endl;
    for (const int N: inputs) {
        bool first = true;
        for (const int x : squares) {
            if (x > N) break;
            if (!first) cout << " ";
            cout << x;
            first = false;
        }
        cout << endl;
    }
    return 0;
}

std::vector<int> sieve(const int max) {
    using namespace std;
    bool isPrime[max + 1];
    vector<int> squares; // Lưu p^2 với p nguyên tố
    fill(isPrime, isPrime + max + 1, true);
    isPrime[0] = isPrime[1] = false; // Số 0 và số 1 không phải số nguyên tố nên ta đánh dấu false cho hai vị trí này ngay từ đầu
    for (int i = 2; i * i <= max; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= max; j += i) {
                isPrime[j] = false;
            }
        }
    }
    for (int i = 2; i <= max; i++) {
        if (isPrime[i]) {
            squares.push_back(i * i);
        }
    }
    return squares;
}
