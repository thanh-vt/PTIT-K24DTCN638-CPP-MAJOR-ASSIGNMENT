#include <fstream>
#include <iostream>
#include <iomanip>
#include "K24DTCN638_VuTatThanh_BT21.h"

#include <algorithm>

// CẤU TRÚC NHÂN VIÊN
int main() {
    const std::string filename = "K24DTCN638_VuTatThanh_BT21.txt";
    std::ifstream file(filename); // Mở file để đọc
    if (!file) {
        std::cerr << "Khong the mo file input " << filename << std::endl;
        return 1;
    }

    std::string fullname, genderStr, dateStr, address, taxCode, contractSignDateStr;
    if (!std::getline(file, fullname)) {
        std::cerr << "Khong co dong tiep theo" << std::endl;
        return 2;
    }
    if (!std::getline(file, genderStr)) {
        std::cerr << "Khong co dong tiep theo" << std::endl;
        return 2;
    }
    if (!std::getline(file, dateStr)) {
        std::cerr << "Khong co dong tiep theo" << std::endl;
        return 2;
    }
    if (!std::getline(file, address)) {
        std::cerr << "Khong co dong tiep theo" << std::endl;
        return 2;
    }
    if (!std::getline(file, taxCode)) {
        std::cerr << "Khong co dong tiep theo" << std::endl;
        return 2;
    }
    if (!std::getline(file, contractSignDateStr)) {
        std::cerr << "Khong co dong tiep theo" << std::endl;
        return 2;
    }
    file.close();
    try {
        Staff staff(fullname, genderStr, dateStr, address, taxCode, contractSignDateStr);
        std::cout << staff << std::endl;
    } catch (const std::exception &ex) {
        std::cerr << ex.what() << std::endl;
        return 2;
    }

    return 0;
}

Staff::Staff(const std::string &fullname, const std::string &genderStr, const std::string &dateStr,
                 const std::string &address, const std::string &taxCode, const std::string &contractSignDateStr) {
    this->code = "00001";
    this->fullname = normalize_and_validate_name(fullname, 40);
    this->gender = parse_gender(genderStr);
    this->dateOfBirth = parse_date(dateStr);
    if (address.size() > 100) {
        throw std::invalid_argument("Dia chi do dai khong vuot qua 100");
    }
    this->address = address;
    if (taxCode.size() != 10 && std::all_of(taxCode.begin(), taxCode.end(), isdigit)) {
        throw std::invalid_argument("Ma so thue phai gom 10 chu so");
    }
    this->taxCode = taxCode;
    this->contractSignDate = parse_date(contractSignDateStr);
}

std::ostream &operator<<(std::ostream &os, const Staff &staff) {
    os
    << staff.code << " "
    << staff.fullname << " "
    << print_gender(staff.gender) << " "
    << print_date(staff.dateOfBirth) << " "
    << staff.address << " "
    << staff.taxCode << " "
    << print_date(staff.contractSignDate);
   return os;
}
