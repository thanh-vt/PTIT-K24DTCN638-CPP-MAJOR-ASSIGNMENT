#include <fstream>
#include <iostream>
#include <string>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT19.h"

// SẮP XẾP CHỮ SỐ
int main() {
    using namespace std;
    const string filename = "K24DTCN638_VuTatThanh_BT19.txt";
    ifstream file(filename); // Mở file để đọc
    if (!file) {
        cerr << "Khong the mo file input " << filename << endl;
        return 1;
    }

    string line;
    if (!getline(file, line)) {
        cerr << "Khong co dong tiep theo" << endl;
        return 2;
    }
    const int total_tests = parse_int(line);
    if (total_tests < 1 || total_tests > 100) {
        cerr << "T phai lon hon hoac bang 1 va nho hon hoac bang 100" << endl;
        return 2;
    }
    for (int i = 0; i < total_tests; i++) {
        if (!getline(file, line)) {
            cerr << "Khong co dong tiep theo" << endl;
            return 2;
        }
        const int n = parse_int(line);
        if (n < 0) return 2;
        if (n < 1) {
            cerr << "n phai lon hon hoac bang 1" << endl;
            return 2;
        }
        if (n > 10000000) {
            cerr << "n phai nho hon hoac bang 10000000" << endl;
            return 2;
        }

        if (!getline(file, line)) {
            cerr << "Khong co dong tiep theo" << endl;
            return 2;
        }
        const vector<long> A = string_to_long_vector(line, n);
        for (int j = 0; j < n; j++) {
            if (A[j] > 10000000000000000) {
                cerr << "A[i] phai nho hon hoac bang 1000000" << endl;
                return 2;
            }
        }
        set<int> digit_set = sort_digits_array(A, n);

        for (const int d: digit_set) {
            cout << d << " ";
        }
        cout << endl;
    }

    file.close();

    return 0;
}

std::set<int> sort_digits_array(const std::vector<long> &A, int n) {
    using namespace std;
    set<int> digits_set;
    for (int i = 0; i < n; ++i) {
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
