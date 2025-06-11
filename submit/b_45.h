#ifndef B_45_H
#define B_45_H

class exit_code_exception : public std::exception {
    int code;
    std::string message;
public:
    explicit exit_code_exception(const int c, std::string m) : code(c), message(std::move(m)) {}
    int getCode() const { return code; }
    const char* what() const noexcept override { return message.c_str(); }
};

int parse_int(const std::string &line);

std::string trim(const std::string &str);

std::string trim_and_validate_name(const std::string &input, int max_length);

std::string shorten(const std::string& s);

std::string toLower(std::string s);

class Teacher {
public:
    Teacher(std::string fullname, std::string subject);

    bool is_matched(const std::string &query) const;

    // Hàm chuyển bộ môn thành viết tắt
    static std::string shorten(const std::string& s);

    // Chuyển chuỗi về chữ thường
    static std::string to_lower(std::string s);

    friend std::ostream & operator<<(std::ostream &os, const Teacher &teacher);

private:
    static int counter;
    std::string code;
    std::string fullname;
    std::string subject;
    std::string shortenedSubject;
};

int Teacher::counter = 0;

#endif //B_45_H
