#ifndef UTIL_H
#define UTIL_H
#include <string>
#include <vector>
#include <sstream>

char parse_char(const std::string& line);

int parse_int(const std::string& line);

long parse_long(const std::string &line);

std::vector<int> string_to_int_vector(const std::string& s, size_t size);

#endif //UTIL_H
