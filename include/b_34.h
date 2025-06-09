#ifndef K24DTCN638_VUTATTHANH_BT34_H
#define K24DTCN638_VUTATTHANH_BT34_H
#include <string>

struct Student {
    Student(const std::string &fullname, const std::string &clazz, const std::string &dateStr, const std::string &gpaMarkStr);
    friend std::ostream& operator<<(std::ostream& os, const Student& student);
    static int counter;
    std::string code;
    std::string fullname;
    std::string clazz;
    std::tm dateOfBirth;
    float gpaMark;
};

int Student::counter = 0;

#endif //K24DTCN638_VUTATTHANH_BT34_H
