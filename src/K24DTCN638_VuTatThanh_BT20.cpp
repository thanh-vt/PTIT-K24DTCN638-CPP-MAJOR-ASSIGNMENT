#include <fstream>
#include <iostream>
#include <iomanip>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT20.h"

// CẤU TRÚC THÍ SINH
int main() {
    const std::string filename = "K24DTCN638_VuTatThanh_BT20.txt";
    std::ifstream file(filename); // Mở file để đọc
    if (!file) {
        std::cerr << "Khong the mo file input " << filename << std::endl;
        return 1;
    }

    std::string fullname, dateStr, subject1MarkStr, subject2MarkStr, subject3MarkStr;
    if (!std::getline(file, fullname)) {
        std::cerr << "Khong co dong tiep theo" << std::endl;
        return 2;
    }
    if (!std::getline(file, dateStr)) {
        std::cerr << "Khong co dong tiep theo" << std::endl;
        return 2;
    }
    if (!std::getline(file, subject1MarkStr)) {
        std::cerr << "Khong co dong tiep theo" << std::endl;
        return 2;
    }
    if (!std::getline(file, subject2MarkStr)) {
        std::cerr << "Khong co dong tiep theo" << std::endl;
        return 2;
    }
    if (!std::getline(file, subject3MarkStr)) {
        std::cerr << "Khong co dong tiep theo" << std::endl;
        return 2;
    }
    file.close();
    try {
        Candidate candidate(fullname, dateStr, subject1MarkStr, subject2MarkStr, subject3MarkStr);
        std::cout << candidate << std::endl;
    } catch (const std::exception &ex) {
        std::cerr << ex.what() << std::endl;
        return 2;
    }

    return 0;
}

Candidate::Candidate(const std::string &fullname, const std::string &dateStr, const std::string &subject1MarkStr,
                     const std::string &subject2MarkStr, const std::string &subject3MarkStr) {
    this->fullname = normalize_and_validate_name(fullname);
    this->dateOfBirth = parse_date(dateStr);
    this->subject1Mark = parse_float(subject1MarkStr);
    if (this->subject1Mark < 0) {
        throw std::invalid_argument("Diem mon 1 khong hop le");
    }
    this->subject2Mark = parse_float(subject2MarkStr);
    if (this->subject2Mark < 0) {
        throw std::invalid_argument("Diem mon 2 khong hop le");
    }
    this->subject3Mark = parse_float(subject3MarkStr);
    if (this->subject3Mark < 0) {
        throw std::invalid_argument("Diem mon 3 khong hop le");
    }
    this->totalMark = this->subject1Mark + this->subject2Mark + this->subject3Mark;
}

std::ostream &operator<<(std::ostream &os, const Candidate &candidate) {
    os
            << candidate.fullname << " "
            << print_date(candidate.dateOfBirth) << " "
            << std::fixed << std::setprecision(1) << candidate.totalMark;
    return os;
}
