#include <iomanip>
#include <ios>
#include <stdexcept>
#include <iostream>
#include <functional>
#include <algorithm>
#include "util.h"
#include "b_39.h"

int main() {
    using namespace std;
    cout << "b_39: LIỆT KÊ SINH VIÊN THEO NGÀNH" << endl;

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

    file.close();
    function<bool(const Student&, const Student&)> compare_student = [](const Student &s1, const Student &s2) {
        using namespace std;
        const string code1 = s1.code;
        const string code2 = s2.code;
        // Compare code
        return code1 < code2;
    };

    // Sắp xếp theo ngày sinh từ già nhất đến trẻ nhất
    sort(students.begin(), students.end(), compare_student);

    for (const auto & student : students) {
        cout << student << endl;
    }

    return 0;
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
