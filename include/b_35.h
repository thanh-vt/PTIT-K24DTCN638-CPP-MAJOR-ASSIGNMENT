#ifndef K24DTCN638_VUTATTHANH_BT35_H
#define K24DTCN638_VUTATTHANH_BT35_H
#include <string>

struct Student {
    Student(std::string fullname, std::string clazz, const std::tm &date_of_birth, float gpa_mark);
    friend std::ostream& operator<<(std::ostream& os, const Student& student);
    static int counter;
    std::string code;
    std::string fullname;
    std::string clazz;
    std::tm dateOfBirth;
    float gpaMark;
};

int Student::counter = 0;

#endif //K24DTCN638_VUTATTHANH_BT35_H
