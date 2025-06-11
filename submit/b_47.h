#ifndef B_47_H
#define B_47_H
#include <string>

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

bool is_binary(const std::string& str);

int max_deleted_length(const std::string& s);

#endif //B_47_H
