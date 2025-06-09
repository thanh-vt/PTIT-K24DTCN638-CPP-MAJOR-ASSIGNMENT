#include <iostream>
#include <string>
#include <regex>
#include "util.h"
#include "b_13.h"

int main() {
    using namespace std;
    cout << "b_13: BIÊN CỦA MA TRẬN" << endl;
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
    vector<vector<vector<int>>> A_inputs(T);
    for (int i = 0; i < T; i++) {
        cout << "Nhập bộ test " << i + 1 << " - Số N:" << endl;
        int N = 0;
        do {
            is_valid = false;
            getline(cin, line);
            try {
                N = parse_int(line);
                if (N < 1) {
                    cerr << "n phải >= 1" << endl;
                    continue;
                }
                if (N > 100) {
                    cerr << "n phải <= 100" << endl;
                    continue;
                }
            } catch (const exception &e) {
                cerr << e.what() << endl;
                continue;
            }
            is_valid = true;
        } while (!is_valid);
        vector<vector<int> > A(N, vector<int>(N));
        cout << "Nhập bộ test " << i + 1 << " - Ma trận A[][]  gồm " << N << "x" << N << "=" << N*N << " phần tử:" << endl;
        do {
            is_valid = false;
            getline(cin, line);
            try {
                // hàm lambda validate từng phần tử đọc được
                static const function<string(int, int)> validate_func = [](const int pos, const long value) {
                    if (value < 1) {
                        return "A[" + to_string(pos) + "] phải >= 1";
                    }
                    if (value > 150) {
                        return "A[" + to_string(pos) + "] phải <= 150";
                    }
                    static string oke_msg;
                    return oke_msg;
                };
                vector<int> B = string_to_int_vector(line, N * N, validate_func);
                for (int j = 0; j < N; j++) {
                    const vector<int> C(B.begin() + j * N, B.begin() + (j + 1) * N);
                    A[j] = C;
                }
            } catch (const exception &e) {
                cerr << e.what() << endl;
                continue;
            }
            is_valid = true;
        } while (!is_valid);
        A_inputs[i] = A;
    }
    cout << "Kết quả:" << endl;
    for (const vector<vector<int>>& A: A_inputs) {
        print_matrix_borders(A);
    }
    return 0;
}

void print_matrix_borders(const std::vector<std::vector<int> > &A) {
    using namespace std;
    const size_t n = A.size();
    // In dòng đầu đầy đủ
    for (size_t j = 0; j < n; j++) {
        cout << A[0][j];
        if (j < n - 1) cout << " ";
    }
    cout << endl;

    // In các dòng giữa: phần tử đầu, 4 dấu cách, phần tử cuối
    for (int i = 1; i < n - 1; i++) {
        cout << A[i][0];
        cout << "    ";  // 4 dấu cách
        cout << A[i][n - 1] << endl;
    }

    // In dòng cuối đầy đủ
    for (int j = 0; j < n; j++) {
        cout << A[n - 1][j];
        if (j < n - 1) cout << " ";
    }
    cout << endl;
}
