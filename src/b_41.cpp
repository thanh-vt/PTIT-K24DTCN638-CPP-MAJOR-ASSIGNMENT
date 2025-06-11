#include <string>
#include <iomanip>
#include <iostream>
#include <regex>
#include <utility>
#include <exception>
#include "b_41.h"

int main() {
    using namespace std;
    // cerr << "b_41: DANH SÁCH ĐỐI TƯỢNG NHÂN VIÊN" << endl;
    string line;
    // cerr << "Nhập số nhân viên N:" << endl;
    getline(cin, line);
    int N;
    try {
        N = parse_int(line);
        if (N < 1) {
            cerr << "N phải >= 1" << endl;
            return 2;
        }
    } catch (const exception &e) {
        cerr << e.what() << endl;
        return 2;
    }
    vector<Employee> E_inputs;
    for (int i = 0; i < N; i++) {
        // cerr << "Nhập họ tên nhân viên " << i + 1 << ":" << endl;
        string fullname;
        getline(cin, line);
        try {
            fullname = trim_and_validate_name(line, 40);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
        // cerr << "Nhập giới tính nhân viên " << i + 1 << ":" << endl;
        Gender gender;
        getline(cin, line);
        try {
            gender = parse_gender(line);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
        // cerr << "Nhập ngày sinh nhân viên " << i + 1 << ":" << endl;
        tm date_of_birth;
        getline(cin, line);
        try {
            date_of_birth = parse_date(line);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
        // cerr << "Nhập địa chỉ nhân viên " << i + 1 << ":" << endl;
        string address;
        getline(cin, line);
        try {
            if (line.size() > 150) {
                cerr << "Địa chỉ không quá 150 ký tự" << endl;
                return 2;
            }
            address = move(line);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
        // cerr << "Nhập mã số thuế nhân viên " << i + 1 << ":" << endl;
        string tax_code;
        getline(cin, line);
        try {
            tax_code = validate_tax_code(line);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
        // cerr << "Nhập ngày ký hợp đồng nhân viên " << i + 1 << ":" << endl;
        tm contract_sign_date;
        getline(cin, line);
        try {
            contract_sign_date = parse_date(line);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
        Employee employee(fullname, gender, date_of_birth, address, tax_code, contract_sign_date);
        E_inputs.push_back(employee);
    }
    // cerr << "Kết quả:" << endl;
    for (int i = 0; i < N; ++i) {
        const Employee& employee = E_inputs[i];
        cout << employee << endl;
    }
    return 0;
}

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

std::string trim_and_validate_name(const std::string &input, const int max_length) {
    using namespace std;
    const string trimmed = [&input]() {
        const size_t first = input.find_first_not_of(" \t\n\r\f\v");
        if (first == string::npos)
            return string("");
        const size_t last = input.find_last_not_of(" \t\n\r\f\v");
        return input.substr(first, (last - first + 1));
    }();
    string result;
    int letterCount = 0;
    bool inSpace = false;
    for (size_t i = 0; i < trimmed.length();) {
        unsigned char c = trimmed[i];
        if (c < 128) {
            if (isalpha(c)) {
                result += c;
                letterCount++;
                inSpace = false;
            } else if (isspace(c)) {
                if (!inSpace) {
                    result += ' ';
                    inSpace = true;
                }
            } else {
                throw exit_code_exception(2, "Họ tên không được chứa ký tự khác chữ cái hoặc dấu cách.");
            }
            i++;
        } else {
            if ((c & 0xE0) == 0xC0) {
                if (i + 1 >= trimmed.length()) {
                    throw exit_code_exception(2, "Họ tên chứa ký tự Unicode không hợp lệ.");
                }
                result += trimmed.substr(i, 2);
                letterCount++;
                inSpace = false;
                i += 2;
            } else if ((c & 0xF0) == 0xE0) {
                if (i + 2 >= trimmed.length()) {
                    throw exit_code_exception(2, "Họ tên chứa ký tự Unicode không hợp lệ.");
                }
                result += trimmed.substr(i, 3);
                letterCount++;
                inSpace = false;
                i += 3;
            } else if ((c & 0xF8) == 0xF0) {
                if (i + 3 >= trimmed.length()) {
                    throw exit_code_exception(2, "Họ tên chứa ký tự Unicode không hợp lệ.");
                }
                result += trimmed.substr(i, 4);
                letterCount++;
                inSpace = false;
                i += 4;
            } else {
                throw exit_code_exception(2, "Họ tên chứa ký tự Unicode không hợp lệ.");
            }
        }
    }
    if (letterCount == 0) {
        throw exit_code_exception(2, "Họ tên không được bỏ trống.");
    }
    if (letterCount > max_length) {
        throw exit_code_exception(2, string("Họ tên vượt quá ") + to_string(max_length) + " ký tự.");
    }
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
    throw exit_code_exception(2, "Giới tính không hợp lệ (Nam / Nu).");
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
    static function<bool(char)> validate_func = [](const unsigned char c){ return isdigit(c); };
    if (tax_code.size() != 10 && all_of(tax_code.begin(), tax_code.end(), validate_func)) {
        throw invalid_argument("Mã số thuế phải bao gồm 10 chữ số");
    }
    return tax_code;
}


Employee::Employee(std::string fullname, Gender gender, const std::tm &date_of_birth, std::string address,
                   std::string tax_code, const std::tm &contract_sign_date)
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

std::string print_gender(Gender gender) {
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
    oss << setw(2) << setfill('0') << date.tm_mday << "/"
        << setw(2) << setfill('0') << (date.tm_mon + 1) << "/"
        << setw(4) << setfill('0') << (date.tm_year + 1900);
    return oss.str();
}
