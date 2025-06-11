#ifndef B_30_H
#define B_30_H

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

std::string validate_upper_alphanumeric(const std::string &line);

std::string separate_alphabet_and_numeric(const std::string &S);

#endif //B_30_H
