#ifndef K24DTCN638_VUTATTHANH_BT37_H
#define K24DTCN638_VUTATTHANH_BT37_H
#include <string>

struct Employee {
    Employee(std::string fullname, Gender gender, const std::tm &date_of_birth, std::string address,
        std::string tax_code, const std::tm &contract_sign_date);
    friend std::ostream& operator<<(std::ostream& os, const Employee& employee);
    static int counter;
    std::string code;
    std::string fullname;
    Gender gender;
    std::tm dateOfBirth;
    std::string address;
    std::string taxCode;
    std::tm contractSignDate;
    // override toán tử so sánh để sắp xếp theo điểm GPA
    bool operator <(const Employee &other) const;

};


int Employee::counter = 0;

#endif //K24DTCN638_VUTATTHANH_BT37_H
