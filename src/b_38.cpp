#include <string>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <utility>
#include "util.h"
#include "b_38.h"

int main() {
    using namespace std;
    cerr << "b_38: BẢNG ĐIỂM THÀNH PHẦN - 1" << endl;
    string line;
    cerr << "Nhập số sinh viên N:" << endl;
    bool is_valid = false;
    int N = 0;
    do {
        getline(cin, line);
        try {
            N = parse_int(line);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            continue;
        }
        if (N < 1) {
            cerr << "T phải >= 1" << endl;
            continue;
        }
        if (N > 100) {
            cerr << "N phải <= 100" << endl;
            continue;
        }
        is_valid = true;
    } while (!is_valid);
    vector<Student> S_inputs;

    for (int i = 0; i < N; i++) {
        cerr << "Nhập mã của sinh viên " << i + 1 << ":" << endl;
        string code;
        do {
            try {
                is_valid = false;
                getline(cin, line);
                if (line.size() > 15) {
                    cerr << "Mã không quá 15 ký tự" << endl;
                    continue;
                }
                if (line.find(' ') != std::string::npos) {
                    cerr << "Mã không được có khoảng trắng" << endl;
                    continue;
                }
                code = line;
            } catch (const exception &e) {
                cerr << e.what() << endl;
                continue;
            }
            is_valid = true;
        } while (!is_valid);
        cerr << "Nhập họ tên của sinh viên " << i + 1 << ":" << endl;
        string fullname;
        do {
            try {
                is_valid = false;
                getline(cin, line);
                fullname = trim_and_validate_name(line, 50);
            } catch (const exception &e) {
                cerr << e.what() << endl;
                continue;
            }
            is_valid = true;
        } while (!is_valid);
        cerr << "Nhập lớp của sinh viên " << i + 1 << ":" << endl;
        string clazz;
        do {
            try {
                is_valid = false;
                getline(cin, line);
                if (line.size() > 15) {
                    cerr << "Lớp không quá 15 ký tự" << endl;
                    continue;
                }
                if (line.find(' ') != std::string::npos) {
                    cerr << "Lớp không được có khoảng trắng" << endl;
                    continue;
                }
                clazz = line;
            } catch (const exception &e) {
                cerr << e.what() << endl;
                continue;
            }
            is_valid = true;
        } while (!is_valid);
        cerr << "Nhập điểm môn 1 của sinh viên " << i + 1 << ":" << endl;
        float subject_1_mark = 0;
        do {
            try {
                is_valid = false;
                getline(cin, line);
                subject_1_mark = parse_float(line);
                if (subject_1_mark < 0) {
                    cerr << "Điểm môn 1 phải >= 0" << endl;
                    continue;
                }
                if (subject_1_mark > 10) {
                    cerr << "Điểm môn 1 phải <= 10" << endl;
                    continue;
                }
            } catch (const exception &e) {
                cerr << e.what() << endl;
                continue;
            }
            is_valid = true;
        } while (!is_valid);
        float subject_2_mark = 0;
        cerr << "Nhập điểm môn 2 của sinh viên " << i + 1 << ":" << endl;
        do {
            try {
                is_valid = false;
                getline(cin, line);
                subject_2_mark = parse_float(line);
                if (subject_2_mark < 0) {
                    cerr << "Điểm môn 2 phải >= 0" << endl;
                    continue;
                }
                if (subject_2_mark > 10) {
                    cerr << "Điểm môn 2 phải <= 10" << endl;
                    continue;
                }
            } catch (const exception &e) {
                cerr << e.what() << endl;
                continue;
            }
            is_valid = true;
        } while (!is_valid);
        cerr << "Nhập điểm môn 3 của sinh viên " << i + 1 << ":" << endl;
        float subject_3_mark = 0;
        do {
            try {
                is_valid = false;
                getline(cin, line);
                subject_3_mark = parse_float(line);
                if (subject_3_mark < 0) {
                    cerr << "Điểm môn 3 phải >= 0" << endl;
                    continue;
                }
                if (subject_3_mark > 10) {
                    cerr << "Điểm môn 3 phải <= 10" << endl;
                    continue;
                }
            } catch (const exception &e) {
                cerr << e.what() << endl;
                continue;
            }
            is_valid = true;
        } while (!is_valid);
        const Student student(code, fullname, clazz, subject_1_mark, subject_2_mark, subject_3_mark);
        S_inputs.push_back(student);
    }
    cerr << "Kết quả:" << endl;
    sort(S_inputs.begin(), S_inputs.end());
    for (int i = 0; i < N; ++i) {
        const Student& student = S_inputs[i];
        cout << i + 1 << " " << student << endl;
    }
    return 0;
}


Student::Student(std::string code, std::string fullname, std::string clazz, const float subject1_mark,
                 const float subject2_mark, const float subject3_mark)
    : code(std::move(code)),
      fullname(std::move(fullname)),
      clazz(std::move(clazz)),
      subject1Mark(subject1_mark),
      subject2Mark(subject2_mark),
      subject3Mark(subject3_mark) {
}

bool Student::operator<(const Student &other) const {
    return code < other.code;
}

std::ostream & operator<<(std::ostream &os, const Student &student) {
    using namespace std;
    os
            << student.code << " "
            << student.fullname << " "
            << student.clazz << " "
            << fixed << setprecision(1) << student.subject1Mark << " "
            << fixed << setprecision(1) << student.subject2Mark << " "
            << fixed << setprecision(1) << student.subject3Mark;
    return os;
}
