#include <cmath>
#include <iostream>


bool Ex6::is_prime(const int n) {
    if (n < 2)
        return false;
    if (n == 2)
        return true;
    if (n % 2 == 0)
        return false;
    int limit = std::sqrt(n);
    for (int i = 3; i <= limit; i += 2) {
        if (n % i == 0)
            return false;
    }
    return true;
}

int main() {
    int a = getQuantityInput(std::string("Enter a:"));
    int b = getQuantityInput(std::string("Enter b:"));
    if (a > 1000000 || b > 1000000) {
        std::cerr << a << " " << b << " is greater than 1000000.\n";
        return;
    }
    if (a > b) {
        std::swap(a, b); // Ensure a <= b
    }
    std::cout << "Prime numbers between " << a << " and " << b << ":" << std::endl;
    for (int i = a; i <= b; ++i) {
        if (is_prime(i)) {
            std::cout << i << " ";
        }
    }
    std::cout << std::endl;
    return 0;
}
