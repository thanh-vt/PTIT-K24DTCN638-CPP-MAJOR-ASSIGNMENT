#include <fstream>
#include <iostream>
#include <string>
#include "K24DTCN638_VuTatThanh_BT18.h"

// LOẠI BỎ NGUYÊN ÂM
int main() {
    using namespace std;
    const string filename = "K24DTCN638_VuTatThanh_BT18.txt";
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
    if (line.size() > 100) {
        cerr << "S phai co do dai nho hon hoac bang 100" << endl;
        return 2;
    }

    cout << remove_vowels(line) << endl;
    file.close();

    return 0;
}

bool is_vowel(char c) {
    c = tolower(c);
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y';
}

std::string remove_vowels(const std::string &S) {
    using namespace std;
    string result;
    for (const char c : S) {
        if (!is_vowel(c)) {
            result += '.';
            result += tolower(c);
        }
    }
    return result;
}
