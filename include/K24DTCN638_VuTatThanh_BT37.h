#ifndef K24DTCN638_VUTATTHANH_BT37_H
#define K24DTCN638_VUTATTHANH_BT37_H
#include <ctime>
#include <string>

struct Employee {
    Employee(const std::string & fullname, const std::string & genderStr, const std::string & dateOfBirthStr,
        const std::string & address, const std::string & taxCode, const std::string & contractDateStr);
    friend std::ostream& operator<<(std::ostream& os, const Employee& employee);
    static int counter;
    std::string code;
    std::string fullname;
    Gender gender;
    std::tm dateOfBirth;
    std::string address;
    std::string taxCode;
    std::tm contractDate;

};


int Employee::counter = 0;

#endif //K24DTCN638_VUTATTHANH_BT37_H
