#ifndef B_21_H
#define B_21_H
#include <string>
#include "util.h"

struct Staff {
    Staff(std::string fullname, Gender gender, const std::tm &date_of_birth, std::string address,
             std::string tax_code, const std::tm &contract_sign_date);

    friend std::ostream &operator<<(std::ostream &os, const Staff &staff);

    std::string code;
    std::string fullname;
    Gender gender; // 1 nam 2 nu
    std::tm dateOfBirth;
    std::string address;
    std::string taxCode;
    std::tm contractSignDate;
};

#endif //B_21_H
