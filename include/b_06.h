#ifndef B_06_H
#define B_06_H

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

/**
 * Kiểm tra số nguyên tố
 *
 * @param n số nguyên dương đầu vào
 * @return n có phải số nguyên tố hay không
 */
bool is_prime(int n);

#endif //B_06_H
