#ifndef K24DTCN638_VUTATTHANH_BT21_H
#define K24DTCN638_VUTATTHANH_BT21_H
#include <string>
#include "util.h"

struct Staff {
    Staff(const std::string &fullname, const std::string &genderStr, const std::string &dateStr,
                 const std::string &address, const std::string &taxCode, const std::string &contractSignDateStr);

    friend std::ostream &operator<<(std::ostream &os, const Staff &staff);

    std::string code;
    std::string fullname;
    Gender gender; // 1 nam 2 nu
    std::tm dateOfBirth;
    std::string address;
    std::string taxCode;
    std::tm contractSignDate;
};

#endif //K24DTCN638_VUTATTHANH_BT21_H
