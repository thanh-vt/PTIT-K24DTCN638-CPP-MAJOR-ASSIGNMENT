#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <functional>
#include <sstream>
#include "b_11.h"

int main() {
    using namespace std;
    // cerr << "b_11: QUAY VÒNG DÃY SỐ 1" << endl;
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
    if (T > 10) {
        cerr << "T phải <= 10" << endl;
        return 2;
    }
    vector<int> d_inputs(T);
    vector<vector<int> > v_inputs(T);
    for (int i = 0; i < T; i++) {
        int n, d;
        // cerr << "Nhập bộ test " << i + 1 << " - Số n và d:" << endl;
        getline(cin, line);
        static regex ws_re(" +");  // tách chuỗi bởi khoảng trắng, static để tránh compile lại regex nhiều lần khi chạy chương trình
        const sregex_token_iterator iter(line.begin(), line.end(), ws_re, -1);
        const sregex_token_iterator end;
        vector<string> result(iter, end);
        if (result.size() != 2) {
            cerr << "Dòng phải có 2 số n và d" << endl;
            return 2;
        }
        try {
            n = parse_int(result[0]);
            if (n < 1) {
                cerr << "n phải >= 1" << endl;
                return 2;
            }
            if (n > 1000000) {
                cerr << "n phải <= 1000000" << endl;
                return 2;
            }
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
        try {
            d = parse_int(result[1]);
            if (d < 1) {
                cerr << "d phải >= 1" << endl;
                return 2;
            }
            if (d > 1000000) {
                cerr << "d phải <= 1000000" << endl;
                return 2;
            }
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
        if (d >= n) {
            cerr << "d phải < n" << endl;
            return 2;
        }
        d_inputs[i] = d;
        // cerr << "Nhập bộ test " << i + 1 << " - Dãy A[] gồm " << n << " phần tử:" << endl;
        getline(cin, line);
        try {
            // hàm lambda validate từng phần tử đọc được
            static const function<string(int, int)> validate_func = [](const int pos, const long value) {
                if (value < 0) {
                    return "A[" + to_string(pos) + "] phải >= 0";
                }
                if (value > 100000) {
                    return "A[" + to_string(pos) + "] phải <= 100000";
                }
                static string oke_msg;
                return oke_msg;
            };
            vector<int> A = string_to_int_vector(line, n, validate_func);
            v_inputs[i] = A;
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
    }
    // cerr << "Kết quả:" << endl;
    for (int i = 0; i < T; i++) {
        const vector<int>& A = v_inputs[i];
        int d = d_inputs[i];
        vector<int> rotated_A = rotate_vector(A, d);
        size_t n = rotated_A.size();
        for (int j = 0; j < n; j++) {
            cout << rotated_A[j];
            if (j < n - 1) cout << " ";
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

std::vector<int> rotate_vector(const std::vector<int>& A, const int d) {
    using namespace std;
    const size_t n = A.size();
    vector<int> rotated(n);
    // Copy từ A[d..n-1]
    for (int i = 0; i < n - d; i++) {
        rotated[i] = A[i + d];
    }
    // Copy từ A[0..d-1]
    for (int i = n - d; i < n; i++) {
        rotated[i] = A[i - (n - d)];
    }
    return rotated;
}
