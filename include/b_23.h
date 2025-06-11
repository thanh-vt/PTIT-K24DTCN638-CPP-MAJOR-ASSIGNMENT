#ifndef B_23_H
#define B_23_H

class exit_code_exception : public std::exception {
    int code;
    std::string message;
public:
    explicit exit_code_exception(const int c, std::string m) : code(c), message(std::move(m)) {}
    int getCode() const { return code; }
    const char* what() const noexcept override {
        return message.c_str();
    }
};

int parse_int(const std::string &line);

class Fraction {
public:
    Fraction(const std::string &numeratorStr, const std::string &denominatorStr);
    Fraction(int numerator, int denominator);
    friend std::ostream& operator<<(std::ostream& os, const Fraction& ps);
    Fraction operator+(const Fraction& other) const;
private:
    int numerator{};
    int denominator{};

    static int gcd(int a, int b);

    void reduce();
};

#endif //B_23_H
