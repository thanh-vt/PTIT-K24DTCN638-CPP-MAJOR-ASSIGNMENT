#include <iostream>
#include <iomanip>
#include <utility>
#include "util.h"
#include "b_20.h"

int main() {
    using namespace std;
    cerr << "b_20: CẤU TRÚC THÍ SINH" << endl;
    string line;
    bool is_valid = false;
    cerr << "Nhập tên của thí sinh:" << endl;
    string fullname;
    do {
        try {
            is_valid = false;
            getline(cin, line);
            fullname = trim_and_validate_name(line);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            continue;
        }
        is_valid = true;
    } while (!is_valid);
    cerr << "Nhập ngày sinh của thí sinh:" << endl;
    tm dateOfBirth = {};
    do {
        try {
            is_valid = false;
            getline(cin, line);
            dateOfBirth = parse_date(line);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            continue;
        }
        is_valid = true;
    } while (!is_valid);
    cerr << "Nhập điểm môn 1 của thí sinh:" << endl;
    float subject1Mark = 0;
    do {
        try {
            is_valid = false;
            getline(cin, line);
            subject1Mark = parse_float(line);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            continue;
        }
        is_valid = true;
    } while (!is_valid);
    cerr << "Nhập điểm môn 2 của thí sinh:" << endl;
    float subject2Mark = 0;
    do {
        try {
            is_valid = false;
            getline(cin, line);
            subject2Mark = parse_float(line);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            continue;
        }
        is_valid = true;
    } while (!is_valid);
    cerr << "Nhập điểm môn 3 của thí sinh:" << endl;
    float subject3Mark = 0;
    do {
        try {
            is_valid = false;
            getline(cin, line);
            subject3Mark = parse_float(line);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            continue;
        }
        is_valid = true;
    } while (!is_valid);
    cerr << "Kết quả:" << endl;
    const Candidate candidate(fullname, dateOfBirth, subject1Mark, subject2Mark, subject3Mark);
    cout << candidate << endl;
    return 0;
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
