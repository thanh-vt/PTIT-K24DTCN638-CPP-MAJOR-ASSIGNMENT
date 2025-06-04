#include <iostream>
#include <fstream>
#include <vector>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT08.h"

// LIỆT KÊ SỐ CÓ BA ƯỚC SỐ
int main() {
    using namespace std;
    const string filename = "K24DTCN638_VuTatThanh_BT08.txt";
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

    // Dùng thuật toán sàng nguyên tố Eratosthenes để tìm các số nguyên tố đến 1000 (vì 1000^2 = 1,000,000)
    const vector<int> squares = sieve(1000);
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
        if (n > 1000000) {
            cout << "N phai nho hon hoac bang 1000000" << endl;
            return 2;
        }
        bool first = true;

        for (const int x : squares) {
            if (x > n) break;
            if (!first) cout << " ";
            cout << x;
            first = false;
        }
        cout << endl;
    }
    file.close();

    return 0;
}

std::vector<int> sieve(const int max) {
    using namespace std;
    bool isPrime[max + 1];
    vector<int> squares; // Lưu p^2 với p nguyên tố
    fill(isPrime, isPrime + max + 1, true);
    isPrime[0] = isPrime[1] = false; // Số 0 và số 1 không phải số nguyên tố nên ta đánh dấu false cho hai vị trí này ngay từ đầu
    for (int i = 2; i * i <= max; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= max; j += i) {
                isPrime[j] = false;
            }
        }
    }
    for (int i = 2; i <= max; i++) {
        if (isPrime[i]) {
            squares.push_back(i * i);
        }
    }
    return squares;
}
