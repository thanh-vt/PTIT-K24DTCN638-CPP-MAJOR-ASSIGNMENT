#include <fstream>
#include <iostream>
#include <iomanip>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT20.h"

// CẤU TRÚC THÍ SINH
int main() {
    using namespace std;
    const string filename = "K24DTCN638_VuTatThanh_BT20.txt";
    ifstream file(filename); // Mở file để đọc
    if (!file) {
        cerr << "Khong the mo file input " << filename << endl;
        return 1;
    }

    string fullname, dateStr, subject1MarkStr, subject2MarkStr, subject3MarkStr;
    if (!getline(file, fullname)) {
        cerr << "Khong co dong tiep theo" << endl;
        return 2;
    }
    if (!getline(file, dateStr)) {
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
    file.close();
    try {
        Candidate candidate(fullname, dateStr, subject1MarkStr, subject2MarkStr, subject3MarkStr);
        cout << candidate << endl;
    } catch (const exception &ex) {
        cerr << ex.what() << endl;
        return 2;
    }

    return 0;
}

Candidate::Candidate(const std::string &fullname, const std::string &dateStr, const std::string &subject1MarkStr,
                     const std::string &subject2MarkStr, const std::string &subject3MarkStr) {
    using namespace std;
    this->fullname = normalize_and_validate_name(fullname);
    this->dateOfBirth = parse_date(dateStr);
    this->subject1Mark = parse_float(subject1MarkStr);
    if (this->subject1Mark < 0) {
        throw invalid_argument("Diem mon 1 khong hop le");
    }
    this->subject2Mark = parse_float(subject2MarkStr);
    if (this->subject2Mark < 0) {
        throw invalid_argument("Diem mon 2 khong hop le");
    }
    this->subject3Mark = parse_float(subject3MarkStr);
    if (this->subject3Mark < 0) {
        throw invalid_argument("Diem mon 3 khong hop le");
    }
    this->totalMark = this->subject1Mark + this->subject2Mark + this->subject3Mark;
}

std::ostream &operator<<(std::ostream &os, const Candidate &candidate) {
    using namespace std;
    os
            << candidate.fullname << " "
            << print_date(candidate.dateOfBirth) << " "
            << fixed << setprecision(1) << candidate.totalMark;
    return os;
}
