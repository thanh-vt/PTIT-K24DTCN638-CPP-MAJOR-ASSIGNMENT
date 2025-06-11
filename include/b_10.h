#ifndef B_10_H
#define B_10_H

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

std::vector<int> string_to_int_vector(const std::string &s, const size_t size, const std::function<std::string(int, int)>& validate_func);

size_t find_smallest_missing_positive(const std::vector<int>& arr);

#endif //B_10_H
