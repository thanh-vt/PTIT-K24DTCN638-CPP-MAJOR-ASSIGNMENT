#include <fstream>
#include <string>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include "util.h"
#include "b_38.h"

// BẢNG ĐIỂM THÀNH PHẦN - 1
int main() {
    using namespace std;
    const string filename = "K24DTCN638_VuTatThanh_BT38.txt";
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
    if (N < 1 || N > 40) {
        cerr << "N phải lon hon 0 va nho hon 40" << endl;
        return 2;
    }
    vector<Student> students;

    for (int i = 0; i < N; i++) {
        string code, fullname, clazz, subject1MarkStr, subject2MarkStr, subject3MarkStr;

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
        if (!getline(file, subject1MarkStr)) {
            cerr << "Khong co dong tiep theo" << endl;
            return 2;
        }
        if (!getline(file, subject2MarkStr)) {
            cerr << "Khong co dong tiep theo" << endl;
            return 2;
        }
        if (!getline(file, subject3MarkStr)) {
            cerr << "Khong co dong tiep theo" << endl;
            return 2;
        }
        try {
            Student student(code, fullname, clazz, subject1MarkStr, subject2MarkStr, subject3MarkStr);
            students.push_back(student);
        } catch (const exception &ex) {
            cerr << ex.what() << endl;
            return 2;
        }
    }

    function<bool(const Student&, const Student&)> compare_code = [](const Student &s1, const Student &s2) {
        using namespace std;
        const string code1 = s1.code;
        const string code2 = s2.code;
        // Compare code
        return code1 < code2;
    };

    // Sắp xếp theo ngày sinh từ già nhất đến trẻ nhất
    sort(students.begin(), students.end(), compare_code);

    file.close();
    for (int i = 0; i < students.size(); ++i) {
        cout << i + 1 << " " << students.at(i) << endl;
    }

    return 0;
}

Student::Student(const std::string &code, const std::string &fullname, const std::string &clazz,
    const std::string &subject1MarkStr,const std::string &subject2MarkStr, const std::string &subject3MarkStr) {
    using namespace std;
    this->code = code;
    this->fullname = trim_and_validate_name(fullname, 50);
    if (clazz.size() > 15) {
        throw invalid_argument("Lop khong qua 15 ky tu");
    }
    if (clazz.find(' ') != std::string::npos) {
        throw invalid_argument("Lop khong co khoang trong");
    }
    this->clazz = clazz;
    this->subject1Mark = parse_float(subject1MarkStr);
    this->subject2Mark = parse_float(subject2MarkStr);
    this->subject3Mark = parse_float(subject3MarkStr);
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
