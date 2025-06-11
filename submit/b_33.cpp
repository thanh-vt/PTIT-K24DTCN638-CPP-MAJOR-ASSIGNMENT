#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <functional>
#include <vector>
#include "b_33.h"

int main() {
    using namespace std;
    // cerr << "b_33: SẮP XẾP XEN KẼ - 2" << endl;
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
    vector<vector<int> > A_inputs(T);
    for (int i = 0; i < T; i++) {
        // cerr << "Nhập bộ test " << i + 1 << " - Số n:" << endl;
        getline(cin, line);
        int n;
        try {
            n = parse_int(line);
            if (n < 1) {
                cerr << "n phải >= 1" << endl;
                return 2;
            }
            if (n > 1000) {
                cerr << "n phải <= 1000" << endl;
                return 2;
            }
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
        // cerr << "Nhập bộ test " << i + 1 << " - Dãy A[] gồm " << n << " phần tử:" << endl;
        getline(cin, line);
        try {
            static const function<string(int, int)> validate_func = [](const int pos, const long value) {
                if (value < 1) {
                    return "A[" + to_string(pos) + "] phải >= 0";
                }
                if (value > 1000) {
                    return "A[" + to_string(pos) + "] phải <= 1000";
                }
                static string oke_msg;
                return oke_msg;
            };
            A_inputs[i] = string_to_int_vector(line, n, validate_func);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
    }
    // cerr << "Kết quả:" << endl;
    for (int i = 0; i < T; i++) {
        vector<int> &A = A_inputs[i];
        vector<int> result = sort_alternating(A);
        for (const int x : result) cout << x << " ";
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

std::vector<int> sort_alternating(std::vector<int>& a) {
    using namespace std;
    sort(a.begin(), a.end()); // Sắp xếp tăng dần
    size_t i = a.size() - 1;     // chỉ số lớn nhất
    int j = 0;                // chỉ số nhỏ nhất
    vector<int> result;
    while (j <= i) {
        result.push_back(a[i--]); // chèn số lớn nhất còn lại
        if (j <= i) {
            result.push_back(a[j++]); // chèn số nhỏ nhất còn lại
        }
    }
    return result;
}