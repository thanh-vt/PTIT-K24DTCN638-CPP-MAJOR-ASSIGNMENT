#include <iostream>

int main() {
    const int x = getQuantityInput(std::string("Enter X:"));
    if (x > 999999999) {
        std::cerr << "X length must be less than 10";
        return 1;
    }
    std::cout << (x % 100 == 86) << std::endl;
    return 0;
}
