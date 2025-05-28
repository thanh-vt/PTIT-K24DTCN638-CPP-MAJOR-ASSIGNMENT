#include <iostream>

char convert_char();

int main() {
    std::ifstream file("K24DTCN638_VuTatThanh_BT02.txt"); // Mở file để đọc
    if (!file) {
        std::cerr << "Khong the mo file input K24DTCN638_VuTatThanh_BT01.txt\n";
        return 1;
    }
    return 0;
}

char convert_char() {
    char c;
    std::cin >> c;
    if (std::islower(c)) {
        char upper_char = std::toupper(c);
        std::cout << "Uppercase equivalent: " << upper_char << std::endl;
    } else if (std::isupper(c)) {
        char lower_char = std::tolower(c);
        std::cout << "Lower case equivalent: " << lower_char << std::endl;
    } else {
        std::cerr << "Invalid character." << std::endl;
    }
    return c;
}