#ifndef B_02_H
#define B_02_H

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

char parse_char(const std::string &line);

char convert_char(char c);

/**
 * Chuyển đổi ký tự in hoa và in thường hoặc ngược lại
 *
 * @param c Ký tự đầu vào
 * @return Ký tự đã được chuyển đổi
 */
char convert_char(char c);

#endif //B_02_H
