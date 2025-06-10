#ifndef B_41_H
#define B_41_H

class Employee {
public:
    Employee(std::string fullname, Gender gender, const std::tm &date_of_birth, std::string address,
             std::string tax_code, const std::tm &contract_sign_date);

    friend std::ostream &operator<<(std::ostream &os, const Employee &employee);
private:
    static int counter;
    std::string code;
    std::string fullname;
    Gender gender;
    std::tm dateOfBirth;
    std::string address;
    std::string taxCode;
    std::tm contractSignDate;
};


int Employee::counter = 0;

#endif //B_41_H
