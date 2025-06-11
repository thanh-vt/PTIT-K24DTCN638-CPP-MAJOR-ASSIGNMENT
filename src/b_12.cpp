#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <functional>
#include <sstream>
#include "b_12.h"

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
void print_modified_matrix(std::vector<std::vector<int> > A, const int n, const int m);

int main() {
    using namespace std;
    // cerr << "b_12: BIẾN ĐỔI NHỊ PHÂN" << endl;
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
    vector<int> n_inputs(T);
    vector<int> m_inputs(T);
    vector<vector<vector<int>>> A_inputs(T);
    for (int i = 0; i < T; i++) {
        // cerr << "Nhập bộ test " << i + 1 << " - Số n và m:" << endl;
        int n = 0, m = 0;
        getline(cin, line);
        static regex ws_re(" +");  // tách chuỗi bởi khoảng trắng, static để tránh compile lại regex nhiều lần khi chạy chương trình
        const sregex_token_iterator iter(line.begin(), line.end(), ws_re, -1);
        const sregex_token_iterator end;
        vector<string> result(iter, end);
        if (result.size() != 2) {
            cerr << "Dòng phải có 2 số n và m" << endl;
            return 2;
        }
        try {
            n = parse_int(result[0]);
            if (n < 1) {
                cerr << "n phải >= 1" << endl;
                return 2;
            }
            if (n > 100) {
                cerr << "n phải <= 100" << endl;
                return 2;
            }
            n_inputs[i] = n;
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
        try {
            m = parse_int(result[1]);
            if (m < 1) {
                cerr << "m phải >= 1" << endl;
                return 2;
            }
            if (m > 100) {
                cerr << "m phải <= 100" << endl;
                return 2;
            }
            m_inputs[i] = m;
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
        vector<vector<int> > A(n, vector<int>(m));
        for (int j = 0; j < n; ++j) {
            // cerr << "Nhập bộ test " << i + 1 << " - Ma trận A[][] hàng " << j + 1 << " gồm " << m << " phần tử:" << endl;
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
                return 2;
            }
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
