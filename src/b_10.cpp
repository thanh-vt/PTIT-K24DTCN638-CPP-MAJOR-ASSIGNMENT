#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <sstream>
#include "b_10.h"

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
size_t find_smallest_missing_positive(const std::vector<int>& arr);

int main() {
    using namespace std;
    // cerr << "b_10: SỐ NHỎ NHẤT CHƯA XUẤT HIỆN" << endl;
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
    vector<vector<int> > v_inputs(T);
    for (int i = 0; i < T; i++) {
        // cerr << "Nhập bộ test " << i + 1 << " - Số N:" << endl;
        getline(cin, line);
        int N;
        try {
            N = parse_int(line);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
        if (N < 1) {
            cerr << "N phải >= bang 1" << endl;
            return 2;
        }
        if (N > 1000000) {
            cerr << "N phải <= 1000000" << endl;
            return 2;
        }
        // cerr << "Nhập bộ test " << i + 1 << " - Dãy số A[] gồm " << N << " phần tử:" << endl;
        getline(cin, line);
        vector<int> A;
        try {
            // hàm lambda validate từng phần tử đọc được
            static const function<string(int, int)> validate_func = [](const int pos, const long value) {
                if (value < -1000000000) {
                    return "A[" + to_string(pos) + "] phải >= -1000000000";
                }
                if (value > 1000000000) {
                    return "A[" + to_string(pos) + "] phải <= 1000000000";
                }
                static string oke_msg;
                return oke_msg;
            };
            A = string_to_int_vector(line, N, validate_func);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
        v_inputs[i] = A;
    }
    // cerr << "Kết quả:" << endl;
    for (const vector<int> &A: v_inputs) {
        cout << find_smallest_missing_positive(A) << endl;
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

size_t find_smallest_missing_positive(const std::vector<int>& arr) {
    using namespace std;
    const size_t n = arr.size();
    vector<bool> present(n + 2, false); // đánh dấu số từ 1 đến n+1

    for (const int x : arr) {
        if (x >= 1 && x <= n + 1) {
            present[x] = true;
        }
    }

    for (int i = 1; i <= n + 1; i++) {
        if (!present[i]) return i;
    }
    return n + 1; // trường hợp này ít xảy ra vì đã kiểm tra hết
}
