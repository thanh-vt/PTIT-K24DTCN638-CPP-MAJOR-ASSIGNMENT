#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT33.h"

// SẮP XẾP XEN KẼ - 2
int main() {
    using namespace std;
    const string filename = "K24DTCN638_VuTatThanh_BT33.txt";
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
        if (n > 100000) {
            cerr << "n phai nho hon hoac bang 100000" << endl;
            return 2;
        }
        if (!getline(file, line)) {
            cerr << "Khong co dong tiep theo" << endl;
            return 2;
        }
        vector<int> A = string_to_int_vector(line, n);
        for (int e : A) {
            if (e > 1000) {
                cerr << "Phan tu cua A phai nho hon hoac bang 1000" << endl;
                return 2;
            }
        }
        vector<int> result = sort_alternating(A);
        for (int x : result) cout << x << " ";
        cout << endl;
    }
    file.close();

    return 0;
}

std::vector<int> sort_alternating(std::vector<int>& a) {
    using namespace std;
    sort(a.begin(), a.end()); // Sắp xếp tăng dần
    unsigned long i = a.size() - 1;     // chỉ số lớn nhất
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