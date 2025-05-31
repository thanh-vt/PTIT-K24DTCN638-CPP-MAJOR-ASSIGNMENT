#ifndef UTIL_H
#define UTIL_H
#include <ctime>
#include <string>
#include <vector>
#include <sstream>

std::string trim(const std::string &str);

std::string normalize_and_validate_name(const std::string &input);

bool is_leap_year(int year);

std::tm parse_date(const std::string &dateStr, const std::string &format);

std::tm parse_date(const std::string &dateStr);

char parse_char(const std::string &line);

int parse_int(const std::string &line);

long parse_long(const std::string &line);

double parse_double(const std::string &line);

std::vector<int> string_to_int_vector(const std::string &s, size_t size);

std::vector<long> string_to_long_vector(const std::string &s, size_t size);

#endif //UTIL_H
