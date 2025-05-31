#ifndef K24DTCN638_VUTATTHANH_BT23_H
#define K24DTCN638_VUTATTHANH_BT23_H

class Fraction {
public:
    Fraction(const std::string &numeratorStr, const std::string &denominatorStr);
    Fraction(int numerator, int denominator);
    friend std::ostream& operator<<(std::ostream& os, const Fraction& ps);
    Fraction operator+(const Fraction& other) const;
private:
    int numerator{};
    int denominator{};

    int gcd(int a, int b);

    void reduce();
};

#endif //K24DTCN638_VUTATTHANH_BT23_H
