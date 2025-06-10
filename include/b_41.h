#ifndef K24DTCN638_VUTATTHANH_BT41_H
#define K24DTCN638_VUTATTHANH_BT41_H

class Employee {
public:
    Employee(const std::string &fullname, const std::string &genderStr, const std::string &dateOfBirthStr,
             const std::string &address, const std::string &taxCode, const std::string &contractDateStr);
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

#endif //K24DTCN638_VUTATTHANH_BT41_H
