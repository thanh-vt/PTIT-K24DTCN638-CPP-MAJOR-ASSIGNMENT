#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT15.h"

// ĐẾM SỐ PHẦN TỬ LẶP LẠI
int main() {
    using namespace std;
    const string filename = "K24DTCN638_VuTatThanh_BT15.txt";
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
        if (n > 1000000) {
            cerr << "n phai nho hon hoac bang 1000000" << endl;
            return 2;
        }

        if (!getline(file, line)) {
            cerr << "Khong co dong tiep theo" << endl;
            return 2;
        }
        const vector<int> A = string_to_int_vector(line, n);
        for (int j = 0; j < n; j++) {
            if (A[j] > 1000000) {
                cerr << "A[i] phai nho hon hoac bang 1000000" << endl;
                return 2;
            }
        }
        const int count = count_array_duplicated_elements(A, n);

        cout << count << endl;
    }

    file.close();

    return 0;
}

int count_array_duplicated_elements(const std::vector<int> &A, const int n) {
    using namespace std;
    unordered_map<int, int> freq;

    for (int i = 0; i < n; i++) {
        freq[A[i]]++;
    }

    int count = 0;
    for (const auto& p : freq) {
        if (p.second >= 2) count += p.second;
    }
    return count;
}
