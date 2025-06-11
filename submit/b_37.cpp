#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <regex>
#include <ctime>
#include "b_37.h"

int main() {
    using namespace std;
    // cerr << "b_37: SẮP XẾP DANH SÁCH NHÂN VIÊN" << endl;
    string line;
    // cerr << "Nhập số nhân viên N:" << endl;
    getline(cin, line);
    int N;
    try {
        N = parse_int(line);
        if (N < 1) {
            cerr << "T phải >= 1" << endl;
            return 2;
        }
        if (N > 40) {
            cerr << "N phải <= 40" << endl;
            return 2;
        }
    } catch (const exception &e) {
        cerr << e.what() << endl;
        return 2;
    }
    vector<Employee> E_inputs;

    for (int i = 0; i < N; i++) {
        // cerr << "Nhập họ tên của nhân viên " << i + 1 << ":" << endl;
        string fullname;
        try {
            getline(cin, line);
            fullname = trim_and_validate_name(line, 40);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
        // cerr << "Nhập giới tính của nhân viên " << i + 1 << ":" << endl;
        Gender gender;
        try {
            getline(cin, line);
            gender = parse_gender(line);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
        // cerr << "Nhập ngày sinh của nhân viên " << i + 1 << ":" << endl;
        tm date_of_birth{};
        try {
            getline(cin, line);
            date_of_birth = parse_date(line);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
        // cerr << "Nhập địa chỉ của nhân viên " << i + 1 << ":" << endl;
        string address;
        try {
            getline(cin, line);
            if (line.size() > 100) {
                cerr << "Địa chỉ không quá 100 ký tự" << endl;
                return 2;
            }
            address = move(line);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
        string tax_code;
        // cerr << "Nhập mã số thuế của nhân viên " << i + 1 << ":" << endl;
        try {
            getline(cin, line);
            tax_code = validate_tax_code(line);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
        // cerr << "Nhập ngày ký hợp đồng của nhân viên " << i + 1 << ":" << endl;
        tm contract_sign_date{};
        try {
            getline(cin, line);
            contract_sign_date = parse_date(line);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
        const Employee employee(fullname, gender, date_of_birth, address, tax_code, contract_sign_date);
        E_inputs.push_back(employee);
    }
    // cerr << "Kết quả:" << endl;
    sort(E_inputs.begin(), E_inputs.end());
    for (const Employee &employee: E_inputs) {
        cout << employee << endl;
    }
    return 0;
}

// Function definitions
int parse_int(const std::string &line) {
    using namespace std;
    try {
        size_t pos;
        const int x = stoi(line, &pos);
        if (pos != line.size()) {
            throw exit_code_exception(2, "Chuỗi nhập có chứa các ký tự không hợp lệ");
        }
        return x;
    } catch (const invalid_argument &e) {
        throw exit_code_exception(2, "Chuỗi nhập không phải số kiểu integer hợp lệ");
    } catch (const out_of_range &e) {
        throw exit_code_exception(2, "Số vượt quá phạm vi kiểu integer");
    }
}

std::string trim_and_validate_name(const std::string &line, const int max_length) {
    using namespace std;
    if (line.empty()) {
        throw exit_code_exception(2, "Chuỗi nhập không được để trống");
    }
    if (line.size() > max_length) {
        throw exit_code_exception(2, "Chuỗi nhập có độ dài vượt quá " + to_string(max_length) + " ký tự");
    }
    static const regex name_regex(R"(^\s*[A-Za-z\s]+\s*$)");
    if (!regex_match(line, name_regex)) {
        throw exit_code_exception(2, "Chuỗi nhập chỉ được chứa các ký tự chữ cái và khoảng trắng");
    }
    string result = line;
    result.erase(0, result.find_first_not_of(" \t\n\r\f\v"));
    result.erase(result.find_last_not_of(" \t\n\r\f\v") + 1);
    static const regex multiple_spaces_regex(R"(\s+)");
    result = regex_replace(result, multiple_spaces_regex, " ");
    return result;
}

Gender parse_gender(const std::string &line) {
    using namespace std;
    if (line == "Nam") {
        return MALE;
    }
    if (line == "Nu") {
        return FEMALE;
    }
    throw invalid_argument("Giới tính không hợp lệ (Nam / Nu).");
}

std::tm parse_date(const std::string &dateStr) {
    using namespace std;
    tm tm = {};
    istringstream ss(dateStr);
    ss >> get_time(&tm, "%d/%m/%Y");
    if (ss.fail()) {
        throw exit_code_exception(2, "Định dạng ngày không hợp lệ (dd/mm/yyyy).");
    }
    return tm;
}

std::string validate_tax_code(const std::string &tax_code) {
    using namespace std;
    static auto validate_func = [](const unsigned char c){ return isdigit(c); };
    if (tax_code.size() != 10 || !all_of(tax_code.begin(), tax_code.end(), validate_func)) {
        throw exit_code_exception(2, "Mã số thuế phải bao gồm 10 chữ số");
    }
    return tax_code;
}

std::string print_gender(Gender gender) {
    return gender == Gender::MALE ? "Nam" : "Nu";
}

std::string print_date(const std::tm &date) {
    using namespace std;
    ostringstream oss;
    oss << setw(2) << setfill('0') << date.tm_mday << "/"
        << setw(2) << setfill('0') << (date.tm_mon + 1) << "/"
        << setw(4) << setfill('0') << (date.tm_year + 1900);
    return oss.str();
}

Employee::Employee(std::string fullname, Gender gender, const tm &date_of_birth, std::string address,
                   std::string tax_code, const tm &contract_sign_date)
    : fullname(std::move(fullname)),
      gender(gender),
      dateOfBirth(date_of_birth),
      address(std::move(address)),
      taxCode(std::move(tax_code)),
      contractSignDate(contract_sign_date) {
    using namespace std;
    ++counter;
    std::ostringstream oss;
    oss << setw(5) << setfill('0') << counter;
    this->code = oss.str();
}

bool Employee::operator<(const Employee &other) const {
    using namespace std;
    const tm t1 = dateOfBirth;
    const tm t2 = other.dateOfBirth;
    // Compare year
    if (t1.tm_year != t2.tm_year) return t1.tm_year < t2.tm_year;

    // Compare month
    if (t1.tm_mon != t2.tm_mon) return t1.tm_mon < t2.tm_mon;

    // Compare day
    if (t1.tm_mday != t2.tm_mday) return t1.tm_mday < t2.tm_mday;

    // Compare hour
    if (t1.tm_hour != t2.tm_hour) return t1.tm_hour < t2.tm_hour;

    // Compare minute
    if (t1.tm_min != t2.tm_min) return t1.tm_min < t2.tm_min;

    // Compare second
    return t1.tm_sec < t2.tm_sec;
}

std::ostream &operator<<(std::ostream &os, const Employee &employee) {
    using namespace std;
    os
            << employee.code << " "
            << employee.fullname << " "
            << print_gender(employee.gender) << " "
            << print_date(employee.dateOfBirth) << " "
            << employee.address << " "
            << employee.taxCode << " "
            << print_date(employee.contractSignDate);
    return os;
}
