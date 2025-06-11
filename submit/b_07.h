#ifndef B_07_H
#define B_07_H

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

long parse_long(const std::string &line);

/**
 * In các ước số nguyên tố
 *
 * @param n số nguyên dương đầu vào
 */
void print_factorization(long n);

#endif //B_07_H
