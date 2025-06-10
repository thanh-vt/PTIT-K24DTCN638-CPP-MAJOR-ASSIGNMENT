#ifndef B_36_H
#define B_36_H

struct Student {
    Student(std::string fullname, std::string clazz, const std::tm &date_of_birth, float gpa_mark);
    friend std::ostream& operator<<(std::ostream& os, const Student& student);
    static int counter;
    std::string code;
    std::string fullname;
    std::string clazz;
    std::tm dateOfBirth;
    float gpaMark;
    // override toán tử so sánh để sắp xếp theo điểm GPA
    bool operator <(const Student &other) const;
};

int Student::counter = 0;

#endif //B_36_H
