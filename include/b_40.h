#ifndef K24DTCN638_VUTATTHANH_BT40_H
#define K24DTCN638_VUTATTHANH_BT40_H

struct Person {
    Person(std::string name, const std::tm &date_of_birth);
    friend std::ostream & operator<<(std::ostream &os, const Person &person);
    bool operator<(const Person &other) const;
    std::string name;
    std::tm dateOfBirth;
};

#endif //K24DTCN638_VUTATTHANH_BT40_H
