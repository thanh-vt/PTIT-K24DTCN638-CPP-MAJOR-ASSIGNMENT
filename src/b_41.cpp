#include <string>
#include <iomanip>
#include <iostream>
#include <regex>
#include <utility>
#include "util.h"
#include "b_41.h"

int main() {
    using namespace std;
    cout << "b_41: DANH SÁCH ĐỐI TƯỢNG NHÂN VIÊN" << endl;
    string line;
    cout << "Nhập số nhân viên N:" << endl;
    bool is_valid = false;
    int N = 0;
    do {
        getline(cin, line);
        try {
            N = parse_int(line);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            continue;
        }
        if (N < 1) {
            cerr << "N phải >= 1" << endl;
            continue;
        }
        if (N > 100) {
            cerr << "N phải <= 100" << endl;
            continue;
        }
        is_valid = true;
    } while (!is_valid);
    vector<Employee> E_inputs;

    for (int i = 0; i < N; i++) {
        cout << "Nhập họ tên của nhân viên " << i + 1 << ":" << endl;
        string fullname;
        do {
            try {
                is_valid = false;
                getline(cin, line);
                fullname = trim_and_validate_name(line, 40);
            } catch (const exception &e) {
                cout << e.what() << endl;
                continue;
            }
            is_valid = true;
        } while (!is_valid);
        cout << "Nhập giới tính của viên " << i + 1 << ":" << endl;
        Gender gender;
        do {
            try {
                is_valid = false;
                getline(cin, line);
                gender = parse_gender(line);
            } catch (const exception &e) {
                cout << e.what() << endl;
                continue;
            }
            is_valid = true;
        } while (!is_valid);
        cout << "Nhập ngày sinh của nhân viên " << i + 1 << ":" << endl;
        tm date_of_birth;
        do {
            try {
                is_valid = false;
                getline(cin, line);
                date_of_birth = parse_date(line);
            } catch (const exception &e) {
                cout << e.what() << endl;
                continue;
            }
            is_valid = true;
        } while (!is_valid);
        cout << "Nhập địa chỉ của nhân viên " << i + 1 << ":" << endl;
        string address;
        do {
            try {
                is_valid = false;
                getline(cin, line);
                if (line.size() > 100) {
                    cerr << "Địa chỉ phải <= 100 chữ cái" << endl;
                    continue;
                }
                address = line;
            } catch (const exception &e) {
                cout << e.what() << endl;
                continue;
            }
            is_valid = true;
        } while (!is_valid);
        string tax_code;
        cout << "Nhập mã số thuế của nhân viên " << i + 1 << ":" << endl;
        do {
            try {
                is_valid = false;
                getline(cin, line);
                tax_code = validate_tax_code(line);
            } catch (const exception &e) {
                cout << e.what() << endl;
                continue;
            }
            is_valid = true;
        } while (!is_valid);
        cout << "Nhập ngày ký hợp đồng của nhân viên " << i + 1 << ":" << endl;
        tm contract_sign_date;
        do {
            try {
                is_valid = false;
                getline(cin, line);
                contract_sign_date = parse_date(line);
            } catch (const exception &e) {
                cout << e.what() << endl;
                continue;
            }
            is_valid = true;
        } while (!is_valid);
        Employee employee(fullname, gender, date_of_birth, address, tax_code, contract_sign_date);
        E_inputs.push_back(employee);
    }
    cout << "Kết quả:" << endl;
    for (int i = 0; i < N; ++i) {
        const Employee& employee = E_inputs[i];
        cout << employee << endl;
    }
    return 0;
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
