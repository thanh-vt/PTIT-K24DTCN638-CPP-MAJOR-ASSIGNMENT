#include <iomanip>
#include <ios>
#include <stdexcept>
#include <iostream>
#include "util.h"
#include "b_43.h"

// SẮP XẾP THEO MÃ SINH VIÊN
int main() {
    using namespace std;
    const string filename = "K24DTCN638_VuTatThanh_BT43.txt";
    ifstream file(filename); // Mở file để đọc
    if (!file) {
        cerr << "Khong the mo file input " << filename << endl;
        return 1;
    }

    int i = 0;
    vector<Student> students;
    while (i % 4 == 0) {
        string code, fullname, clazz, email;
        if (!getline(file, code)) {
            if (i == 0) {
                cerr << "File khong co du lieu"<< endl;
            }
            break;
        }
        i++;
        if (!getline(file, fullname)) {
            cerr << "Ket thuc o dong " << i << " => khong phai chan lan 4 dong "<< endl;
            return 2;
        }
        i++;
        if (!getline(file, clazz)) {
            cerr << "Ket thuc o dong " << i << " => khong phai chan lan 4 dong "<< endl;
            return 2;
        }
        i++;
        if (!getline(file, email)) {
            cerr << "Ket thuc o dong " << i << " => khong phai chan lan 4 dong "<< endl;
            return 2;
        }
        i++;
        if (i > 4000) {
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
    for (const Student& student : students) {
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
    if (email.size() > 50) {
        throw invalid_argument("Email khong qua 50 ky tu"); // đề bài để max = 15 sai với test case mẫu?
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

