#include <iomanip>
#include <iostream>
#include <regex>
#include "util.h"

Gender parse_gender(const std::string &genderStr) {
    using namespace std;
    if (genderStr == "Nam") {
        return MALE;
    }
    if (genderStr == "Nu") {
        return FEMALE;
    }
    throw invalid_argument("Gioi tinh khong hop le (Nam / Nu).");
}

std::string print_gender(const Gender gender) {
    switch (gender) {
        case MALE:
            return "Nam";
        case FEMALE:
            return "Nu";
        default:
            return "";
    }
}

std::string trim(const std::string& str) {
    using namespace std;
    const size_t first = str.find_first_not_of(" \t\n\r\f\v");
    if (first == string::npos)
        return ""; // Chuỗi toàn khoảng trắng
    const size_t last = str.find_last_not_of(" \t\n\r\f\v");
    return str.substr(first, (last - first + 1));
}

std::string trim_and_validate_name(const std::string& input) {
    return trim_and_validate_name(input, 50);
}

std::string trim_and_validate_name(const std::string& input, const int max_length) {
    using namespace std;
    const string trimmed = trim(input);
    string result;
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
            throw invalid_argument("Ho ten khong duoc chua ky tu khac chu cai.");
        }
    }

    if (letterCount > max_length) {
        throw length_error(string("Ho ten vuot qua ") + to_string(max_length) + " chu cai.");
    }

    return result;
}

std::string normalize_and_validate_name(const std::string& input) {
    return normalize_and_validate_name(input, 50);
}

std::string normalize_and_validate_name(const std::string& input, const int max_length) {
    using namespace std;
    stringstream ss(trim_and_validate_name(input, max_length));
    string word, result;

    while (ss >> word) {
        // Convert to lowercase
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        // Capitalize first letter
        word[0] = toupper(word[0]);
        // Append to result
        if (!result.empty()) result += " ";
        result += word;
    }
    return result;
}

bool is_leap_year(const int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}


std::tm parse_date(const std::string& dateStr, const std::string& format) {
    using namespace std;
    tm tm = {};
    istringstream ss(dateStr);
    ss >> get_time(&tm, format.c_str());

    if (ss.fail()) {
        throw invalid_argument("Dinh dang ngay sinh khong hop le (dd/mm/yyyy).");
    }
    return tm;
}


std::tm parse_date(const std::string& dateStr) {
    return parse_date(dateStr, "%d/%m/%Y");
}

std::string print_date(const std::tm &date, const std::string &format) {
    using namespace std;
    stringstream ss;
    ss << put_time(&date, format.c_str());
    return ss.str();
}

std::string print_date(const std::tm &date) {
    return print_date(date, "%d/%m/%Y");
}

char parse_char(const std::string &line) {
    using namespace std;
    if (line.size() != 1) {
        cerr << "Chuoi khong phai chu cai hop le" << endl;
        return -1;
    }
    const char c = line[0];
    if (isalpha(c)) {
        return c;
    }
    cerr << "Chuoi khong phai chu cai hop le" << endl;
    return -1;
}

int parse_int(const std::string &line) {
    using namespace std;
    try {
        return stoi(line);
    } catch (const invalid_argument &e) {
        cerr << "Chuoi khong phai so integer hop le" << endl;
    } catch (const out_of_range &e) {
        cerr << "So vuot qua pham vi integer" << endl;
    }
    return -1;
}

long parse_long(const std::string &line) {
    using namespace std;
    try {
        return stol(line);
    } catch (const invalid_argument &e) {
        cerr << "Chuoi khong phai so long hop le\n";
    } catch (const out_of_range &e) {
        cerr << "So vuot qua pham vi long\n";
    }
    return -1;
}

float parse_float(const std::string &line) {
    using namespace std;
    try {
        return stof(line);
    } catch (const invalid_argument &e) {
        std::cerr << "Chuoi khong phai so float hop le\n";
    } catch (const out_of_range &e) {
        std::cerr << "So vuot qua pham vi float\n";
    }
    return -1;
}

double parse_double(const std::string &line) {
    using namespace std;
    try {
        return stod(line);
    } catch (const invalid_argument &e) {
        cerr << "Chuoi khong phai so double hop le\n";
    } catch (const out_of_range &e) {
        cerr << "So vuot qua pham vi double\n";
    }
    return -1;
}

std::vector<int> string_to_int_vector(const std::string& s, const size_t size) {
    using namespace std;
    vector<int> result;
    istringstream iss(s);
    int number;
    while (result.size() < size && iss >> number) {
        result.push_back(number);
    }
    return result;
}

std::vector<long> string_to_long_vector(const std::string& s, const size_t size) {
    using namespace std;
    vector<long> result;
    istringstream iss(s);
    long number;
    while (result.size() < size && iss >> number) {
        result.push_back(number);
    }
    return result;
}

std::string validate_ptit_clazz(const std::string &clazz) {
    using namespace std;
    regex pattern(R"(^[A-Z](\d){2}(CQ|TX|DC)CN(\d){2}-[A-Z]$)");

    if (!regex_match(clazz, pattern)) {
        throw invalid_argument("Ten lop khong dung dinh dang ten lop PTIT: ^[A-Z](\\d){2}(CQ|TX|DC)CN(\\d){2}-[A-Z]$");
    }
    return clazz;
}


