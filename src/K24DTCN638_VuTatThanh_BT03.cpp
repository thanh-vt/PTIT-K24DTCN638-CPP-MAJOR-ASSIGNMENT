#include <fstream>
#include <iostream>

#include "util.h"
#include "K24DTCN638_VuTatThanh_BT03.h"

// TÍNH TỔNG GIAI THỪA
int main() {
    using namespace std;
    const string filename = "K24DTCN638_VuTatThanh_BT03.txt";
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
    if (n < 0) return 2;
    if (n > 20) {
        cerr << "N phai nho hon 20" << endl;
        return 2;
    }
    cout << sum_products(n) << endl;
    file.close();

    return 0;
}

int sum_products(const int n) {
    int sum = 0;
    int product = 1;
    for (int i = 1; i <= n; i++) {
        product *= i;
        sum += product;
    }
    return sum;
}
