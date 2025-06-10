#include <iostream>
#include <string>
#include <regex>
#include <set>
#include "util.h"
#include "b_14.h"

int main() {
    using namespace std;
    cerr << "b_14: LIỆT KÊ SỐ KHÁC NHAU" << endl;
    string line;
    cerr << "Nhập số N:" << endl;
    bool is_valid = false;
    int N = 0;
    do {
        is_valid = false;
        getline(cin, line);
        try {
            N = parse_int(line);
            if (N < 1) {
                cerr << "n phải >= 1" << endl;
                continue;
            }
            if (N > 100) {
                cerr << "n phải <= 100" << endl;
                continue;
            }
        } catch (const exception &e) {
            cerr << e.what() << endl;
            continue;
        }
        is_valid = true;
    } while (!is_valid);
    vector<int> A;
    cerr << "Nhập dãy A[] gồm " << N << " phần tử:" << endl;
    do {
        is_valid = false;
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
            continue;
        }
        is_valid = true;
    } while (!is_valid);
    cerr << "Kết quả:" << endl;
    print_unique_element(A);
    return 0;
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
