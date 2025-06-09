#include <iostream>
#include <string>
#include "b_18.h"

int main() {
    using namespace std;
    cout << "b_18: LOẠI BỎ NGUYÊN ÂM" << endl;
    string S;
    cout << "Nhập chuỗi S:" << endl;
    bool is_valid = false;
    do {
        is_valid = false;
        getline(cin, S);
        if (S.size() > 100) {
            cerr << "S độ dài không quá 100" << endl;
            continue;
        }
        is_valid = true;
    } while (!is_valid);
    cout << "Kết quả:" << endl;
    cout << remove_vowels(S) << endl;
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
