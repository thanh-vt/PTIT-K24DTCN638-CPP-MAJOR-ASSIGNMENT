#include <iostream>
#include <string>
#include <regex>
#include <set>
#include <sstream>
#include <functional>
#include "b_14.h"

int main() {
    using namespace std;
    // cerr << "b_14: LIỆT KÊ SỐ KHÁC NHAU" << endl;
    string line;
    // cerr << "Nhập số N:" << endl;
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
    vector<int> A;
    // cerr << "Nhập dãy A[] gồm " << N << " phần tử:" << endl;
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
        A = string_to_int_vector(line, N, validate_func);
    } catch (const exception &e) {
        cerr << e.what() << endl;
        return 2;
    }
    // cerr << "Kết quả:" << endl;
    print_unique_element(A);
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

void print_unique_element(const std::vector<int> &A) {
    using namespace std;
    set<int> unique_numbers;
    for (const int x: A) {
        unique_numbers.insert(x);
    }

    bool first = true;
    for (const int num: unique_numbers) {
        if (!first) cout << " ";
        cout << num;
        first = false;
    }
    cout << endl;
}
