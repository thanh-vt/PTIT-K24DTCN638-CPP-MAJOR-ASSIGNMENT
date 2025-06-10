#ifndef B_42_H
#define B_42_H

struct Student {
    Student(std::string code, std::string fullname, std::string clazz, std::string email);
    friend std::ostream& operator<<(std::ostream& os, const Student& student);
    bool operator <(const Student &other) const;
    std::string code;
    std::string fullname;
    std::string clazz;
    std::string email;
};

#endif //B_42_H
