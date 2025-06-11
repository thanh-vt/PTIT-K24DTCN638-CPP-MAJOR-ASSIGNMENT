#ifndef B_46_H
#define B_46_H

// Declarations for cloned utility functions/classes
class exit_code_exception;
int parse_int(const std::string &line);
// End declarations

class exit_code_exception : public std::exception {
    int code;
    std::string message;
public:
    explicit exit_code_exception(const int c, std::string m) : code(c), message(std::move(m)) {}
    int getCode() const { return code; }
    const char* what() const noexcept override {
        return message.c_str();
    }
};


int parse_int(const std::string &line);


class Enterprise {
public:
    Enterprise(std::string code, std::string name, int numberOfInterns);
    friend std::ostream &operator<<(std::ostream &os, const Enterprise &enterprise);

private:
    std::string code;
    std::string name;
    int numberOfInterns;

public:
    // override toán tử so sánh để sắp xếp theo số lượng sinh viên thực tập và mã doanh nghiệp
    bool operator <(const Enterprise &other) const;
};

#endif //B_46_H
