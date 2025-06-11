#ifndef B_21_H
#define B_21_H
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

std::string trim_and_validate_name(const std::string &line);

Gender parse_gender(const std::string &line);

std::tm parse_date(const std::string &line);

std::string validate_tax_code(const std::string &line);

std::string print_gender(Gender gender);

std::string print_date(const std::tm &date);

struct Staff {
    Staff(std::string fullname, Gender gender, const std::tm &date_of_birth, std::string address,
             std::string tax_code, const std::tm &contract_sign_date);

    friend std::ostream &operator<<(std::ostream &os, const Staff &staff);

    std::string code;
    std::string fullname;
    Gender gender; // 1 nam 2 nu
    std::tm dateOfBirth;
    std::string address;
    std::string taxCode;
    std::tm contractSignDate;
};

#endif //B_21_H
