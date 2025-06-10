#ifndef B_22_H
#define B_22_H

class Fraction {
public:
    Fraction(int numerator, int denominator);
    friend std::ostream& operator<<(std::ostream& os, const Fraction& ps);
private:
    int numerator;
    int denominator;

    static int gcd(int a, int b);

    void reduce();
};

#endif //B_22_H
