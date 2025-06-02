#include <fstream>
#include <iostream>
#include <string>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT17.h"

// ĐẦU CUỐI GIỐNG NHAU
int main() {
    using namespace std;
    const string filename = "K24DTCN638_VuTatThanh_BT17.txt";
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
        const int count = count_substring_begin_end_equals(line);
        cout << count << endl;
    }

    file.close();

    return 0;
}

int count_substring_begin_end_equals(const std::string &S) {
    using namespace std;
    vector<int> freq(26, 0);
    for (const char c : S) {
        freq[c - 'a']++;
    }

    int result = 0;
    for (const int f : freq) {
        if (f > 0) {
            result += static_cast<int>(f) * (f + 1) / 2;
        }
    }
    return result;
}
