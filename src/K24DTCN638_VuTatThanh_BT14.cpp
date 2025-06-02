#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include <set>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT14.h"

// LIỆT KÊ SỐ KHÁC NHAU
int main() {
    using namespace std;
    const string filename = "K24DTCN638_VuTatThanh_BT14.txt";
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
    const int n = parse_int(line);
    if (n < 0) return 2;
    if (n < 1) {
        cerr << "n phai lon hon hoac bang 1" << endl;
        return 2;
    }
    if (n > 100) {
        cerr << "n phai nho hon hoac bang 100" << endl;
        return 2;
    }

    if (!getline(file, line)) {
        cerr << "Khong co dong tiep theo" << endl;
        return 2;
    }
    const vector<int> A = string_to_int_vector(line, n);
    print_unique_element(A);

    file.close();

    return 0;
}

void print_unique_element(const std::vector<int> &A) {
    using namespace std;
    set<int> unique_numbers;
    for (const int x: A) {
        unique_numbers.insert(x);
    }

    bool first = true;
    for (const int num: unique_numbers) {
        if (!first) cout << " ";
        cout << num;
        first = false;
    }
    cout << endl;
}
