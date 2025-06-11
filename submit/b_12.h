#ifndef B_12_H
#define B_12_H

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

void print_modified_matrix(std::vector<std::vector<int>> A, int n, int m);

#endif //B_12_H
