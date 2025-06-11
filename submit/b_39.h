#ifndef B_39_H
#define B_39_H

class exit_code_exception : public std::exception {
    int code;
    std::string message;
public:
    explicit exit_code_exception(const int c, std::string m) : code(c), message(std::move(m)) {}
    int getCode() const { return code; }
    const char* what() const noexcept override { return message.c_str(); }
};

int parse_int(const std::string &line);

float parse_float(const std::string &line);

std::string trim_and_validate_name(const std::string &input, int max_length);

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

#endif //B_39_H
