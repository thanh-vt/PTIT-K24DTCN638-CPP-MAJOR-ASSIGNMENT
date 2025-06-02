#include <fstream>
#include <iostream>
#include <string>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT10.h"

// SỐ NHỎ NHẤT CHƯA XUẤT HIỆN
int main() {
    using namespace std;
    const string filename = "K24DTCN638_VuTatThanh_BT10.txt";
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
            cout << "N phai lon hon hoac bang 1" << endl;
            return 2;
        }
        if (n > 1000000) {
            cout << "N phai nho hon hoac bang 1000000" << endl;
            return 2;
        }
        if (!getline(file, line)) {
            cerr << "Khong co dong tiep theo" << endl;
            return 2;
        }
        const vector<int> A = string_to_int_vector(line, n);
        cout << find_smallest_missing_positive(A, n) << endl;
    }
    file.close();

    return 0;
}

int find_smallest_missing_positive(const std::vector<int>& arr, const int n) {
    using namespace std;
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
