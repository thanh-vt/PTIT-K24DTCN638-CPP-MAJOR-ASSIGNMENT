#include <iomanip>
#include <ios>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <utility>
#include "util.h"
#include "b_44.h"

std::map<std::string, std::string> major_alias_to_code;

int main() {
    using namespace std;
    // cerr << "b_44: LIỆT KÊ SINH VIÊN THEO NGÀNH" << endl;
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
    vector<string> Q_inputs;
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
        const Student student(code, fullname, clazz, email);
        S_inputs.push_back(student);
        S_codes.insert(code);
    }
    // ánh xạ tên chuyen ngành với mã chuyên nganh
    major_alias_to_code["KE TOAN"] = "DCKT";
    major_alias_to_code["CONG NGHE THONG TIN"] = "DCCN";
    major_alias_to_code["AN TOAN THONG TIN"] = "DCAT";
    major_alias_to_code["VIEN THONG"] = "DCKT";
    major_alias_to_code["DIEN TU"] = "DCDT";
    cerr << "Nhập số truy vấn Q:" << endl;
    int Q = 0;
    do {
        getline(cin, line);
        try {
            Q = parse_int(line);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            continue;
        }
        if (Q < 1) {
            cerr << "Q phải >= 1" << endl;
            continue;
        }
        is_valid = true;
    } while (!is_valid);
    for (int i = 0; i < Q; i++) {
        cerr << "Nhập chuỗi truy vấn thứ " << i + 1 << endl;
        do {
            is_valid = false;
            getline(cin, line);
            if (trim(line).empty()) {
                cerr << "Chuỗi truy vẫn ko được bỏ trống" << endl;
                continue;
            }
            is_valid = true;
        } while (!is_valid);
        Q_inputs.push_back(move(line));
    }
    // cerr << "Kết quả:" << endl;
    for (int i = 0; i < Q; ++i) {
        filter_students_by_major(S_inputs, Q_inputs[i]);
    }
    return 0;
}

void filter_students_by_major(const std::vector<Student> &students, const std::string &majorAlias) {
    using namespace std;
    string normalizeMajorAlias = trim(majorAlias); // trim khoảng trắng chuỗi truy vấn
    transform(normalizeMajorAlias.begin(), normalizeMajorAlias.end(), normalizeMajorAlias.begin(), ::toupper);
    // viết hoa chuỗi truy vấn
    cout << "DANH SACH SINH VIEN NGANH " << normalizeMajorAlias << ":" << endl;
    for (const Student &student: students) {
        string studentMajorCode = student.code.substr(3, 4);
        // Lấy ngành học từ mã sinh viên (4 chữ cái từ thứ 4 đến thứ 7)
        if (major_alias_to_code.count(normalizeMajorAlias) == 0) {
            throw invalid_argument("Ten nganh hoc khong hop le");
        }
        string majorCode = major_alias_to_code[normalizeMajorAlias];
        if (studentMajorCode == majorCode) {
            // Kiểm tra điều kiện cho từng ngành
            if (majorCode == "DCKT" || // Kế toán
                (majorCode == "DCCN" && student.clazz[0] != 'E') || // Công nghệ thông tin
                (majorCode == "DCAT" && student.clazz[0] != 'E') || // An toàn thông tin
                majorCode == "DCVT" || // Viễn thông
                majorCode == "DCDT") {
                // Điện tử
                cout << student.code << " " << student.fullname << " " << student.clazz << " " << student.email << endl;
            }
        }
    }
}

Student::Student(std::string code, std::string fullname, std::string clazz, std::string email)
    : code(std::move(code)), fullname(std::move(fullname)), clazz(std::move(clazz)), email(std::move(email)) {
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
