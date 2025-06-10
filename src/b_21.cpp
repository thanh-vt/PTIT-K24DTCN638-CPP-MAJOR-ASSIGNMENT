#include <iostream>
#include <iomanip>
#include <utility>
#include "b_21.h"

int main() {
    using namespace std;
    cerr << "b_21: CẤU TRÚC NHÂN VIÊN" << endl;
    string line;
    bool is_valid = false;
    cerr << "Nhập tên của nhân viên:" << endl;
    string fullname;
    do {
        try {
            is_valid = false;
            getline(cin, line);
            fullname = trim_and_validate_name(line);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            continue;
        }
        is_valid = true;
    } while (!is_valid);
    cerr << "Nhập giới tính của nhân viên:" << endl;
    Gender gender;
    do {
        try {
            is_valid = false;
            getline(cin, line);
            gender = parse_gender(line);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            continue;
        }
        is_valid = true;
    } while (!is_valid);
    cerr << "Nhập ngày sinh của nhân viên:" << endl;
    tm date_of_birth;
    do {
        try {
            is_valid = false;
            getline(cin, line);
            date_of_birth = parse_date(line);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            continue;
        }
        is_valid = true;
    } while (!is_valid);
    cerr << "Nhập địa chỉ của nhân viên:" << endl;
    string address;
    do {
        is_valid = false;
        getline(cin, line);
        address = move(line);
        if (address.size() > 100) {
            cerr << "Địa chỉ có độ dài không vượt quá 100" << endl;
            continue;
        }
        is_valid = true;
    } while (!is_valid);
    cerr << "Nhập mã số thuế của nhân viên:" << endl;
    string tax_code;
    do {
        try {
            is_valid = false;
            getline(cin, line);
            tax_code = validate_tax_code(line);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            continue;
        }
        is_valid = true;
    } while (!is_valid);
    cerr << "Nhập ngày sinh của nhân viên:" << endl;
    tm contract_sign_date;
    do {
        try {
            is_valid = false;
            getline(cin, line);
            contract_sign_date = parse_date(line);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            continue;
        }
        is_valid = true;
    } while (!is_valid);
    cerr << "Kết quả:" << endl;
    Staff staff(fullname, gender, date_of_birth, address, tax_code, contract_sign_date);
    cout << staff << endl;
    return 0;
}

Staff::Staff(std::string fullname, const Gender gender, const std::tm &date_of_birth, std::string address,
             std::string tax_code, const std::tm &contract_sign_date)
    : code("00001"),
      fullname(std::move(fullname)),
      gender(gender),
      dateOfBirth(date_of_birth),
      address(std::move(address)),
      taxCode(std::move(tax_code)),
      contractSignDate(contract_sign_date) {
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
