#ifndef B_16_H
#define B_16_H
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

std::string find_min(int m, int s);

std::string find_max(int m, int s);

#endif //B_16_H
