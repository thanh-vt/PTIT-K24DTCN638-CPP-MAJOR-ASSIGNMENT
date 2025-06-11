#ifndef B_11_H
#define B_11_H

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

std::vector<int> string_to_int_vector(const std::string &s, size_t size, const std::function<std::string(int, int)>& validate_func);

std::vector<int> rotate_vector(const std::vector<int>& A, int d);

#endif //B_11_H
