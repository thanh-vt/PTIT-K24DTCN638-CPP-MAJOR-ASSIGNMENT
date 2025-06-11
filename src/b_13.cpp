#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <functional>
#include <sstream>
#include "b_13.h"

class exit_code_exception : public std::exception {
    int code;
    std::string message;
public:
    explicit exit_code_exception(const int c, std::string m) : code(c), message(std::move(m)) {}
    int getCode() const { return code; }
    const char* what() const noexcept override {
        return message.c_str();
    }
};

// Function declarations
int parse_int(const std::string &line);
std::vector<int> string_to_int_vector(const std::string &s, const size_t size, const std::function<std::string(int, int)>& validate_func);
void print_matrix_borders(const std::vector<std::vector<int> > &A);

int main() {
    using namespace std;
    // cerr << "b_13: BIÊN CỦA MA TRẬN" << endl;
    string line;
    // cerr << "Nhập số bộ test T:" << endl;
    getline(cin, line);
    int T;
    try {
        T = parse_int(line);
    } catch (const exception &e) {
        cerr << e.what() << endl;
        return 2;
    }
    if (T < 1) {
        cerr << "T phải >= 1" << endl;
        return 2;
    }
    if (T > 100) {
        cerr << "T phải <= 100" << endl;
        return 2;
    }
    vector<vector<vector<int>>> A_inputs(T);
    for (int i = 0; i < T; i++) {
        // cerr << "Nhập bộ test " << i + 1 << " - Số N:" << endl;
        getline(cin, line);
        int N;
        try {
            N = parse_int(line);
            if (N < 1) {
                cerr << "n phải >= 1" << endl;
                return 2;
            }
            if (N > 100) {
                cerr << "n phải <= 100" << endl;
                return 2;
            }
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
        vector<vector<int> > A(N, vector<int>(N));
        // cerr << "Nhập bộ test " << i + 1 << " - Ma trận A[][]  gồm " << N << "x" << N << "=" << N*N << " phần tử:" << endl;
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
            return 2;
        }
        A_inputs[i] = A;
    }
    // cerr << "Kết quả:" << endl;
    for (const vector<vector<int>>& A: A_inputs) {
        print_matrix_borders(A);
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

std::vector<int> string_to_int_vector(const std::string &s, const size_t size, const std::function<std::string(int, int)>& validate_func) {
    using namespace std;
    vector<int> result;
    istringstream iss(s);
    string token;
    int pos = 0;
    while (iss >> token) {
        int number;
        try {
            number = parse_int(token);
        } catch (const exception &e) {
            throw exit_code_exception(2, "Lỗi đọc phần tử thứ " + to_string(pos + 1) + ": " + string(e.what()));
        }
        if (validate_func != nullptr) {
            string err = validate_func(pos, number);
            if (!err.empty()) {
                throw exit_code_exception(2, "Lỗi đọc phần tử thứ " + to_string(pos + 1) + ": " + err);
            }
        }
        result.push_back(number);
        pos++;
    }
    if (result.size() > size) {
        throw exit_code_exception(2, "Dòng nhập có số lượng phần tử > " + to_string(size));
    }
    if (result.size() < size) {
        throw exit_code_exception(2, "Dòng nhập có số lượng phần tử < " + to_string(size));
    }
    return result;
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
