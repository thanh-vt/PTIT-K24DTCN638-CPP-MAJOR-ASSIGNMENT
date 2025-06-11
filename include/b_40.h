#ifndef B_40_H
#define B_40_H

class exit_code_exception : public std::exception {
    int code;
    std::string message;
public:
    explicit exit_code_exception(const int c, std::string m) : code(c), message(std::move(m)) {}
    int getCode() const { return code; }
    const char* what() const noexcept override { return message.c_str(); }
};

int parse_int(const std::string &line);

std::string trim_and_validate_name(const std::string &input, int max_length);

std::tm parse_date(const std::string &line);

struct Person {
    Person(std::string name, const std::tm &date_of_birth);
    friend std::ostream & operator<<(std::ostream &os, const Person &person);
    bool operator<(const Person &other) const;
    std::string name;
    std::tm dateOfBirth;
};

#endif //B_40_H
