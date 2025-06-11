#ifndef B_37_H
#define B_37_H
#include <string>

enum Gender {
    MALE,
    FEMALE
  };

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

std::string trim_and_validate_name(const std::string &line, int max_length);

Gender parse_gender(const std::string &line);

std::tm parse_date(const std::string &dateStr);

std::string validate_tax_code(const std::string &tax_code);

std::string print_gender(Gender gender);

std::string print_date(const std::tm &date);

struct Employee {
    Employee(std::string fullname, Gender gender, const std::tm &date_of_birth, std::string address,
        std::string tax_code, const std::tm &contract_sign_date);
    friend std::ostream& operator<<(std::ostream& os, const Employee& employee);
    static int counter;
    std::string code;
    std::string fullname;
    Gender gender;
    std::tm dateOfBirth;
    std::string address;
    std::string taxCode;
    std::tm contractSignDate;
    // override toán tử so sánh để sắp xếp theo điểm GPA
    bool operator <(const Employee &other) const;

};


int Employee::counter = 0;

#endif //B_37_H
