#include <iostream>
#include <string>
#include <regex>
#include "util.h"
#include "b_25.h"

int main() {
    using namespace std;
    cout << "b_25: QUAY MA TRẬN" << endl;
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
    vector<int> n_inputs(T);
    vector<int> m_inputs(T);
    vector<vector<vector<int>>> A_inputs(T);
    for (int i = 0; i < T; i++) {
        cout << "Nhập bộ test " << i + 1 << " - Số n và m:" << endl;
        int N = 0, M = 0;
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
                N = parse_int(result[0]);
                if (N < 1) {
                    cerr << "n phải >= 1" << endl;
                    continue;
                }
                if (N > 100) {
                    cerr << "n phải <= 100" << endl;
                    continue;
                }
                n_inputs[i] = N;
            } catch (const exception &e) {
                cerr << e.what() << endl;
                continue;
            }
            try {
                M = parse_int(result[1]);
                if (M < 1) {
                    cerr << "m phải >= 1" << endl;
                    continue;
                }
                if (M > 100) {
                    cerr << "m phải <= 100" << endl;
                    continue;
                }
                m_inputs[i] = M;
            } catch (const exception &e) {
                cerr << e.what() << endl;
                continue;
            }
            is_valid = true;
        } while (!is_valid);
        vector<vector<int> > A(N, vector<int>(M));
        cout << "Nhập bộ test " << i + 1 << " - Ma trận A[][] gồm " << N << "x" << M << "=" << N*M << " phần tử:" << endl;
        do {
            is_valid = false;
            getline(cin, line);
            try {
                // hàm lambda validate từng phần tử đọc được
                static const function<string(int, int)> validate_func = [](const int pos, const long value) {
                    if (value < 1) {
                        return "A[" + to_string(pos) + "] phải >= 1";
                    }
                    if (value > 100000) {
                        return "A[" + to_string(pos) + "] phải <= 100000";
                    }
                    static string oke_msg;
                    return oke_msg;
                };
                vector<int> B = string_to_int_vector(line, N * M, validate_func);
                for (int j = 0; j < N; j++) {
                    const vector<int> C(B.begin() + j * M, B.begin() + (j + 1) * M);
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
    for (int i = 0; i < T; i++) {
        int n = n_inputs[i];
        int m = m_inputs[i];
        std::vector<std::vector<int>> &A = A_inputs[i];
        rotate_matrix(A, n, m);
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < m; ++k) {
                cout << A[j][k] << " ";
            }
        }
        cout << endl;
    }
    return 0;
}

void rotate_matrix(std::vector<std::vector<int>>& mat, const int n, const int m) {
    using namespace std;
    int top = 0, bottom = n - 1, left = 0, right = m - 1;

    while (top < bottom && left < right) {
        // Lưu các phần tử của lớp hiện tại
        vector<int> temp;

        // Top row
        for (int i = left; i < right; ++i)
            temp.push_back(mat[top][i]);

        // Right column
        for (int i = top; i < bottom; ++i)
            temp.push_back(mat[i][right]);

        // Bottom row
        for (int i = right; i > left; --i)
            temp.push_back(mat[bottom][i]);

        // Left column
        for (int i = bottom; i > top; --i)
            temp.push_back(mat[i][left]);

        // Xoay phải 1 bước
        int last = temp.back();
        temp.pop_back();
        temp.insert(temp.begin(), last);

        // Gán lại các giá trị vào ma trận
        int idx = 0;

        // Top row
        for (int i = left; i < right; ++i)
            mat[top][i] = temp[idx++];

        // Right column
        for (int i = top; i < bottom; ++i)
            mat[i][right] = temp[idx++];

        // Bottom row
        for (int i = right; i > left; --i)
            mat[bottom][i] = temp[idx++];

        // Left column
        for (int i = bottom; i > top; --i)
            mat[i][left] = temp[idx++];

        top++;
        bottom--;
        left++;
        right--;
    }
}
