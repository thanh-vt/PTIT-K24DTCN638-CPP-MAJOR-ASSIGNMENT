#include <fstream>
#include <iosfwd>
#include <iostream>
#include "K24DTCN638_VuTatThanh_BT48.h"

// SỐ KHÁC NHAU TRONG FILE
int main() {
    using namespace std;
    ifstream fin("DATA.in");

    int dem[1000] = {}; // Mảng đếm từ 0 đến 999, khởi tạo 0
    int x;

    while (fin >> x) {
        if (x >= 0 && x < 1000) {
            dem[x]++;
        }
    }

    for (int i = 0; i < 1000; ++i) {
        if (dem[i] > 0) {
            cout << i << " " << dem[i] << endl;
        }
    }

    return 0;
}
