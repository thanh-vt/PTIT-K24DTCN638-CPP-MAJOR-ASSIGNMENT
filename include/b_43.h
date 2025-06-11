#ifndef B_43_H
#define B_43_H

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

std::string trim(const std::string &str);

std::string trim_and_validate_name(const std::string &input, int max_length);

std::string validate_email(const std::string& email);

struct Student {
    Student(std::string code, std::string fullname, std::string clazz, std::string email);
    friend std::ostream& operator<<(std::ostream& os, const Student& student);
    bool operator <(const Student &other) const;
    std::string code;
    std::string fullname;
    std::string clazz;
    std::string email;
};

#endif //B_43_H
