#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT09.h"

// CHÊNH LỆCH NHỎ NHẤT
int main() {
    using namespace std;
    const string filename = "K24DTCN638_VuTatThanh_BT09.txt";
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
        const int min_diff = find_min_diff(A);
        cout << min_diff << endl;
    }
    file.close();

    return 0;
}

int find_min_diff(std::vector<int> A) {
    sort(A.begin(), A.end());
    int min_diff = INT_MAX;
    for (int i = 0; i < A.size() - 1; i++) {
        const int diff = A[i+1] - A[i];
        if (diff < min_diff) {
            min_diff = diff;
        }
    }
    return min_diff;
}
