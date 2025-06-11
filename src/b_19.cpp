#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <functional>
#include "b_19.h"

int main() {
    using namespace std;
    // cerr << "b_19: SẮP XẾP CHỮ SỐ" << endl;
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
    vector<vector<long>> v_inputs(T);
    for (int i = 0; i < T; i++) {
        // cerr << "Nhập bộ test " << i + 1 << " - Số N:" << endl;
        getline(cin, line);
        int N;
        try {
            N = parse_int(line);
            if (N < 1) {
                cerr << "N phải >= 1" << endl;
                return 2;
            }
            if (N > 10000000) {
                cerr << "N phải <= 10000000" << endl;
                return 2;
            }
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
        // cerr << "Nhập bộ test " << i + 1 << " - Dãy số A[] gồm " << N << " phần tử:" << endl;
        getline(cin, line);
        try {
            // hàm lambda validate từng phần tử đọc được
            static const function<string(int, long)> validate_func = [](const int pos, const long value) {
                if (value < 0) {
                    return "A[" + to_string(pos) + "] phải >= 0";
                }
                if (value > 10000000000000000) {
                    return "A[" + to_string(pos) + "] phải <= 10000000000000000";
                }
                static string oke_msg;
                return oke_msg;
            };
            v_inputs[i] = string_to_long_vector(line, N, validate_func);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
    }
    // cerr << "Kết quả:" << endl;
    for (int i = 0; i < T; i++) {
        const vector<long>& A = v_inputs[i];
        set<int> digit_set = sort_digits_array(A);
        for (const int d: digit_set) {
            cout << d << " ";
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

std::vector<long> string_to_long_vector(const std::string &line, const int expected_size, const std::function<std::string(int, long)> &validate_func) {
    using namespace std;
    vector<long> result;
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
            throw exit_code_exception(2, "Chuỗi nhập không phải số kiểu long hợp lệ");
        } catch (const out_of_range &e) {
            throw exit_code_exception(2, "Số vượt quá phạm vi kiểu long");
        }
    }
    if (pos < expected_size) {
        throw exit_code_exception(2, "Số lượng phần tử thiếu, cần " + to_string(expected_size));
    }
    return result;
}

std::set<int> sort_digits_array(const std::vector<long> &A) {
    using namespace std;
    const size_t n = A.size();
    set<int> digits_set;
    for (size_t i = 0; i < n; ++i) {
        string s = to_string(A[i]);
        for (const char c: s) {
            if (isdigit(c)) {
                digits_set.insert(c - '0');
            }
        }
    }
    // set tự động sắp xếp
    return digits_set;
}
