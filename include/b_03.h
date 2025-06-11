#ifndef B_03_H
#define B_03_H

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

int sum_products(int n);

/**
 * Tính tổng giai thừa
 *
 * @param n Số nguyên dương đầu vào
 * @return Tổng các giai thừa từ 1 đến N
 */
int sum_products(int n);

#endif //B_03_H
