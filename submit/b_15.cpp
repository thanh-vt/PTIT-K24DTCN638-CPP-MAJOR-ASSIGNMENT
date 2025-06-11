#include <string>
#include <iostream>
#include <unordered_map>
#include <sstream>
#include <functional>
#include <vector>
#include "b_15.h"

int main() {
    using namespace std;
    // cerr << "b_15: ĐẾM SỐ PHẦN TỬ LẶP LẠI" << endl;
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
    vector<vector<int> > v_inputs(T);
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
            if (N > 1000000) {
                cerr << "n phải <= 1000000" << endl;
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
            static const function<string(int, int)> validate_func = [](const int pos, const int value) {
                if (value < 0) {
                    return "A[" + to_string(pos) + "] phải >= 0";
                }
                if (value > 1000000) {
                    return "A[" + to_string(pos) + "] phải <= 1000000";
                }
                static string oke_msg;
                return oke_msg;
            };
            v_inputs[i] = string_to_int_vector(line, N, validate_func);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
    }
    // cerr << "Kết quả:" << endl;
    for (int i = 0; i < T; i++) {
        const vector<int>& A = v_inputs[i];
        const int count = count_array_duplicated_elements(A);
        cout << count << endl;
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

int count_array_duplicated_elements(const std::vector<int> &A) {
    using namespace std;
    const size_t n = A.size();
    unordered_map<int, int> freq;

    for (size_t i = 0; i < n; i++) {
        freq[A[i]]++;
    }

    int count = 0;
    for (const pair<const int, int>& p : freq) {
        if (p.second >= 2) count += p.second;
    }
    return count;
}
