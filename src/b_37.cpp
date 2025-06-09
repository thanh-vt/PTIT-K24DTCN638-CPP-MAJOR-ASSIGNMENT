#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include "util.h"
#include "b_37.h"

int main() {
    using namespace std;
    cout << "b_37: SẮP XẾP DANH SÁCH NHÂN VIÊN" << endl;

    string line;
    if (!getline(file, line)) {
        cerr << "Khong co dong tiep theo" << endl;
        return 2;
    }
    const int N = parse_int(line);
    if (N < 1 || N > 40) {
        cerr << "N phải lon hon 0 va nho hon 40" << endl;
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

    function<bool(const Employee&, const Employee&)> compare_birth_date = [](const Employee &e1, const Employee &e2) {
        using namespace std;
        const tm t1 = e1.dateOfBirth;
        const tm t2 = e2.dateOfBirth;
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
    };

    // Sắp xếp theo ngày sinh từ già nhất đến trẻ nhất
    sort(employees.begin(), employees.end(), compare_birth_date);

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
