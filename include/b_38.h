#ifndef B_38_H
#define B_38_H

struct Student {
    Student(std::string code, std::string fullname, std::string clazz, float subject1_mark,
        float subject2_mark, float subject3_mark);
    friend std::ostream & operator<<(std::ostream &os, const Student &student);
    bool operator<(const Student &other) const;
    std::string code;
    std::string fullname;
    std::string clazz;
    float subject1Mark;
    float subject2Mark;
    float subject3Mark;
};

#endif //B_38_H
