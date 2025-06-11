#include <fstream>
#include <iosfwd>
#include <iostream>
#include "b_48.h"

int main() {
    using namespace std;
    // cerr << "b_48: SỐ KHÁC NHAU TRONG FILE" << endl;
    ifstream fin("DATA.in");
    if (!fin) {
        cerr << "Không thể mở file DATA.in " << endl;
        return 1;
    }
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
