#include <string>
#include <iostream>
#include "util.h"
#include "b_28.h"

int main() {
    using namespace std;
    cout << "b_28: ĐỔI CHỖ CHỮ SỐ" << endl;
    string line;
    cout << "Nhập số bộ test T:" << endl;
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
    vector<int> d_inputs(T);
    for (int i = 0; i < T; i++) {
        cout << "Nhập bộ test " << i + 1 << " - Số N:" << endl;
        do {
            is_valid = false;
            getline(cin, line);
            try {
                int N = parse_int(line);
                if (N < 1) {
                    cerr << "n phải >= 1" << endl;
                    continue;
                }
                if (N > 100000) {
                    cerr << "n phải <= 100000" << endl;
                    continue;
                }
                d_inputs[i] = N;
            } catch (const exception &e) {
                cerr << e.what() << endl;
                continue;
            }
            is_valid = true;
        } while (!is_valid);
    }
    cout << "Kết quả:" << endl;
    for (int i = 0; i < T; i++) {
        const int N = d_inputs[i];
        const int swap_count = find_largest_smaller_number(N);
        cout << swap_count << endl;
    }
    return 0;
}

int find_largest_smaller_number(const int n) {
    using namespace std;
    string N = to_string(n);
    const int len = N.length();
    int swap1 = -1, swap2 = -1;

    // Tìm vị trí có thể hoán đổi
    for (int i = len - 2; i >= 0; i--) {
        for (int j = len - 1; j > i; j--) {
            if (N[j] < N[i]) {
                // Tìm vị trí hoán đổi
                if (swap1 == -1 || N[j] > N[swap2]) {
                    swap1 = i;
                    swap2 = j;
                }
            }
        }
    }

    if (swap1 == -1) return -1; // Không thể hoán đổi

    // Hoán đổi các chữ số tại swap1 và swap2
    swap(N[swap1], N[swap2]);
    return parse_int(N);
}
