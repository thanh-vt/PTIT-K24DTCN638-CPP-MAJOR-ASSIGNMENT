#include <iostream>
#include <string>
#include "b_18.h"

int main() {
    using namespace std;
    // cerr << "b_18: LOẠI BỎ NGUYÊN ÂM" << endl;
    string S;
    // cerr << "Nhập chuỗi S:" << endl;
    getline(cin, S);
    if (S.size() > 100) {
        cerr << "S độ dài không quá 100" << endl;
        return 2;
    }
    // cerr << "Kết quả:" << endl;
    cout << remove_vowels(S) << endl;
    return 0;
}

// Function definitions
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
