#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT13.h"

// BIÊN CỦA MA TRẬN
int main() {
    using namespace std;
    const string filename = "K24DTCN638_VuTatThanh_BT13.txt";
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
            cerr << "n phai lon hon hoac bang 1" << endl;
            return 2;
        }
        if (n > 100) {
            cerr << "n phai nho hon hoac bang 100" << endl;
            return 2;
        }

        vector<vector<int> > A(n, vector<int>(n));
        if (!getline(file, line)) {
            cerr << "Khong co dong tiep theo" << endl;
            return 2;
        }
        const vector<int> arr = string_to_int_vector(line, n * n);
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                const int e = arr[j * n + k];
                if (e > 150) {
                    cerr << "Phan tu phai nho hon hoac bang 150" << endl;
                    return 2;
                }
                A[j][k] = e;
            }
        }
        print_matrix_borders(A, n);
    }
    file.close();

    return 0;
}

void print_matrix_borders(const std::vector<std::vector<int> > &A, const int n) {
    using namespace std;
    // In dòng đầu đầy đủ
    for (int j = 0; j < n; j++) {
        cout << A[0][j];
        if (j < n - 1) cout << " ";
    }
    cout << endl;

    // In các dòng giữa: phần tử đầu, 4 dấu cách, phần tử cuối
    for (int i = 1; i < n - 1; i++) {
        cout << A[i][0];
        cout << "    ";  // 4 dấu cách
        cout << A[i][n - 1] << endl;
    }

    // In dòng cuối đầy đủ
    for (int j = 0; j < n; j++) {
        cout << A[n - 1][j];
        if (j < n - 1) cout << " ";
    }
    cout << endl;
}
