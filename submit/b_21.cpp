#include <iostream>
#include <iomanip>
#include <utility>
#include <sstream>
#include <regex>
#include "b_21.h"

int main() {
    using namespace std;
    // cerr << "b_21: CẤU TRÚC NHÂN VIÊN" << endl;
    string line;
    // cerr << "Nhập tên của nhân viên:" << endl;
    getline(cin, line);
    string fullname;
    try {
        fullname = trim_and_validate_name(line);
    } catch (const exception &e) {
        cerr << e.what() << endl;
        return 2;
    }
    // cerr << "Nhập giới tính của nhân viên:" << endl;
    getline(cin, line);
    Gender gender;
    try {
        gender = parse_gender(line);
    } catch (const exception &e) {
        cerr << e.what() << endl;
        return 2;
    }
    // cerr << "Nhập ngày sinh của nhân viên:" << endl;
    getline(cin, line);
    tm date_of_birth;
    try {
        date_of_birth = parse_date(line);
    } catch (const exception &e) {
        cerr << e.what() << endl;
        return 2;
    }
    // cerr << "Nhập địa chỉ của nhân viên:" << endl;
    getline(cin, line);
    string address = move(line);
    if (address.size() > 100) {
        cerr << "Địa chỉ có độ dài không vượt quá 100" << endl;
        return 2;
    }
    // cerr << "Nhập mã số thuế của nhân viên:" << endl;
    getline(cin, line);
    string tax_code;
    try {
        tax_code = validate_tax_code(line);
    } catch (const exception &e) {
        cerr << e.what() << endl;
        return 2;
    }
    // cerr << "Nhập ngày sinh của nhân viên:" << endl;
    getline(cin, line);
    tm contract_sign_date;
    try {
        contract_sign_date = parse_date(line);
    } catch (const exception &e) {
        cerr << e.what() << endl;
        return 2;
    }
    // cerr << "Kết quả:" << endl;
    Staff staff(fullname, gender, date_of_birth, address, tax_code, contract_sign_date);
    cout << staff << endl;
    return 0;
}

// Function definitions
std::string trim_and_validate_name(const std::string &line) {
    using namespace std;
    if (line.empty()) {
        throw exit_code_exception(2, "Tên không được để trống");
    }
    if (line.size() > 100) {
        throw exit_code_exception(2, "Tên không được dài quá 100 ký tự");
    }
    static const regex name_regex("^[a-zA-Z ]+$");
    if (!regex_match(line, name_regex)) {
        throw exit_code_exception(2, "Tên chỉ được chứa chữ cái và dấu cách");
    }
    return line;
}

Gender parse_gender(const std::string &line) {
    using namespace std;
    if (line == "Nam") {
        return Gender::MALE;
    }
    if (line == "Nu") {
        return Gender::FEMALE;
    }
    throw exit_code_exception(2, "Giới tính phải là 'Nam' hoặc 'Nu'");
}

std::tm parse_date(const std::string &line) {
    using namespace std;
    static const regex date_regex("^(\\d{2})/(\\d{2})/(\\d{4})$");
    smatch matches;
    if (!regex_match(line, matches, date_regex)) {
        throw exit_code_exception(2, "Định dạng ngày không hợp lệ, yêu cầu: dd/mm/yyyy");
    }
    tm date = {};
    date.tm_mday = stoi(matches[1].str());
    date.tm_mon = stoi(matches[2].str()) - 1;
    date.tm_year = stoi(matches[3].str()) - 1900;
    if (date.tm_mday < 1 || date.tm_mday > 31) {
        throw exit_code_exception(2, "Ngày không hợp lệ");
    }
    if (date.tm_mon < 0 || date.tm_mon > 11) {
        throw exit_code_exception(2, "Tháng không hợp lệ");
    }
    if (date.tm_year < 0) {
        throw exit_code_exception(2, "Năm không hợp lệ");
    }
    return date;
}

std::string validate_tax_code(const std::string &tax_code) {
    using namespace std;
    static function<bool(char)> validate_func = [](const unsigned char c){ return isdigit(c); };
    if (tax_code.size() != 10 && all_of(tax_code.begin(), tax_code.end(), validate_func)) {
        throw invalid_argument("Mã số thuế phải bao gồm 10 chữ số");
    }
    return tax_code;
}

std::string print_gender(const Gender gender) {
    switch (gender) {
        case MALE:
            return "Nam";
        case FEMALE:
            return "Nu";
        default:
            return "";
    }
}

std::string print_date(const std::tm &date) {
    using namespace std;
    ostringstream oss;
    oss << setfill('0') << setw(2) << date.tm_mday << "/"
        << setfill('0') << setw(2) << (date.tm_mon + 1) << "/"
        << setfill('0') << setw(4) << (date.tm_year + 1900);
    return oss.str();
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
