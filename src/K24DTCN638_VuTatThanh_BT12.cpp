#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT12.h"

// BIẾN ĐỔI NHỊ PHÂN
int main() {
    using namespace std;
    const string filename = "K24DTCN638_VuTatThanh_BT12.txt";
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
        regex ws_re(" +"); // ttách chuỗi bởi khoảng trắng
        sregex_token_iterator iter(line.begin(), line.end(), ws_re, -1);
        sregex_token_iterator end;
        vector<string> result(iter, end);
        if (result.size() != 2) {
            cerr << "Dong phai co 2 so n, m" << endl;
            return 2;
        }
        int n = parse_int(result[0]);
        if (n < 0) return 2;
        if (n < 1) {
            cerr << "n phai lon hon hoac bang 1" << endl;
            return 2;
        }
        if (n > 100) {
            cerr << "n phai nho hon hoac bang 100" << endl;
            return 2;
        }
        const int m = parse_int(result[1]);
        if (m < 0) return 2;
        if (m < 1) {
            cerr << "m phai lon hon hoac bang 1" << endl;
            return 2;
        }
        if (m > 100) {
            cerr << "m phai nho hon hoac bang 100" << endl;
            return 2;
        }

        vector<vector<int> > A(n, vector<int>(m));
        for (int j = 0; j < n; ++j) {
            if (!getline(file, line)) {
                cerr << "Khong co dong tiep theo" << endl;
                return 2;
            }
            const vector<int> arr = string_to_int_vector(line, m);
            A[j] = arr;
        }
        print_modified_matrix(A, n, m);
    }
    file.close();

    return 0;
}

void print_modified_matrix(std::vector<std::vector<int> > A, const int n, const int m) {
    using namespace std;
    vector<bool> row_flag(n, false);
    vector<bool> col_flag(m, false);

    // Tìm hàng và cột có phần tử = 1
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (A[i][j] == 1) {
                row_flag[i] = true;
                col_flag[j] = true;
            }
        }
    }

    // Biến đổi ma trận theo row_flag và col_flag
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (row_flag[i] || col_flag[j]) {
                A[i][j] = 1;
            }
        }
    }

    // In ra kết quả theo yêu cầu: mỗi test trên 1 dòng, in nối các phần tử
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << A[i][j];
            if (i != n - 1 || j != m - 1) cout << " ";
        }
        cout << endl;
    }
}
