#include <iomanip>
#include <ios>
#include <iostream>
#include <set>
#include "util.h"
#include "b_43.h"

int main() {
    using namespace std;
    // cerr << "b_43: SẮP XẾP THEO MÃ SINH VIÊN" << endl;
    string line;
    bool is_valid = false;
    int i = 0;
    vector<Student> S_inputs;
    set<string> S_codes;
    while (i % 4 == 0) {
        if (i >= 4000) {
            break;
        }
        const int s_idx = i / 4;
        string code;
        cerr << "Nhập mã của sinh viên " << s_idx + 1 << ": (Enter để dừng nhập thêm Sinh viên)" << endl;
        do {
            try {
                is_valid = false;
                getline(cin, line);
                if (trim(line).empty()) {
                    goto result;
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
        i++;
        cerr << "Nhập họ tên của sinh viên " << s_idx + 1 << ":" << endl;
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
        i++;
        cerr << "Nhập lớp của sinh viên " << s_idx + 1 << ":" << endl;
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
        i++;
        string email;
        cerr << "Nhập email của sinh viên " << s_idx + 1 << ":" << endl;
        do {
            try {
                is_valid = false;
                getline(cin, line);
                if (line.size() > 20) {
                    cerr << "Email không quá 20 ký tự" << endl;
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
