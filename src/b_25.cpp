#include <iostream>
#include <string>
#include <regex>
#include <sstream>
#include <functional>
#include "b_25.h"

int main() {
    using namespace std;
    // cerr << "b_25: QUAY MA TRẬN" << endl;
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
    vector<int> n_inputs(T);
    vector<int> m_inputs(T);
    vector<vector<vector<int>>> A_inputs(T);
    for (int i = 0; i < T; i++) {
        // cerr << "Nhập bộ test " << i + 1 << " - Số n và m:" << endl;
        getline(cin, line);
        static regex ws_re(" +");  // tách chuỗi bởi khoảng trắng, static để tránh compile lại regex nhiều lần khi chạy chương trình
        const sregex_token_iterator iter(line.begin(), line.end(), ws_re, -1);
        const sregex_token_iterator end;
        vector<string> result(iter, end);
        if (result.size() != 2) {
            cerr << "Dòng phải có 2 số n và m" << endl;
            return 2;
        }
        int N;
        try {
            N = parse_int(result[0]);
            if (N < 1) {
                cerr << "n phải >= 1" << endl;
                return 2;
            }
            if (N > 100) {
                cerr << "n phải <= 100" << endl;
                return 2;
            }
            n_inputs[i] = N;
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
        int M;
        try {
            M = parse_int(result[1]);
            if (M < 1) {
                cerr << "m phải >= 1" << endl;
                return 2;
            }
            if (M > 100) {
                cerr << "m phải <= 100" << endl;
                return 2;
            }
            m_inputs[i] = M;
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
        vector<vector<int> > A(N, vector<int>(M));
        // cerr << "Nhập bộ test " << i + 1 << " - Ma trận A[][] gồm " << N << "x" << M << "=" << N*M << " phần tử:" << endl;
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
            return 2;
        }
        A_inputs[i] = A;
    }
    // cerr << "Kết quả:" << endl;
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

std::vector<int> string_to_int_vector(const std::string &line, const int expected_size, const std::function<std::string(int, long)> &validate_func) {
    using namespace std;
    vector<int> result;
    istringstream iss(line);
    string token;
    int pos = 0;
    while (iss >> token) {
        if (pos >= expected_size) {
            throw exit_code_exception(2, "Số lượng phần tử vượt quá " + to_string(expected_size));
        }
        try {
            size_t pos_end;
            const long value = stol(token, &pos_end);
            if (pos_end != token.size()) {
                throw exit_code_exception(2, "Chuỗi nhập có chứa các ký tự không hợp lệ");
            }
            const string validate_msg = validate_func(pos, value);
            if (!validate_msg.empty()) {
                throw exit_code_exception(2, validate_msg);
            }
            result.push_back(value);
            pos++;
        } catch (const invalid_argument &e) {
            throw exit_code_exception(2, "Chuỗi nhập không phải số kiểu integer hợp lệ");
        } catch (const out_of_range &e) {
            throw exit_code_exception(2, "Số vượt quá phạm vi kiểu integer");
        }
    }
    if (pos < expected_size) {
        throw exit_code_exception(2, "Số lượng phần tử thiếu, cần " + to_string(expected_size));
    }
    return result;
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
