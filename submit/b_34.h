#ifndef B_34_H
#define B_34_H
#include <string>

class exit_code_exception : public std::exception {
    int code;
    std::string message;
public:
    explicit exit_code_exception(const int c, std::string m) : code(c), message(std::move(m)) {}
    int getCode() const { return code; }
    const char* what() const noexcept override { return message.c_str(); }
};

int parse_int(const std::string &line);

std::string trim_and_validate_name(const std::string &line, int max_length);

std::string validate_ptit_clazz(const std::string &line);

std::tm parse_date(const std::string &line);

float parse_float(const std::string &line);

std::string print_date(const std::tm &date);

struct Student {
    Student(std::string fullname, std::string clazz, const std::tm &date_of_birth, float gpa_mark);
    friend std::ostream& operator<<(std::ostream& os, const Student& student);
    static int counter;
    std::string code;
    std::string fullname;
    std::string clazz;
    std::tm dateOfBirth;
    float gpaMark;
};

int Student::counter = 0;

#endif //B_34_H
