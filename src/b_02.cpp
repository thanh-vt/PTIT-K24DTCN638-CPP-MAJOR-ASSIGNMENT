#include <fstream>
#include <iostream>
#include "b_02.h"

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

// Function declarations
int parse_int(const std::string &line);
char parse_char(const std::string &line);
char convert_char(const char c);

int main() {
    using namespace std;
    // cerr << "b_02: CHỮ HOA – CHỮ THƯỜNG" << endl;
    string line;
    // cerr << "Nhập số bộ test T:" << endl;
    getline(cin, line);
    int T;
    try {
        T = parse_int(line);
    } catch (const exception &e) {
        cerr << e.what() << endl;
        return 2;
    }

    if (T < 1) {
        cerr << "T phải >= 1" << endl;
        return 2;
    }
    vector<char> inputs(T);
    for (int i = 0; i < T; i++) {
        // cerr << "Nhập bộ test " << i + 1 << ":" << endl;
        getline(cin, line);
        char c;
        try {
            c = parse_char(line);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
        inputs[i] = c;
    }
    // cerr << "Kết quả:" << endl;
    for (const char c: inputs) {
        cout << convert_char(c) << endl;
    }
    return 0;
}

// Function definitions
int parse_int(const std::string &line) {
    using namespace std;
    try {
        size_t pos;
        const int x = stoi(line, &pos);
        if (pos != line.size()) {
            throw exit_code_exception(2, "Chuỗi nhập có chứa các ký tự không hợp lệ");
        }
        return x;
    } catch (const invalid_argument &e) {
        throw exit_code_exception(2, "Chuỗi nhập không phải số kiểu integer hợp lệ");
    } catch (const out_of_range &e) {
        throw exit_code_exception(2, "Số vượt quá phạm vi kiểu integer");
    }
}

char parse_char(const std::string &line) {
    using namespace std;
    if (line.size() != 1) {
        throw exit_code_exception(2, "Chuỗi nhập có nhiều hơn 1 ký tự");
    }
    const char c = line[0];
    if (isalpha(c)) {
        return c;
    }
    throw exit_code_exception(2, "Chuỗi nhập không phải là một chữ cái hợp lệ");
}

char convert_char(const char c) {
    if (islower(c)) {
        return static_cast<char>(toupper(c));
    }
    if (isupper(c)) {
        return static_cast<char>(tolower(c));
    }
    return c;
}
