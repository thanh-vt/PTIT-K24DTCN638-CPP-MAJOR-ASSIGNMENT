#ifndef B_27_H
#define B_27_H
#include <vector>

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

std::vector<int> string_to_int_vector(const std::string &line, int expected_size, const std::function<std::string(int, long)> &validate_func);

std::vector<std::vector<int>> print_convolution_matrix(const std::vector<std::vector<int>> &A, const std::vector<std::vector<int>> &B);

#endif //B_27_H
