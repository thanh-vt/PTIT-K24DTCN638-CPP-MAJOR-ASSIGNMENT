#ifndef B_31_H
#define B_31_H

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

std::vector<int> find_union_array(const std::vector<int>& A, const std::vector<int>& B);

// Hàm tìm giao hai mảng đã sắp xếp
std::vector<int> find_intersection_array(const std::vector<int>& A, const std::vector<int>& B);

#endif //B_31_H
