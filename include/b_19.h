#ifndef B_19_H
#define B_19_H
#include <set>

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

std::vector<long> string_to_long_vector(const std::string &line, int expected_size, const std::function<std::string(int, long)> &validate_func);

std::set<int> sort_digits_array(const std::vector<long>& A);

#endif //B_19_H
