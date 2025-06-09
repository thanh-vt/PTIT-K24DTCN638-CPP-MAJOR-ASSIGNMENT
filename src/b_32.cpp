#include <iostream>
#include <string>
#include <regex>
#include <set>
#include <unordered_set>
#include "util.h"
#include "b_32.h"

int main() {
    using namespace std;
    cout << "b_32: HỢP VÀ GIAO CỦA HAI DÃY SỐ -2" << endl;
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
    vector<vector<int> > A_inputs(T);
    vector<vector<int> > B_inputs(T);
    for (int i = 0; i < T; i++) {
        cout << "Nhập bộ test " << i + 1 << " - Số n và m:" << endl;
        int n = 0, m = 0;
        do {
            is_valid = false;
            getline(cin, line);
            static regex ws_re(" +");
            // tách chuỗi bởi khoảng trắng, static để tránh compile lại regex nhiều lần khi chạy chương trình
            const sregex_token_iterator iter(line.begin(), line.end(), ws_re, -1);
            const sregex_token_iterator end;
            vector<string> result(iter, end);
            if (result.size() != 2) {
                cerr << "Chuỗi nhập phải có 2 số n, m" << endl;
                continue;
            }
            try {
                n = parse_int(result.at(0));
                if (n < 1) {
                    cerr << "n phải >= 1" << endl;
                    continue;
                }
                if (n > 100000) {
                    cerr << "n phải <= 100000" << endl;
                    continue;
                }
            } catch (const exception &e) {
                cerr << e.what() << endl;
                continue;
            }
            try {
                m = parse_int(result.at(1));
                if (m < 1) {
                    cerr << "m phải >= 1" << endl;
                    continue;
                }
                if (m > 100000) {
                    cerr << "m phải <= 100000" << endl;
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
                    if (value < 1) {
                        return "A[" + to_string(pos) + "] phải >= 1";
                    }
                    if (value > 100000) {
                        return "A[" + to_string(pos) + "] phải <= 100000";
                    }
                    static string oke_msg;
                    return oke_msg;
                };
                const vector<int> A = string_to_int_vector(line, n, validate_func);
                A_inputs[i] = A;
            } catch (const exception &e) {
                cerr << e.what() << endl;
                continue;
            }
            is_valid = true;
        } while (!is_valid);
        cout << "Nhập bộ test " << i + 1 << " - Dãy B[] gồm " << m << " phần tử:" << endl;
        do {
            is_valid = false;
            getline(cin, line);
            try {
                // hàm lambda validate từng phần tử đọc được
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
                const vector<int> B = string_to_int_vector(line, m, validate_func);
                B_inputs[i] = B;
            } catch (const exception &e) {
                cerr << e.what() << endl;
                continue;
            }
            is_valid = true;
        } while (!is_valid);

    }
    cout << "Kết quả:" << endl;
    for (int i = 0; i < T; i++) {
        const vector<int> &A = A_inputs[i];
        const vector<int> &B = B_inputs[i];
        set<int> unionSet;  // Dùng set để loại trùng và tự sắp xếp
        unordered_set<int> Bset;  // Dùng để tra cứu nhanh cho intersection
        set<int> intersectionSet;

        for (int x : A) unionSet.insert(x);
        for (int x : B) {
            unionSet.insert(x);
            Bset.insert(x); // Đưa B vào unordered_set để tìm nhanh
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