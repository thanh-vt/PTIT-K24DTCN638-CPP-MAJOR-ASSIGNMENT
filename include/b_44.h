#ifndef B_44_H
#define B_44_H

struct Student {
    Student(std::string code, std::string fullname, std::string clazz, std::string email);
    friend std::ostream& operator<<(std::ostream& os, const Student& student);
    std::string code;
    std::string fullname;
    std::string clazz;
    std::string email;
};

void filter_students_by_major(const std::vector<Student>& students, const std::string& majorAlias);

#endif //B_44_H
