#include <iostream>
#include <string>
#include "util.h"
#include "b_26.h"

int main() {
    using namespace std;
    cout << "b_26: BIẾN ĐỔI DÃY SỐ" << endl;
    string line;
    cout << "Nhập số bộ test T:" << endl;
    bool is_valid = false;
    int T = 0;
    do {
        getline(cin, line);
        try {
            T = parse_int(line);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            continue;
        }
        if (T < 1) {
            cerr << "T phải >= 1" << endl;
            continue;
        }
        if (T > 100) {
            cerr << "T phải <= 100" << endl;
            continue;
        }
        is_valid = true;
    } while (!is_valid);
    vector<vector<int> > v_inputs(T);
    for (int i = 0; i < T; i++) {
        int n = 0;
        cout << "Nhập bộ test " << i + 1 << " - Số N:" << endl;
        do {
            is_valid = false;
            getline(cin, line);
            try {
                n = parse_int(line);
                if (n < 1) {
                    cerr << "n phải >= 1" << endl;
                    continue;
                }
                if (n > 1000) {
                    cerr << "n phải <= 1000" << endl;
                    continue;
                }
            } catch (const exception &e) {
                cerr << e.what() << endl;
                continue;
            }
            is_valid = true;
        } while (!is_valid);
        cout << "Nhập bộ test " << i + 1 << " - Dãy A[] gồm " << n << " phần tử:" << endl;
        do {
            is_valid = false;
            getline(cin, line);
            try {
                // hàm lambda validate từng phần tử đọc được
                static const function<string(int, int)> validate_func = [](const int pos, const long value) {
                    if (value < 0) {
                        return "A[" + to_string(pos) + "] phải >= 0";
                    }
                    if (value > 1000) {
                        return "A[" + to_string(pos) + "] phải <= 1000";
                    }
                    static string oke_msg;
                    return oke_msg;
                };
                const vector<int> A = string_to_int_vector(line, n, validate_func);
                v_inputs[i] = A;
            } catch (const exception &e) {
                cerr << e.what() << endl;
                continue;
            }
            is_valid = true;
        } while (!is_valid);
    }
    cout << "Kết quả:" << endl;
    for (int i = 0; i < T; i++) {
        vector<int>& A = v_inputs[i];
        const int merge_count = min_merges_to_make_palindrome(A);
        cout << merge_count << endl;
    }
    return 0;
}

int min_merges_to_make_palindrome(std::vector<int> &arr) {
    const size_t n = arr.size();
    size_t left = 0, right = n - 1;
    int merges = 0;

    while (left < right) {
        if (arr[left] == arr[right]) {
            left++;
            right--;
        } else if (arr[left] < arr[right]) {
            arr[left + 1] += arr[left];
            left++;
            merges++;
        } else {
            arr[right - 1] += arr[right];
            right--;
            merges++;
        }
    }

    return merges;
}
