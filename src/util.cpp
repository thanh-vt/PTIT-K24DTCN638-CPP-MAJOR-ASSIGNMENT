#include "util.h"

#include <iomanip>
#include <iostream>
#include <regex>

std::string trim(const std::string& str) {
    const size_t first = str.find_first_not_of(" \t\n\r\f\v");
    if (first == std::string::npos)
        return ""; // Chuỗi toàn khoảng trắng
    const size_t last = str.find_last_not_of(" \t\n\r\f\v");
    return str.substr(first, (last - first + 1));
}

std::string normalize_and_validate_name(const std::string& input) {
    std::string trimmed = trim(input);
    std::string result;
    int letterCount = 0;
    bool inSpace = false;

    for (const char c : trimmed) {
        if (isalpha(c)) {
            result += c;
            letterCount++;
            inSpace = false;
        } else if (isspace(c)) {
            if (!inSpace) {
                result += ' ';
                inSpace = true;
            }
        } else {
            throw std::invalid_argument("Ho ten khong duoc chua ky tu khac chu cai.");
        }
    }

    if (letterCount > 50) {
        throw std::length_error("Ho ten vuot qua 50 chu cai.");
    }

    return result;
}

bool is_leap_year(const int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}


std::tm parse_date(const std::string& dateStr, const std::string& format) {
    std::tm tm = {};
    std::istringstream ss(dateStr);
    ss >> std::get_time(&tm, format.c_str());

    if (ss.fail()) {
        throw std::invalid_argument("Dinh dang ngay sinh khong hop le (dd/mm/yyyy).");
    }
    return tm;
}


std::tm parse_date(const std::string& dateStr) {
    return parse_date(dateStr, "%d/%m/%Y");
}

char parse_char(const std::string &line) {
    if (line.size() != 1) {
        std::cerr << "Chuoi khong phai chu cai hop le\n";
        return -1;
    }
    const char c = line[0];
    if (isalpha(c)) {
        return c;
    }
    std::cerr << "Chuoi khong phai chu cai hop le\n";
    return -1;
}

int parse_int(const std::string &line) {
    try {
        return std::stoi(line);
    } catch (const std::invalid_argument &e) {
        std::cerr << "Chuoi khong phai so integer hop le\n";
    } catch (const std::out_of_range &e) {
        std::cerr << "So vuot qua pham vi integer\n";
    }
    return -1;
}

long parse_long(const std::string &line) {
    try {
        return std::stol(line);
    } catch (const std::invalid_argument &e) {
        std::cerr << "Chuoi khong phai so long hop le\n";
    } catch (const std::out_of_range &e) {
        std::cerr << "So vuot qua pham vi long\n";
    }
    return -1;
}

double parse_double(const std::string &line) {
    try {
        return std::stod(line);
    } catch (const std::invalid_argument &e) {
        std::cerr << "Chuoi khong phai so double hop le\n";
    } catch (const std::out_of_range &e) {
        std::cerr << "So vuot qua pham vi double\n";
    }
    return -1;
}

std::vector<int> string_to_int_vector(const std::string& s, const size_t size) {
    std::vector<int> result;
    std::istringstream iss(s);
    int number;
    while (result.size() < size && iss >> number) {
        result.push_back(number);
    }
    return result;
}

std::vector<long> string_to_long_vector(const std::string& s, const size_t size) {
    std::vector<long> result;
    std::istringstream iss(s);
    long number;
    while (result.size() < size && iss >> number) {
        result.push_back(number);
    }
    return result;
}
