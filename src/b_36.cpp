#include <iomanip>
#include <ios>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <regex>
#include "util.h"
#include "b_36.h"

int main() {
    using namespace std;
    cout << "b_36: DANH SÁCH SINH VIÊN - 3" << endl;
    string line;
    cout << "Nhập số sinh viên N:" << endl;
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
        if (N > 50) {
            cerr << "N phải <= 50" << endl;
            continue;
        }
        is_valid = true;
    } while (!is_valid);
    vector<Student > S_inputs;
    for (int i = 0; i < N; i++) {
        cout << "Nhập họ tên của sinh viên " << i + 1 << ":" << endl;
        string fullname;
        do {
            try {
                is_valid = false;
                getline(cin, line);
                fullname = normalize_and_validate_name(line, 30);
            } catch (const exception &e) {
                cout << e.what() << endl;
                continue;
            }
            is_valid = true;
        } while (!is_valid);
        cout << "Nhập lớp của sinh viên " << i + 1 << ":" << endl;
        string clazz;
        do {
            try {
                is_valid = false;
                getline(cin, line);
                clazz = validate_ptit_clazz(line);
            } catch (const exception &e) {
                cout << e.what() << endl;
                continue;
            }
            is_valid = true;
        } while (!is_valid);
        cout << "Nhập ngày sinh của sinh viên " << i + 1 << ":" << endl;
        tm date_of_birth{};
        do {
            try {
                is_valid = false;
                getline(cin, line);
                date_of_birth = parse_date(line);
            } catch (const exception &e) {
                cout << e.what() << endl;
                continue;
            }
            is_valid = true;
        } while (!is_valid);
        float gpaMark = 0;
        cout << "Nhập điểm GPA của sinh viên " << i + 1 << ":" << endl;
        do {
            try {
                is_valid = false;
                getline(cin, line);
                gpaMark = parse_float(line);
                if (gpaMark < 0) {
                    cerr << "Điểm GPA phải >= 0" << endl;
                    continue;
                }
                if (gpaMark > 4) {
                    cerr << "Điểm GPA phải <= 4" << endl;
                    continue;
                }
                static regex float_regex(R"(^\s*(\d+)(?:\.(\d*?))?\s*$)");
                smatch match;
                if (regex_match(line, match, float_regex)) {
                    string decimal_part = match[2].str();
                    if (decimal_part.size() > 2) {
                        cerr << "Điểm GPA có nhiều nhất 2 chữ số sau dấu phẩy" << endl;
                        continue;
                    }
                }

            } catch (const exception &e) {
                cout << e.what() << endl;
                continue;
            }
            is_valid = true;
        } while (!is_valid);
        const Student student(fullname, clazz, date_of_birth, gpaMark);
        S_inputs.push_back(student);
    }
    cout << "Kết quả:" << endl;
    sort(S_inputs.begin(), S_inputs.end());
    for (const Student& student : S_inputs) {
        cout << student << endl;
    }
    return 0;
}

Student::Student(std::string fullname, std::string clazz, const std::tm &date_of_birth, const float gpa_mark)
        : fullname(std::move(fullname)),
          clazz(std::move(clazz)),
          dateOfBirth(date_of_birth),
          gpaMark(gpa_mark) {
    using namespace std;
    ++counter;
    std::ostringstream oss;
    oss << "B20DCCN" << setw(3) << setfill('0') << counter;
    this->code = oss.str();
}

bool Student::operator<(const Student &other) const {
    return gpaMark > other.gpaMark; // gpa giảm dần
}

std::ostream &operator<<(std::ostream &os, const Student &student) {
    using namespace std;
    os
            << student.code << " "
            << student.fullname << " "
            << print_date(student.dateOfBirth) << " "
            << student.clazz << " "
            << fixed << setprecision(2) << student.gpaMark;
    return os;
}
