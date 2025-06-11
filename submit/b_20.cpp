#include <iostream>
#include <iomanip>
#include <utility>
#include <sstream>
#include <regex>
#include <ctime>
#include "b_20.h"

int main() {
    using namespace std;
    // cerr << "b_20: CẤU TRÚC THÍ SINH" << endl;
    string line;
    // cerr << "Nhập tên của thí sinh:" << endl;
    getline(cin, line);
    string fullname;
    try {
        fullname = trim_and_validate_name(line);
    } catch (const exception &e) {
        cerr << e.what() << endl;
        return 2;
    }
    // cerr << "Nhập ngày sinh của thí sinh:" << endl;
    getline(cin, line);
    tm dateOfBirth;
    try {
        dateOfBirth = parse_date(line);
    } catch (const exception &e) {
        cerr << e.what() << endl;
        return 2;
    }
    // cerr << "Nhập điểm môn 1 của thí sinh:" << endl;
    getline(cin, line);
    float subject1Mark;
    try {
        subject1Mark = parse_float(line);
    } catch (const exception &e) {
        cerr << e.what() << endl;
        return 2;
    }
    // cerr << "Nhập điểm môn 2 của thí sinh:" << endl;
    getline(cin, line);
    float subject2Mark;
    try {
        subject2Mark = parse_float(line);
    } catch (const exception &e) {
        cerr << e.what() << endl;
        return 2;
    }
    // cerr << "Nhập điểm môn 3 của thí sinh:" << endl;
    getline(cin, line);
    float subject3Mark;
    try {
        subject3Mark = parse_float(line);
    } catch (const exception &e) {
        cerr << e.what() << endl;
        return 2;
    }
    // cerr << "Kết quả:" << endl;
    const Candidate candidate(fullname, dateOfBirth, subject1Mark, subject2Mark, subject3Mark);
    cout << candidate << endl;
    return 0;
}

// Function definitions
std::string trim_and_validate_name(const std::string &line) {
    using namespace std;
    if (line.empty()) {
        throw exit_code_exception(2, "Tên không được để trống");
    }
    if (line.size() > 100) {
        throw exit_code_exception(2, "Tên không được dài quá 100 ký tự");
    }
    static const regex name_regex("^[a-zA-Z ]+$");
    if (!regex_match(line, name_regex)) {
        throw exit_code_exception(2, "Tên chỉ được chứa chữ cái và dấu cách");
    }
    return line;
}

std::tm parse_date(const std::string &line) {
    using namespace std;
    static const regex date_regex("^(\\d{2})/(\\d{2})/(\\d{4})$");
    smatch matches;
    if (!regex_match(line, matches, date_regex)) {
        throw exit_code_exception(2, "Định dạng ngày không hợp lệ, yêu cầu: dd/mm/yyyy");
    }
    tm date = {};
    date.tm_mday = stoi(matches[1].str());
    date.tm_mon = stoi(matches[2].str()) - 1;
    date.tm_year = stoi(matches[3].str()) - 1900;
    if (date.tm_mday < 1 || date.tm_mday > 31) {
        throw exit_code_exception(2, "Ngày không hợp lệ");
    }
    if (date.tm_mon < 0 || date.tm_mon > 11) {
        throw exit_code_exception(2, "Tháng không hợp lệ");
    }
    if (date.tm_year < 0) {
        throw exit_code_exception(2, "Năm không hợp lệ");
    }
    return date;
}

float parse_float(const std::string &line) {
    using namespace std;
    try {
        size_t pos;
        const float x = stof(line, &pos);
        if (pos != line.size()) {
            throw exit_code_exception(2, "Chuỗi nhập có chứa các ký tự không hợp lệ");
        }
        if (x < 0) {
            throw exit_code_exception(2, "Điểm phải >= 0");
        }
        if (x > 10) {
            throw exit_code_exception(2, "Điểm phải <= 10");
        }
        return x;
    } catch (const invalid_argument &e) {
        throw exit_code_exception(2, "Chuỗi nhập không phải số kiểu float hợp lệ");
    } catch (const out_of_range &e) {
        throw exit_code_exception(2, "Số vượt quá phạm vi kiểu float");
    }
}

std::string print_date(const std::tm &date) {
    using namespace std;
    ostringstream oss;
    oss << setfill('0') << setw(2) << date.tm_mday << "/"
        << setfill('0') << setw(2) << (date.tm_mon + 1) << "/"
        << setfill('0') << setw(4) << (date.tm_year + 1900);
    return oss.str();
}

Candidate::Candidate(std::string fullname, const std::tm &dateOfBirth, const float subject1Mark, const float subject2Mark,
                     const float subject3Mark): 
    fullname(std::move(fullname)), 
    dateOfBirth(dateOfBirth), 
    subject1Mark(subject1Mark),
    subject2Mark(subject2Mark), 
    subject3Mark(subject3Mark) {
    this->totalMark = subject1Mark + subject2Mark + subject3Mark;
}

std::ostream &operator<<(std::ostream &os, const Candidate &candidate) {
    using namespace std;
    os
            << candidate.fullname << " "
            << print_date(candidate.dateOfBirth) << " "
            << fixed << setprecision(1) << candidate.totalMark;
    return os;
}
