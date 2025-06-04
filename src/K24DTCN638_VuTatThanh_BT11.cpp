#include <fstream>
#include <iostream>
#include <string>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT11.h"

#include <regex>

// QUAY VÒNG DÃY SỐ 1
int main() {
    using namespace std;
    const string filename = "K24DTCN638_VuTatThanh_BT11.txt";
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
        regex ws_re(" +");  // ttách chuỗi bởi khoảng trắng
        sregex_token_iterator iter(line.begin(), line.end(), ws_re, -1);
        sregex_token_iterator end;
        vector<string> result(iter, end);
        if (result.size() != 2) {
            cerr << "Dong phai co 2 so n, d" << endl;
            return 2;
        }
        int n = parse_int(result[0]);
        if (n < 1) {
            cerr << "n phai lon hon hoac bang 1" << endl;
            return 2;
        }
        if (n > 1000000) {
            cerr << "n phai nho hon hoac bang 1000000" << endl;
            return 2;
        }
        const int d = parse_int(result[1]);
        if (d < 0) return 2;
        if (d < 1) {
            cerr << "d phai lon hon hoac bang 1" << endl;
            return 2;
        }
        if (d > 1000000) {
            cerr << "d phai nho hon hoac bang 1000000" << endl;
            return 2;
        }
        if (d >= n) {
            cerr << "d phai nho hon hoac bang n" << endl;
            return 2;
        }
        if (!getline(file, line)) {
            cerr << "Khong co dong tiep theo" << endl;
            return 2;
        }
        const vector<int> A = string_to_int_vector(line, n);
        print_rotated_vector(A, n, d);
    }
    file.close();

    return 0;
}

void print_rotated_vector(const std::vector<int>& A, const int n, const int d) {
    using namespace std;
    vector<int> rotated(n);
    // Copy từ A[d..n-1]
    for (int i = 0; i < n - d; i++) {
        rotated[i] = A[i + d];
    }
    // Copy từ A[0..d-1]
    for (int i = n - d; i < n; i++) {
        rotated[i] = A[i - (n - d)];
    }

    for (int i = 0; i < n; i++) {
        cout << rotated[i];
        if (i < n - 1) cout << " ";
    }
    cout << endl;
}
