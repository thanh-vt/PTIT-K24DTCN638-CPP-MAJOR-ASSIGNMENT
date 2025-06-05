#include <fstream>
#include <iostream>
#include <iomanip>
#include "K24DTCN638_VuTatThanh_BT21.h"

#include <algorithm>

// CẤU TRÚC NHÂN VIÊN
int main() {
    using namespace std;
    const string filename = "K24DTCN638_VuTatThanh_BT21.txt";
    ifstream file(filename); // Mở file để đọc
    if (!file) {
        cerr << "Khong the mo file input " << filename << endl;
        return 1;
    }

    string fullname, genderStr, dateStr, address, taxCode, contractSignDateStr;
    if (!getline(file, fullname)) {
        cerr << "Khong co dong tiep theo" << endl;
        return 2;
    }
    if (!getline(file, genderStr)) {
        cerr << "Khong co dong tiep theo" << endl;
        return 2;
    }
    if (!getline(file, dateStr)) {
        cerr << "Khong co dong tiep theo" << endl;
        return 2;
    }
    if (!getline(file, address)) {
        cerr << "Khong co dong tiep theo" << endl;
        return 2;
    }
    if (!getline(file, taxCode)) {
        cerr << "Khong co dong tiep theo" << endl;
        return 2;
    }
    if (!getline(file, contractSignDateStr)) {
        cerr << "Khong co dong tiep theo" << endl;
        return 2;
    }
    file.close();
    try {
        Staff staff(fullname, genderStr, dateStr, address, taxCode, contractSignDateStr);
        cout << staff << endl;
    } catch (const exception &ex) {
        cerr << ex.what() << endl;
        return 2;
    }

    return 0;
}

Staff::Staff(const std::string &fullname, const std::string &genderStr, const std::string &dateStr,
                 const std::string &address, const std::string &taxCode, const std::string &contractSignDateStr) {
    using namespace std;
    this->code = "00001";
    this->fullname = trim_and_validate_name(fullname, 40);
    this->gender = parse_gender(genderStr);
    this->dateOfBirth = parse_date(dateStr);
    if (address.size() > 100) {
        throw invalid_argument("Dia chi do dai khong vuot qua 100");
    }
    this->address = address;
    this->taxCode = validate_tax_code(taxCode);
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
