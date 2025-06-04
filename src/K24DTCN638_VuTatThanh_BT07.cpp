#include <iostream>
#include <fstream>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT07.h"

// ƯỚC SỐ NGUYÊN TỐ
int main() {
    using namespace std;
    string filename = "K24DTCN638_VuTatThanh_BT07.txt";
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
        const long n = parse_long(line);
        if (n < 1) {
            cout << "N phai lon hon hoac bang 1" << endl;
            return 2;
        }
        if (n > 10000000000) {
            cout << "N phai nho hon hoac bang 10000000000" << endl;
            return 2;
        }
        print_factorization(n);
    }

    file.close();

    return 0;
}

void print_factorization(long n) {
    using namespace std;
    while (n % 2 == 0) {
        cout << 2 << " ";
        n /= 2;
    }

    for (long i = 3; i * i <= n; i += 2) {
        while (n % i == 0) {
            cout << i << " ";
            n /= i;
        }
    }

    if (n > 2) {
        cout << n;
    }

    cout << endl;
}
