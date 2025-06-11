#include <iostream>
#include <string>
#include <regex>
#include <set>
#include <unordered_set>
#include <sstream>
#include <functional>
#include "b_32.h"

int main() {
    using namespace std;
    // cerr << "b_32: HỢP VÀ GIAO CỦA HAI DÃY SỐ -2" << endl;
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
    vector<vector<int> > B_inputs(T);
    for (int i = 0; i < T; i++) {
        // cerr << "Nhập bộ test " << i + 1 << " - Số n và m:" << endl;
        getline(cin, line);
        static regex ws_re(" +");
        const sregex_token_iterator iter(line.begin(), line.end(), ws_re, -1);
        const sregex_token_iterator end;
        vector<string> result(iter, end);
        if (result.size() != 2) {
            cerr << "Chuỗi nhập phải có 2 số n, m" << endl;
            return 2;
        }
        int n, m;
        try {
            n = parse_int(result.at(0));
            if (n < 1) {
                cerr << "n phải >= 1" << endl;
                return 2;
            }
            if (n > 100000) {
                cerr << "n phải <= 100000" << endl;
                return 2;
            }
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
        try {
            m = parse_int(result.at(1));
            if (m < 1) {
                cerr << "m phải >= 1" << endl;
                return 2;
            }
            if (m > 100000) {
                cerr << "m phải <= 100000" << endl;
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
                    return "A[" + to_string(pos) + "] phải >= 1";
                }
                if (value > 100000) {
                    return "A[" + to_string(pos) + "] phải <= 100000";
                }
                static string oke_msg;
                return oke_msg;
            };
            A_inputs[i] = string_to_int_vector(line, n, validate_func);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
        // cerr << "Nhập bộ test " << i + 1 << " - Dãy B[] gồm " << m << " phần tử:" << endl;
        getline(cin, line);
        try {
            static const function<string(int, int)> validate_func = [](const int pos, const long value) {
                if (value < 1) {
                    return "B[" + to_string(pos) + "] phải >= 1";
                }
                if (value > 100000) {
                    return "B[" + to_string(pos) + "] phải <= 100000";
                }
                static string oke_msg;
                return oke_msg;
            };
            B_inputs[i] = string_to_int_vector(line, m, validate_func);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
    }
    // cerr << "Kết quả:" << endl;
    for (int i = 0; i < T; i++) {
        const vector<int> &A = A_inputs[i];
        const vector<int> &B = B_inputs[i];
        set<int> unionSet;
        unordered_set<int> Bset;
        set<int> intersectionSet;
        for (int x : A) unionSet.insert(x);
        for (int x : B) {
            unionSet.insert(x);
            Bset.insert(x);
        }
        for (int x : A) {
            if (Bset.count(x)) {
                intersectionSet.insert(x);
            }
        }
        for (int x : unionSet) cout << x << " ";
        cout << endl;
        for (int x : intersectionSet) cout << x << " ";
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

// Hàm tìm hợp hai mảng đã sắp xếp
std::vector<int> find_union_array(const std::vector<int>& A, const std::vector<int>& B) {
    using namespace std;
    vector<int> result;
    int i = 0, j = 0;
    const size_t n = A.size();
    const size_t m = B.size();

    while (i < n && j < m) {
        if (A[i] < B[j]) {
            result.push_back(A[i++]);
        } else if (A[i] > B[j]) {
            result.push_back(B[j++]);
        } else {
            result.push_back(A[i]);
            ++i; ++j;
        }
    }

    while (i < n) result.push_back(A[i++]);
    while (j < m) result.push_back(B[j++]);

    return result;
}

// Hàm tìm giao hai mảng đã sắp xếp
std::vector<int> find_intersection_array(const std::vector<int>& A, const std::vector<int>& B) {
    using namespace std;
    vector<int> result;
    int i = 0, j = 0;
    const size_t n = A.size();
    const size_t m = B.size();

    while (i < n && j < m) {
        if (A[i] < B[j]) {
            ++i;
        } else if (A[i] > B[j]) {
            ++j;
        } else {
            result.push_back(A[i]);
            ++i; ++j;
        }
    }

    return result;
}