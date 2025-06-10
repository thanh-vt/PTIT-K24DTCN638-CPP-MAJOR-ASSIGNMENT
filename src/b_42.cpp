#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <set>
#include <utility>
#include "util.h"
#include "b_42.h"

int main() {
    using namespace std;
    cerr << "b_42: SẮP XẾP SINH VIÊN THEO LỚP" << endl;
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
            cerr << "N phải >= 1" << endl;
            continue;
        }
        if (N > 1000) {
            cerr << "N phải <= 1000" << endl;
            continue;
        }
        is_valid = true;
    } while (!is_valid);
    vector<Student> S_inputs;
    set<string> S_codes;
    for (int i = 0; i < N; i++) {
        string code;
        cerr << "Nhập mã của sinh viên " << i + 1 << ":" << endl;
        do {
            try {
                is_valid = false;
                getline(cin, line);
                if (line.empty()) {
                    cerr << "Mã không được bỏ trống" << endl;
                    continue;
                }
                if (line.size() > 15) {
                    cerr << "Mã không quá 15 ký tự" << endl;
                    continue;
                }
                if (line.find(' ') != std::string::npos) {
                    cerr << "Mã không có khoảng trống" << endl;
                    continue;
                }
                if (S_codes.find(line) != S_codes.end()) {
                    cerr << "Mã" << line << " đã tồn tại" << endl;
                    continue;
                }
                code = move(line);
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
                fullname = trim_and_validate_name(line, 100);
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
                    cerr << "Lớp không có khoảng trống" << endl;
                    continue;
                }
                clazz = move(line);
            } catch (const exception &e) {
                cerr << e.what() << endl;
                continue;
            }
            is_valid = true;
        } while (!is_valid);
        string email;
        cerr << "Nhập email của sinh viên " << i + 1 << ":" << endl;
        do {
            try {
                is_valid = false;
                getline(cin, line);
                if (line.size() > 50) {
                    cerr << "Email không quá 50 ký tự" << endl;
                    continue;
                }
                if (line.find(' ') != std::string::npos) {
                    cerr << "Email không có khoảng trống" << endl;
                    continue;
                }
                email = move(line);
            } catch (const exception &e) {
                cerr << e.what() << endl;
                continue;
            }
            is_valid = true;
        } while (!is_valid);
        const Student student(code, fullname, clazz, email);
        S_inputs.push_back(student);
        S_codes.insert(code);
    }
    cerr << "Kết quả:" << endl;
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



