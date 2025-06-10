#include <iostream>
#include <string>
#include "util.h"
#include "b_27.h"

int main() {
    using namespace std;
    cerr << "b_27: CỬA SỔ TRƯỢT" << endl;
    string line;
    cerr << "Nhập số N:" << endl;
    bool is_valid = false;
    int N = 0;
    do {
        is_valid = false;
        getline(cin, line);
        try {
            N = parse_int(line);
            if (N <= 3) {
                cerr << "N phải > 3" << endl;
                continue;
            }
            if (N >= 100) {
                cerr << "N phải < 100" << endl;
                continue;
            }
        } catch (const exception &e) {
            cerr << e.what() << endl;
            continue;
        }
        is_valid = true;
    } while (!is_valid);
    vector<vector<int>>A(N, vector<int>(N));
    for (int j = 0; j < N; ++j) {
        cerr << "Nhập ma trận A[][] hàng " << j + 1 << " gồm " << N << " phần tử:" << endl;
        do {
            is_valid = false;
            getline(cin, line);
            try {
                // hàm lambda validate từng phần tử đọc được
                static const function<string(int, int)> validate_func = [](const int pos, const long value) {
                    if (value <= 0) {
                        return "A[" + to_string(pos) + "] phải > 0";
                    }
                    if (value > 1000) {
                        return "A[" + to_string(pos) + "] phải <= 1000";
                    }
                    static string oke_msg;
                    return oke_msg;
                };
                const vector<int> AJ = string_to_int_vector(line, N, validate_func);
                A[j] = AJ;
            } catch (const exception &e) {
                cerr << e.what() << endl;
                continue;
            }
            is_valid = true;
        } while (!is_valid);
    }
    cerr << "Nhập số M:" << endl;
    int M = 0;
    do {
        is_valid = false;
        getline(cin, line);
        try {
            M = parse_int(line);
            if (M <= 1) {
                cerr << "M phải > 1" << endl;
                continue;
            }
            if (M >= 10) {
                cerr << "M phải < 10" << endl;
                continue;
            }
            if (N % M != 0) {
                cerr << "M phải là ước số của N" << endl;
                continue;
            }
        } catch (const exception &e) {
            cerr << e.what() << endl;
            continue;
        }
        is_valid = true;
    } while (!is_valid);
    vector<vector<int>>B(M, vector<int>(M));
    for (int j = 0; j < M; ++j) {
        cerr << "Nhập ma trận B[][] hàng " << j + 1 << " gồm " << M << " phần tử:" << endl;
        do {
            is_valid = false;
            getline(cin, line);
            try {
                // hàm lambda validate từng phần tử đọc được
                static const function<string(int, int)> validate_func = [](const int pos, const long value) {
                    if (value < 0) {
                        return "B[" + to_string(pos) + "] phải >= 0";
                    }
                    if (value > 20) {
                        return "B[" + to_string(pos) + "] phải <= 20";
                    }
                    static string oke_msg;
                    return oke_msg;
                };
                const vector<int> BJ = string_to_int_vector(line, M, validate_func);
                B[j] = BJ;
            } catch (const exception &e) {
                cerr << e.what() << endl;
                continue;
            }
            is_valid = true;
        } while (!is_valid);
    }
    cerr << "Kết quả:" << endl;
    const vector<vector<int>> result = print_convolution_matrix(A, B);
    // In ra ma trận kết quả
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << result[i][j];
            if (j < N - 1) cout << " ";
        }
        cout << endl;
    }
    return 0;
}

std::vector<std::vector<int>> print_convolution_matrix(const std::vector<std::vector<int>> &A, const std::vector<std::vector<int>> &B) {
    using namespace std;
    const size_t N = A.size();
    const size_t M = B.size();
    // Tạo ma trận kết quả
    vector<vector<int>> result(N, vector<int>(N, 0));
    // Tính tích chập
    for (int i = 0; i <= N - M; i += M) {
        for (int j = 0; j <= N - M; j += M) {
            // Lặp qua các phần tử trong cửa sổ trượt MxM
            for (int k = 0; k < M; k++) {
                for (int l = 0; l < M; l++) {
                    // Tính tích của mỗi phần tử tương ứng trong A và B
                    result[i + k][j + l] = A[i + k][j + l] * B[k][l];
                }
            }
        }
    }
    return result;
}
