#ifndef K24DTCN638_VUTATTHANH_BT39_H
#define K24DTCN638_VUTATTHANH_BT39_H

struct Student {
    Student(const std::string &code, const std::string &fullname, const std::string &clazz,
        const std::string &subject1MarkStr, const std::string &subject2MarkStr, const std::string &subject3MarkStr);
    friend std::ostream & operator<<(std::ostream &os, const Student &student);
    std::string code;
    std::string fullname;
    std::string clazz;
    float subject1Mark;
    float subject2Mark;
    float subject3Mark;
};

#endif //K24DTCN638_VUTATTHANH_BT39_H
