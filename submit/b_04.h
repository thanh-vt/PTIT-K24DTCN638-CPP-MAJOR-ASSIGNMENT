#ifndef B_04_H
#define B_04_H

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

bool has_equal_odd_even_digits(int n);

/**
 * Cân bằng chẵn lẻ
 *
 * @param n Số nguyên dương đầu vào
 * @return trong n số chữ số chẵn có bằng số chữ số lẻ hay không
 */
bool has_equal_odd_even_digits(int n);

#endif //B_04_H
