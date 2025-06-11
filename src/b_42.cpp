#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <set>
#include <utility>
#include <vector>
#include "b_42.h"

#include <regex>

int main() {
    using namespace std;
    // cerr << "b_42: SẮP XẾP SINH VIÊN THEO LỚP" << endl;
    string line;
    // cerr << "Nhập số sinh viên N:" << endl;
    getline(cin, line);
    int N;
    try {
        N = parse_int(line);
        if (N < 1) {
            cerr << "N phải >= 1" << endl;
            return 2;
        }
        if (N > 1000) {
            cerr << "N phải <= 1000" << endl;
            return 2;
        }
    } catch (const exception &e) {
        cerr << e.what() << endl;
        return 2;
    }
    vector<Student> S_inputs;
    set<string> S_codes;
    for (int i = 0; i < N; i++) {
        string code;
        // cerr << "Nhập mã của sinh viên " << i + 1 << ":" << endl;
        getline(cin, line);
        if (line.empty()) {
            cerr << "Mã không được bỏ trống" << endl;
            return 2;
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
        // cerr << "Nhập họ tên của sinh viên " << i + 1 << ":" << endl;
        getline(cin, line);
        string fullname;
        try {
            fullname = trim_and_validate_name(line, 100);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
        // cerr << "Nhập lớp của sinh viên " << i + 1 << ":" << endl;
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
        // cerr << "Nhập email của sinh viên " << i + 1 << ":" << endl;
        getline(cin, line);
        if (line.size() > 50) {
            cerr << "Email không quá 50 ký tự" << endl;
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
        string email = move(line);
        const Student student(code, fullname, clazz, email);
        S_inputs.push_back(student);
        S_codes.insert(code);
    }
    // cerr << "Kết quả:" << endl;
    sort(S_inputs.begin(), S_inputs.end());
    for (int i = 0; i < N; ++i) {
        const Student& student = S_inputs[i];
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
    using namespace std;
    try {
        size_t pos;
        const int x = stoi(line, &pos);
        if (pos != line.size()) {
            throw exit_code_exception(2, "Chuỗi nhập có chứa các ký tự không hợp lệ");
        }
        return x;
    } catch (const invalid_argument &e) {
        throw exit_code_exception(2, "Chuỗi nhập không phải số kiểu integer hợp lệ");
    } catch (const out_of_range &e) {
        throw exit_code_exception(2, "Số vượt quá phạm vi kiểu integer");
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

