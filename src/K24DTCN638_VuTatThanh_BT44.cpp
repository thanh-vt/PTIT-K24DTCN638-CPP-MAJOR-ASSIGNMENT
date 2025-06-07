#include <iomanip>
#include <ios>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT44.h"

#include <algorithm>
#include <map>

std::map<std::string, std::string> major_alias_to_code;

// LIỆT KÊ SINH VIÊN THEO NGÀNH
int main() {
    using namespace std;
    const string filename = "K24DTCN638_VuTatThanh_BT44.txt";
    ifstream file(filename); // Mở file để đọc
    if (!file) {
        cerr << "Khong the mo file input " << filename << endl;
        return 1;
    }

    string line;
    if (!getline(file, line)) {
        cerr << "Khong co dong tiep theo" << endl;
        return 2;
    }
    const int N = parse_int(line);
    if (N < 1 || N > 50) {
        cerr << "N phai lon hon 0 va nho hon 50" << endl;
        return 2;
    }
    vector<Student> students;
    for (int i = 0; i < N; i++) {
        string code, fullname, clazz, email;
        if (!getline(file, code)) {
            cerr << "Khong co dong tiep theo" << endl;
            return 2;
        }
        if (!getline(file, fullname)) {
            cerr << "Khong co dong tiep theo" << endl;
            return 2;
        }
        if (!getline(file, clazz)) {
            cerr << "Khong co dong tiep theo" << endl;
            return 2;
        }
        if (!getline(file, email)) {
            cerr << "Khong co dong tiep theo" << endl;
            return 2;
        }
        if (i > 1000) {
            cerr << "Co hon 1000 sinh vien trong danh sach"<< endl;
            return 2;
        }
        try {
            Student student(code, fullname, clazz, email);
            students.push_back(student);
        } catch (const exception &ex) {
            cerr << ex.what() << endl;
            return 2;
        }
    }
    // ánh xạ tên chuyen ngành với mã chuyên nganh
    major_alias_to_code["ke toan"] = "DCKT";
    major_alias_to_code["cong nghe thong tin"] = "DCCN";
    major_alias_to_code["an toan thong tin"] = "DCAT";
    major_alias_to_code["vien thong"] = "DCKT";
    major_alias_to_code["dien tu"] = "DCDT";
    if (!getline(file, line)) {
        cerr << "Khong co dong tiep theo" << endl;
        return 2;
    }
    const int M = parse_int(line);
    for (int i = 0; i < M; i++) {
        string Q;
        if (!getline(file, Q)) {
            cerr << "Khong co dong tiep theo" << endl;
            return 2;
        }
        filter_students_by_major(students, Q);
    }

    file.close();

    return 0;
}

void filter_students_by_major(const std::vector<Student>& students, const std::string& majorAlias) {
    using namespace std;
    cout << "DANH SACH SINH VIEN NGANH " << majorAlias << ":" << endl;
    for (const auto& student : students) {
        string studentMajorCode = student.code.substr(3, 4); // Lấy ngành học từ mã sinh viên (4 chữ cái từ thứ 4 đến thứ 7)
        string normalizeMajorAlias = trim(majorAlias); // trim khoảng trắng chuỗi truy vấn
        transform(normalizeMajorAlias.begin(), normalizeMajorAlias.end(), normalizeMajorAlias.begin(), ::tolower); // viết thường chuỗi truy vấn

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
                majorCode == "DCDT") { // Điện tử
                cout << student.code << " " << student.fullname << " " << student.clazz << " " << student.email << endl;
                }
        }
    }
}

Student::Student(const std::string &code, const std::string &fullname, const std::string &clazz, const std::string &email) {
    using namespace std;
    this->code = code;
    this->fullname = normalize_and_validate_name(fullname);
    if (clazz.size() > 15) {
        throw invalid_argument("Lop khong qua 15 ky tu");
    }
    if (clazz.find(' ') != std::string::npos) {
        throw invalid_argument("Lop khong co khoang trong");
    }
    this->clazz = clazz;
    if (email.size() > 20) {
        throw invalid_argument("Email khong qua 15 ky tu");
    }
    if (email.find(' ') != std::string::npos) {
        throw invalid_argument("Email khong co khoang trong");
    }
    this->email = email;
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
