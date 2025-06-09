#ifndef K24DTCN638_VUTATTHANH_BT40_H
#define K24DTCN638_VUTATTHANH_BT40_H

struct Person {
    Person(const std::string &name, const std::string &dateOfBirthStr);
    friend std::ostream & operator<<(std::ostream &os, const Person &person);
    std::string name;
    std::tm dateOfBirth;
};

#endif //K24DTCN638_VUTATTHANH_BT40_H
