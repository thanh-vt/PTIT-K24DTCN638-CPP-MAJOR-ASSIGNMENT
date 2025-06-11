#include <string>
#include <iostream>
#include <sstream>
#include <functional>
#include <vector>
#include "b_28.h"

int main() {
    using namespace std;
    // cerr << "b_28: ĐỔI CHỖ CHỮ SỐ" << endl;
    string line;
    // cerr << "Nhập số bộ test T:" << endl;
    getline(cin, line);
    int T;
    try {
        T = parse_int(line);
        if (T < 1) {
            cerr << "T phải >= 1" << endl;
            return 2;
        }
        if (T > 100) {
            cerr << "T phải <= 100" << endl;
            return 2;
        }
    } catch (const exception &e) {
        cerr << e.what() << endl;
        return 2;
    }
    vector<int> d_inputs(T);
    for (int i = 0; i < T; i++) {
        // cerr << "Nhập bộ test " << i + 1 << " - Số N:" << endl;
        getline(cin, line);
        try {
            int N = parse_int(line);
            if (N < 1) {
                cerr << "n phải >= 1" << endl;
                return 2;
            }
            if (N > 100000) {
                cerr << "n phải <= 100000" << endl;
                return 2;
            }
            d_inputs[i] = N;
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
    }
    // cerr << "Kết quả:" << endl;
    for (int i = 0; i < T; i++) {
        const int N = d_inputs[i];
        const int swap_count = find_largest_smaller_number(N);
        cout << swap_count << endl;
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
