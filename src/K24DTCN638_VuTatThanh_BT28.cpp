#include <string>
#include <fstream>
#include <iostream>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT28.h"

// ĐỔI CHỖ CHỮ SỐ
int main() {
    using namespace std;
    const string filename = "K24DTCN638_VuTatThanh_BT28.txt";
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
            cerr << "n phai nho lon hon hoac bang 1" << endl;
            return 2;
        }
        if (n > 100000) {
            cerr << "n phai nho hon hoac bang 100000" << endl;
            return 2;
        }
        const int swap_count = find_largest_smaller_number(n);
        cout << swap_count << endl;
    }
    file.close();

    return 0;
}

int find_largest_smaller_number(const int n) {
    using namespace std;
    string N = to_string(n);
    const int len = N.length();
    int swap1 = -1, swap2 = -1;

    // Tìm vị trí có thể hoán đổi
    for (int i = len - 2; i >= 0; i--) {
        for (int j = len - 1; j > i; j--) {
            if (N[j] < N[i]) {
                // Tìm vị trí hoán đổi
                if (swap1 == -1 || N[j] > N[swap2]) {
                    swap1 = i;
                    swap2 = j;
                }
            }
        }
    }

    if (swap1 == -1) return -1; // Không thể hoán đổi

    // Hoán đổi các chữ số tại swap1 và swap2
    swap(N[swap1], N[swap2]);
    return parse_int(N);
}
