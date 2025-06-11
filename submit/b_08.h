#ifndef B_08_H
#define B_08_H

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
 * Sàng các số nguyên tố trong khoảng từ 1 đến max
 *
 * @param max số nguyên dương đầu vào
 * @return tập hợp các số nguyên tố đã sàng được
 */
std::vector<int> sieve(int max);

#endif //B_08_H
