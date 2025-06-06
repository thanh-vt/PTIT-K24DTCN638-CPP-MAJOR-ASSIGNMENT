#ifndef K24DTCN638_VUTATTHANH_BT42_H
#define K24DTCN638_VUTATTHANH_BT42_H

struct Student {
    Student(const std::string &code, const std::string &fullname, const std::string &clazz, const std::string &email);
    friend std::ostream& operator<<(std::ostream& os, const Student& student);
    std::string code;
    std::string fullname;
    std::string clazz;
    std::string email;
};

#endif //K24DTCN638_VUTATTHANH_BT42_H
