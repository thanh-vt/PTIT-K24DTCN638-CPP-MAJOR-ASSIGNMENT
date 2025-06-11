#ifndef B_01_H
#define B_01_H

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

int sum_1_to_n(int n);

/**
 * Tính tổng từ 1 đến n
 *
 * @param n Số nguyên dương đầu vào
 * @return Tổng từ 1 đến n
 */
int sum_1_to_n(int n);

#endif //B_01_H
