#include <iostream>
#include <string>
#include <sstream>
#include <functional>
#include "b_27.h"

int main() {
    using namespace std;
    // cerr << "b_27: CỬA SỔ TRƯỢT" << endl;
    string line;
    // cerr << "Nhập số N:" << endl;
    getline(cin, line);
    int N;
    try {
        N = parse_int(line);
        if (N <= 3) {
            cerr << "N phải > 3" << endl;
            return 2;
        }
        if (N >= 100) {
            cerr << "N phải < 100" << endl;
            return 2;
        }
    } catch (const exception &e) {
        cerr << e.what() << endl;
        return 2;
    }
    vector<vector<int>>A(N, vector<int>(N));
    for (int j = 0; j < N; ++j) {
        // cerr << "Nhập ma trận A[][] hàng " << j + 1 << " gồm " << N << " phần tử:" << endl;
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
            A[j] = string_to_int_vector(line, N, validate_func);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
    }
    // cerr << "Nhập số M:" << endl;
    getline(cin, line);
    int M;
    try {
        M = parse_int(line);
        if (M <= 1) {
            cerr << "M phải > 1" << endl;
            return 2;
        }
        if (M >= 10) {
            cerr << "M phải < 10" << endl;
            return 2;
        }
        if (N % M != 0) {
            cerr << "M phải là ước số của N" << endl;
            return 2;
        }
    } catch (const exception &e) {
        cerr << e.what() << endl;
        return 2;
    }
    vector<vector<int>>B(M, vector<int>(M));
    for (int j = 0; j < M; ++j) {
        // cerr << "Nhập ma trận B[][] hàng " << j + 1 << " gồm " << M << " phần tử:" << endl;
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
            B[j] = string_to_int_vector(line, M, validate_func);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
    }
    // cerr << "Kết quả:" << endl;
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
