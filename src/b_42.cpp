#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <functional>
#include "util.h"
#include "b_42.h"

int main() {
    using namespace std;
    cout << "b_42: DANH SÁCH ĐỐI TƯỢNG NHÂN VIÊN" << endl;

    string line;
    if (!getline(file, line)) {
        cerr << "Khong co dong tiep theo" << endl;
        return 2;
    }
    const int N = parse_int(line);
    if (N < 1 || N > 40) {
        cerr << "N phai lon hon 0 va nho hon 40" << endl;
        return 2;
    }
    vector<Employee> employees;

    for (int i = 0; i < N; i++) {
        string fullname, genderStr, dateOfBirthStr, address, taxCode, contractDateStr;
        if (!getline(file, fullname)) {
            cerr << "Khong co dong tiep theo" << endl;
            return 2;
        }
        if (!getline(file, genderStr)) {
            cerr << "Khong co dong tiep theo" << endl;
            return 2;
        }
        if (!getline(file, dateOfBirthStr)) {
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
        if (!getline(file, contractDateStr)) {
            cerr << "Khong co dong tiep theo" << endl;
            return 2;
        }
        try {
            Employee employee(fullname, genderStr, dateOfBirthStr, address, taxCode, contractDateStr);
            employees.push_back(employee);
        } catch (const exception &ex) {
            cerr << ex.what() << endl;
            return 2;
        }
    }

    file.close();

    // In ra danh sách nhân viên đã sắp xếp
    for (const Employee &emp: employees) {
        cout << emp << endl;
    }

    return 0;
}

Employee::Employee(const std::string &fullname, const std::string &genderStr, const std::string &dateOfBirthStr,
    const std::string &address, const std::string &taxCode, const std::string &contractDateStr) {
    using namespace std;
    ++counter;
    std::ostringstream oss;
    oss << setw(5) << setfill('0') << counter;
    this->code = oss.str();
    this->fullname = trim_and_validate_name(fullname, 40);
    this->gender = parse_gender(genderStr);
    this->dateOfBirth = parse_date(dateOfBirthStr);
    this->address = address;
    if (address.size() > 100) {
        throw invalid_argument("Dia chi khong qua 100 ky tu");
    }
    this->taxCode = validate_tax_code(taxCode);
    this->contractDate = parse_date(contractDateStr);
}

std::ostream & operator<<(std::ostream &os, const Employee &employee) {
    using namespace std;
    os
            << employee.code << " "
            << employee.fullname << " "
            << print_gender(employee.gender) << " "
            << print_date(employee.dateOfBirth) << " "
            << employee.address << " "
            << employee.taxCode << " "
            << print_date(employee.contractDate);
    return os;
}

