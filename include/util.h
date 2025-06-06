#ifndef UTIL_H
#define UTIL_H
#include <ctime>
#include <string>
#include <utility>
#include <vector>

class ExitCodeException : public std::exception {
    int code;
    std::string message;
public:
    explicit ExitCodeException(const int c, std::string m) : code(c), message(std::move(m)) {}
    int getCode() const { return code; }
    const char* what() const noexcept override {
        return message.c_str();
    }
};

enum Gender {
    MALE,
    FEMALE
  };

void validation_termination();

Gender parse_gender(const std::string &genderStr);

std::string print_gender(Gender gender);

std::string trim(const std::string &str);

std::string trim_and_validate_name(const std::string &input);

std::string trim_and_validate_name(const std::string& input, int max_length);

std::string normalize_and_validate_name(const std::string& input);

std::string normalize_and_validate_name(const std::string& input, int max_length);

bool is_leap_year(int year);

std::tm parse_date(const std::string &dateStr, const std::string &format);

std::tm parse_date(const std::string &dateStr);

std::string print_date(const std::tm &date, const std::string &format);

std::string print_date(const std::tm &date);

char parse_char(const std::string &line);

int parse_int(const std::string &line);

long parse_long(const std::string &line);

float parse_float(const std::string &line);

double parse_double(const std::string &line);

std::vector<int> string_to_int_vector(const std::string &s, size_t size);

std::vector<long> string_to_long_vector(const std::string &s, size_t size);

std::string validate_ptit_clazz(const std::string &clazz);

std::string validate_tax_code(const std::string &taxCode);

#endif //UTIL_H
