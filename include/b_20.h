#ifndef B_20_H
#define B_20_H
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

std::string trim_and_validate_name(const std::string &line);

std::tm parse_date(const std::string &line);

float parse_float(const std::string &line);

std::string print_date(const std::tm &date);

struct Candidate {
    Candidate(std::string  fullname, const std::tm& dateOfBirth,
              float subject1Mark, float subject2Mark, float subject3Mark);
    friend std::ostream& operator<<(std::ostream& os, const Candidate& candidate);

    std::string fullname;
    std::tm dateOfBirth;
    float subject1Mark;
    float subject2Mark;
    float subject3Mark;
    float totalMark;
};

#endif //B_20_H
