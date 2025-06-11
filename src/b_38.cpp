#include <string>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <utility>
#include <sstream>
#include <regex>
#include <exception>
#include "b_38.h"

int main() {
    using namespace std;
    // cerr << "b_38: BẢNG ĐIỂM THÀNH PHẦN - 1" << endl;
    string line;
    // cerr << "Nhập số sinh viên N:" << endl;
    getline(cin, line);
    int N;
    try {
        N = parse_int(line);
        if (N < 1) {
            cerr << "T phải >= 1" << endl;
            return 2;
        }
        if (N > 100) {
            cerr << "N phải <= 100" << endl;
            return 2;
        }
    } catch (const exception &e) {
        cerr << e.what() << endl;
        return 2;
    }
    vector<Student> S_inputs;
    for (int i = 0; i < N; i++) {
        // cerr << "Nhập mã của sinh viên " << i + 1 << ":" << endl;
        string code;
        getline(cin, line);
        try {
            if (line.size() > 15) {
                cerr << "Mã không quá 15 ký tự" << endl;
                return 2;
            }
            if (line.find(' ') != std::string::npos) {
                cerr << "Mã không được có khoảng trắng" << endl;
                return 2;
            }
            code = move(line);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
        // cerr << "Nhập họ tên của sinh viên " << i + 1 << ":" << endl;
        string fullname;
        getline(cin, line);
        try {
            fullname = trim_and_validate_name(line, 50);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
        // cerr << "Nhập lớp của sinh viên " << i + 1 << ":" << endl;
        string clazz;
        getline(cin, line);
        try {
            if (line.size() > 15) {
                cerr << "Lớp không quá 15 ký tự" << endl;
                return 2;
            }
            if (line.find(' ') != std::string::npos) {
                cerr << "Lớp không được có khoảng trắng" << endl;
                return 2;
            }
            clazz = move(line);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
        // cerr << "Nhập điểm môn 1 của sinh viên " << i + 1 << ":" << endl;
        float subject_1_mark = 0;
        getline(cin, line);
        try {
            subject_1_mark = parse_float(line);
            if (subject_1_mark < 0) {
                cerr << "Điểm môn 1 phải >= 0" << endl;
                return 2;
            }
            if (subject_1_mark > 10) {
                cerr << "Điểm môn 1 phải <= 10" << endl;
                return 2;
            }
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
        float subject_2_mark = 0;
        // cerr << "Nhập điểm môn 2 của sinh viên " << i + 1 << ":" << endl;
        getline(cin, line);
        try {
            subject_2_mark = parse_float(line);
            if (subject_2_mark < 0) {
                cerr << "Điểm môn 2 phải >= 0" << endl;
                return 2;
            }
            if (subject_2_mark > 10) {
                cerr << "Điểm môn 2 phải <= 10" << endl;
                return 2;
            }
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
        // cerr << "Nhập điểm môn 3 của sinh viên " << i + 1 << ":" << endl;
        float subject_3_mark = 0;
        getline(cin, line);
        try {
            subject_3_mark = parse_float(line);
            if (subject_3_mark < 0) {
                cerr << "Điểm môn 3 phải >= 0" << endl;
                return 2;
            }
            if (subject_3_mark > 10) {
                cerr << "Điểm môn 3 phải <= 10" << endl;
                return 2;
            }
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
        const Student student(code, fullname, clazz, subject_1_mark, subject_2_mark, subject_3_mark);
        S_inputs.push_back(student);
    }
    // cerr << "Kết quả:" << endl;
    sort(S_inputs.begin(), S_inputs.end());
    for (int i = 0; i < N; ++i) {
        const Student& student = S_inputs[i];
        cout << i + 1 << " " << student << endl;
    }
    return 0;
}

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

float parse_float(const std::string &line) {
    using namespace std;
    try {
        size_t pos;
        const float x = stof(line, &pos);
        if (pos != line.size()) {
            throw exit_code_exception(2, "Chuỗi nhập có chứa các ký tự không hợp lệ");
        }
        return x;
    } catch (const invalid_argument &e) {
        throw exit_code_exception(2, "Chuỗi nhập không phải số kiểu float hợp lệ");
    } catch (const out_of_range &e) {
        throw exit_code_exception(2, "Số vượt quá phạm vi kiểu float");
    }
}

std::string trim_and_validate_name(const std::string &input, const int max_length) {
    using namespace std;
    const string trimmed = [&input]() {
        const size_t first = input.find_first_not_of(" \t\n\r\f\v");
        if (first == string::npos)
            return string("");
        const size_t last = input.find_last_not_of(" \t\n\r\f\v");
        return input.substr(first, (last - first + 1));
    }();
    string result;
    int letterCount = 0;
    bool inSpace = false;
    for (size_t i = 0; i < trimmed.length();) {
        unsigned char c = trimmed[i];
        if (c < 128) {
            if (isalpha(c)) {
                result += c;
                letterCount++;
                inSpace = false;
            } else if (isspace(c)) {
                if (!inSpace) {
                    result += ' ';
                    inSpace = true;
                }
            } else {
                throw exit_code_exception(2, "Họ tên không được chứa ký tự khác chữ cái hoặc dấu cách.");
            }
            i++;
        } else {
            if ((c & 0xE0) == 0xC0) {
                if (i + 1 >= trimmed.length()) {
                    throw exit_code_exception(2, "Họ tên chứa ký tự Unicode không hợp lệ.");
                }
                result += trimmed.substr(i, 2);
                letterCount++;
                inSpace = false;
                i += 2;
            } else if ((c & 0xF0) == 0xE0) {
                if (i + 2 >= trimmed.length()) {
                    throw exit_code_exception(2, "Họ tên chứa ký tự Unicode không hợp lệ.");
                }
                result += trimmed.substr(i, 3);
                letterCount++;
                inSpace = false;
                i += 3;
            } else if ((c & 0xF8) == 0xF0) {
                if (i + 3 >= trimmed.length()) {
                    throw exit_code_exception(2, "Họ tên chứa ký tự Unicode không hợp lệ.");
                }
                result += trimmed.substr(i, 4);
                letterCount++;
                inSpace = false;
                i += 4;
            } else {
                throw exit_code_exception(2, "Họ tên chứa ký tự Unicode không hợp lệ.");
            }
        }
    }
    if (letterCount == 0) {
        throw exit_code_exception(2, "Họ tên không được bỏ trống.");
    }
    if (letterCount > max_length) {
        throw exit_code_exception(2, string("Họ tên vượt quá ") + to_string(max_length) + " ký tự.");
    }
    return result;
}


Student::Student(std::string code, std::string fullname, std::string clazz, const float subject1_mark,
                 const float subject2_mark, const float subject3_mark)
    : code(std::move(code)),
      fullname(std::move(fullname)),
      clazz(std::move(clazz)),
      subject1Mark(subject1_mark),
      subject2Mark(subject2_mark),
      subject3Mark(subject3_mark) {
}

bool Student::operator<(const Student &other) const {
    return code < other.code;
}

std::ostream & operator<<(std::ostream &os, const Student &student) {
    using namespace std;
    os
            << student.code << " "
            << student.fullname << " "
            << student.clazz << " "
            << fixed << setprecision(1) << student.subject1Mark << " "
            << fixed << setprecision(1) << student.subject2Mark << " "
            << fixed << setprecision(1) << student.subject3Mark;
    return os;
}
