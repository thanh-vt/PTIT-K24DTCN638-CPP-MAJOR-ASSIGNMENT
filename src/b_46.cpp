#include <iostream>
#include <ostream>
#include <string>
#include <algorithm>
#include "util.h"
#include "b_46.h"

int main() {
    using namespace std;
    cout << "b_46: DANH SÁCH DOANH NGHIỆP NHẬN SINH VIÊN THỰC TẬP - 1" << endl;
    string line;
    if (!getline(file, line)) {
        cerr << "Khong co dong tiep theo" << endl;
        return 2;
    }
    const int total_tests = parse_int(line);
    if (total_tests < 1 || total_tests > 100) {
        cerr << "T phai lon hon hoac bang 1 va nho hon hoac bang 100" << endl;
        return 2;
    }
    vector<Enterprise> enterprises;
    for (int i = 0; i < total_tests; i++) {
        // Xử lý dòng đọc được
        string code, fullname, numberOfInternsStr;
        if (!getline(file, code)) {
            cerr << "Khong co dong tiep theo" << endl;
            return 2;
        }
        if (!getline(file, fullname)) {
            cerr << "Khong co dong tiep theo" << endl;
            return 2;
        }
        if (!getline(file, numberOfInternsStr)) {
            cerr << "Khong co dong tiep theo" << endl;
            return 2;
        }
        Enterprise enterprise(code, fullname, numberOfInternsStr);
        enterprises.push_back(enterprise);
    }
    sort(enterprises.begin(), enterprises.end());
    for (const Enterprise& enterprise : enterprises) {
        cout << enterprise << endl;
    }
    file.close();
    return 0;
}

Enterprise::Enterprise(const std::string &code, const std::string &name, const std::string &numberOfInternsStr) {
    using namespace std;
    if (code.size() > 10) {
        throw invalid_argument("Ma khong vuot qua 10 ky tu");
    }
    if (code.find(' ') != std::string::npos) {
        throw invalid_argument("Ma khong co khoang trong");
    }
    this->code = code;
    if (name.size() > 150) {
        throw invalid_argument("Ten khong vuot qua 150 ky tu");
    }
    this->name = name;
    this->numberOfInterns = parse_int(numberOfInternsStr);
    if (this->numberOfInterns > 1000) {
        throw invalid_argument("So sinh vien khong vuot qua 1000");
    }
}

bool Enterprise::operator<(const Enterprise &other) const {
    if (numberOfInterns != other.numberOfInterns)
        return numberOfInterns > other.numberOfInterns; // giảm dần
    return code < other.code; // tăng dần
}

std::ostream &operator<<(std::ostream &os, const Enterprise &enterprise) {
    using namespace std;
    os
            << enterprise.code << " "
            << enterprise.name << " "
            << enterprise.numberOfInterns;
    return os;
}
