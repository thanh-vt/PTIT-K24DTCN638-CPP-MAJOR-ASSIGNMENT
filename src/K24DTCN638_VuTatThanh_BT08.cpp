#include <iostream>
#include <fstream>
#include <vector>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT08.h"


int main() {
    std::string filename = "K24DTCN638_VuTatThanh_BT08.txt";
    std::ifstream file(filename); // Mở file để đọc
    if (!file) {
        std::cerr << "Khong the mo file input " << filename << std::endl;
        return 1;
    }

    std::string line;
    if (!std::getline(file, line)) {
        std::cerr << "Khong co dong tiep theo" << std::endl;
        return 2;
    }
    int total_tests = parse_int(line);
    if (total_tests < 1 || total_tests > 100) {
        std::cerr << "T phai lon hon hoac bang 1 va nho hon hoac bang 100" << std::endl;
        return 2;
    }
    const std::vector<int> squares = sieve();
    for (int i = 0; i < total_tests; i++) {
        if (!std::getline(file, line)) {
            std::cerr << "Khong co dong tiep theo" << std::endl;
            return 2;
        }
        const long n = parse_long(line);
        if (n < 0) return 2;
        if (n < 1) {
            std::cout << "N phai lon hon hoac bang 1" << std::endl;
            return 2;
        }
        if (n > 1000000) {
            std::cout << "N phai nho hon hoac bang 1000000" << std::endl;
            return 2;
        }
        bool first = true;

        for (const int x : squares) {
            if (x > n) break;
            if (!first) std::cout << " ";
            std::cout << x;
            first = false;
        }
        std::cout << "\n";
    }
    file.close();

    return 0;
}

std::vector<int> sieve() {
    // Dùng thuật toán sàng nguyên tố Eratosthenes để tìm các số nguyên tố đến 1000 (vì 1000^2 = 1,000,000)
    constexpr int MAX = 1000;
    bool isPrime[MAX + 1];
    std::vector<int> squares; // Lưu p^2 với p nguyên tố
    std::fill(isPrime, isPrime + MAX + 1, true);
    isPrime[0] = isPrime[1] = false; // Số 0 và số 1 không phải số nguyên tố nên ta đánh dấu false cho hai vị trí này ngay từ đầu
    for (int i = 2; i * i <= MAX; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= MAX; j += i) {
                isPrime[j] = false;
            }
        }
    }
    for (int i = 2; i <= MAX; i++) {
        if (isPrime[i]) {
            squares.push_back(i * i);
        }
    }
    return squares;
}
