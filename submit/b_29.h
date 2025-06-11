#ifndef B_29_H
#define B_29_H
#include <string>

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

std::string validate_lower_alphanumeric(const std::string &line);

int sum_of_numbers(const std::string &S);

#endif //B_29_H
