#include <fstream>
#include <iostream>
#include <string>
#include "K24DTCN638_VuTatThanh_BT18.h"

// LOẠI BỎ NGUYÊN ÂM
int main() {
    const std::string filename = "K24DTCN638_VuTatThanh_BT18.txt";
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
    if (line.size() > 100) {
        std::cerr << "S phai co do dai nho hon hoac bang 100" << std::endl;
        return 2;
    }

    std::cout << remove_vowels(line) << std::endl;
    file.close();

    return 0;
}

bool isVowel(char c) {
    c = tolower(c);
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y';
}

std::string remove_vowels(const std::string &S) {
    std::string result;
    for (char c : S) {
        if (!isVowel(c)) {
            result += '.';
            result += tolower(c);
        }
    }
    return result;
}
