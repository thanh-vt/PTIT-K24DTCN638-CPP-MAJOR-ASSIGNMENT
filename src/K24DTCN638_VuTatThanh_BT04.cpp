#include <complex>
#include <fstream>
#include <iostream>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT04.h"

// CÂN BẰNG CHẴN LẺ
int main() {
    using namespace std;
    const string filename = "K24DTCN638_VuTatThanh_BT04.txt";
    ifstream file(filename); // Mở file để đọc
    if (!file) {
        cerr << "Khong the mo file input " << filename << endl;
        return 1;
    }

    string line;
    if (!getline(file, line)) {
        // Xử lý dòng đọc được
        cerr << "Khong co dong tiep theo" << endl;
        return 2;
    }
    const int n = parse_int(line);
    if (n <= 1) {
        cerr << "N phai lon hon 1" << endl;
        return 2;
    }
    if (n >= 7) {
        cerr << "N phai nho hon 7" << endl;
        return 2;
    }
    if (n % 2 == 0) {
        const int start = static_cast<int>(pow(10, n - 1));
        const int end = static_cast<int>(pow(10, n)) - 1;
        int count = 0;
        for (int num = start; num <= end; ++num) {
            if (has_equal_odd_even_digits(num)) {
                count ++;
                cout << num << " ";
                if (count % 10 == 0) {
                    cout << endl;
                }
            }
        }
        cout << endl;
    } else {
        cerr << "N phai la so chan" << endl;
        return 2;
    }

    file.close();

    return 0;
}

bool has_equal_odd_even_digits(int n) {
    int oddCount = 0, evenCount = 0;

    while (n > 0) {
        int digit = n % 10;
        if (digit % 2 == 0)
            evenCount++;
        else
            oddCount++;
        n /= 10;
    }

    return oddCount == evenCount;
}