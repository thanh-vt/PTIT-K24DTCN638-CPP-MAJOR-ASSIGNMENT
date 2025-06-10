#include <iostream>
#include <string>
#include <regex>
#include "util.h"
#include "b_12.h"

int main() {
    using namespace std;
    // cerr << "b_12: BIẾN ĐỔI NHỊ PHÂN" << endl;
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
        if (T > 100) {
            cerr << "T phải <= 100" << endl;
            continue;
        }
        is_valid = true;
    } while (!is_valid);
    vector<int> n_inputs(T);
    vector<int> m_inputs(T);
    vector<vector<vector<int>>> A_inputs(T);
    for (int i = 0; i < T; i++) {
        cerr << "Nhập bộ test " << i + 1 << " - Số n và m:" << endl;
        int n = 0, m = 0;
        do {
            is_valid = false;
            getline(cin, line);
            static regex ws_re(" +");  // tách chuỗi bởi khoảng trắng, static để tránh compile lại regex nhiều lần khi chạy chương trình
            const sregex_token_iterator iter(line.begin(), line.end(), ws_re, -1);
            const sregex_token_iterator end;
            vector<string> result(iter, end);
            if (result.size() != 2) {
                cerr << "Dòng phải có 2 số n và m" << endl;
                continue;
            }
            try {
                n = parse_int(result[0]);
                if (n < 1) {
                    cerr << "n phải >= 1" << endl;
                    continue;
                }
                if (n > 100) {
                    cerr << "n phải <= 100" << endl;
                    continue;
                }
                n_inputs[i] = n;
            } catch (const exception &e) {
                cerr << e.what() << endl;
                continue;
            }
            try {
                m = parse_int(result[1]);
                if (m < 1) {
                    cerr << "m phải >= 1" << endl;
                    continue;
                }
                if (m > 100) {
                    cerr << "m phải <= 100" << endl;
                    continue;
                }
                m_inputs[i] = m;
            } catch (const exception &e) {
                cerr << e.what() << endl;
                continue;
            }
            is_valid = true;
        } while (!is_valid);
        vector<vector<int> > A(n, vector<int>(m));
        for (int j = 0; j < n; ++j) {
            cerr << "Nhập bộ test " << i + 1 << " - Ma trận A[][] hàng " << j + 1 << " gồm " << m << " phần tử:" << endl;
            do {
                is_valid = false;
                getline(cin, line);
                try {
                    // hàm lambda validate từng phần tử đọc được
                    static const function<string(int, int)> validate_func = [j](const int pos, const long value) {
                        if (value != 0 && value != 1) {
                            return "A[" + to_string(j) + "][" + to_string(pos) + "] phải = 0 hoặc 1";
                        }
                        static string oke_msg;
                        return oke_msg;
                    };
                    vector<int> B = string_to_int_vector(line, m, validate_func);
                    A[j] = B;
                } catch (const exception &e) {
                    cerr << e.what() << endl;
                    continue;
                }
                is_valid = true;
            } while (!is_valid);
        }
        A_inputs[i] = A;
    }
    // cerr << "Kết quả:" << endl;
    for (int i = 0; i < T; i++) {
        int n = n_inputs[i];
        int m = m_inputs[i];
        const vector<vector<int>>& A = A_inputs[i];
        print_modified_matrix(A, n, m);
    }

    return 0;
}

void print_modified_matrix(std::vector<std::vector<int> > A, const int n, const int m) {
    using namespace std;
    vector<bool> row_flag(n, false);
    vector<bool> col_flag(m, false);

    // Tìm hàng và cột có phần tử = 1
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (A[i][j] == 1) {
                row_flag[i] = true;
                col_flag[j] = true;
            }
        }
    }

    // Biến đổi ma trận theo row_flag và col_flag
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (row_flag[i] || col_flag[j]) {
                A[i][j] = 1;
            }
        }
    }

    // In ra kết quả theo yêu cầu: mỗi test trên 1 dòng, in nối các phần tử
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << A[i][j];
            if (i != n - 1 || j != m - 1) cout << " ";
        }
        cout << endl;
    }
}
