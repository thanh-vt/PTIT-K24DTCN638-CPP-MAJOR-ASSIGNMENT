#include <iomanip>
#include <ios>
#include <iostream>
#include <set>
#include <vector>
#include "b_43.h"

#include <regex>

int main() {
    using namespace std;
    // cerr << "b_43: SẮP XẾP THEO MÃ SINH VIÊN" << endl;
    string line;
    vector<Student> S_inputs;
    set<string> S_codes;
    int i = 0;
    while (i % 4 == 0) {
        if (i >= 4000) {
            break;
        }
        // const int s_idx = i / 4;
        string code;
        // cerr << "Nhập mã của sinh viên " << s_idx + 1 << ": (Enter để dừng nhập thêm Sinh viên)" << endl;
        getline(cin, line);
        if (trim(line).empty()) {
            goto result;
        }
        if (line.size() > 15) {
            cerr << "Mã không quá 15 ký tự" << endl;
            return 2;
        }
        if (line.find(' ') != std::string::npos) {
            cerr << "Mã không có khoảng trống" << endl;
            return 2;
        }
        if (S_codes.find(line) != S_codes.end()) {
            cerr << "Mã" << line << " đã tồn tại" << endl;
            return 2;
        }
        code = move(line);
        i++;
        // cerr << "Nhập họ tên của sinh viên " << s_idx + 1 << ":" << endl;
        getline(cin, line);
        string fullname;
        try {
            fullname = trim_and_validate_name(line, 100);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
        i++;
        // cerr << "Nhập lớp của sinh viên " << s_idx + 1 << ":" << endl;
        getline(cin, line);
        if (line.size() > 15) {
            cerr << "Lớp không quá 15 ký tự" << endl;
            return 2;
        }
        if (line.find(' ') != std::string::npos) {
            cerr << "Lớp không có khoảng trống" << endl;
            return 2;
        }
        const string clazz = move(line);
        i++;
        // cerr << "Nhập email của sinh viên " << s_idx + 1 << ":" << endl;
        getline(cin, line);
        if (line.size() > 20) {
            cerr << "Email không quá 20 ký tự" << endl;
            return 2;
        }
        try {
            if (line.find(' ') != std::string::npos) {
                cerr << "Email không có khoảng trống" << endl;
                return 2;
            }
            line = validate_email(line);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
        const string email = move(line);
        i++;
        const Student student(code, fullname, clazz, email);
        S_inputs.push_back(student);
        S_codes.insert(code);
    }
    result:
    // cerr << "Kết quả:" << endl;
    for (const Student &student: S_inputs) {
        cout << student << endl;
    }
    return 0;
}

Student::Student(std::string code, std::string fullname, std::string clazz, std::string email): code(std::move(code)),
    fullname(std::move(fullname)),
    clazz(std::move(clazz)),
    email(std::move(email)) {
}

bool Student::operator<(const Student &other) const {
    if (clazz != other.clazz)
        return clazz < other.clazz; // tăng dần
    return code < other.code; // tăng dần
}

std::ostream &operator<<(std::ostream &os, const Student &student) {
    using namespace std;
    os
            << student.code << " "
            << student.fullname << " "
            << student.clazz << " "
            << student.email;
    return os;
}

int parse_int(const std::string &line) {
    try {
        size_t idx;
        int value = std::stoi(line, &idx);
        if (idx != line.size()) throw std::invalid_argument("Extra characters");
        return value;
    } catch (const std::exception &e) {
        throw exit_code_exception(2, "Invalid integer input");
    }
}

std::string trim(const std::string &str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

std::string trim_and_validate_name(const std::string &input, int max_length) {
    std::string trimmed = trim(input);
    if (trimmed.empty() || trimmed.size() > static_cast<size_t>(max_length)) {
        throw exit_code_exception(2, "Invalid name length");
    }
    return trimmed;
}

std::string validate_email(const std::string& email) {
    using namespace std;
    // REGEX email
    static const std::regex email_regex(R"(^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$)");
    if (!std::regex_match(email, email_regex)) {
        throw invalid_argument("Email không đúng định dạng");
    }
    return email;
}
