#ifndef B_40_H
#define B_40_H

struct Person {
    Person(std::string name, const std::tm &date_of_birth);
    friend std::ostream & operator<<(std::ostream &os, const Person &person);
    bool operator<(const Person &other) const;
    std::string name;
    std::tm dateOfBirth;
};

#endif //B_40_H
