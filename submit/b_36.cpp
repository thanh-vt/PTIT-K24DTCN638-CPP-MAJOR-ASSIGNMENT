#include <iomanip>
#include <ios>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <regex>
#include <ctime>
#include <exception>
#include <string>
#include "b_36.h"

int main() {
    using namespace std;
    // cerr << "b_36: DANH SÁCH SINH VIÊN - 3" << endl;
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
        if (N > 50) {
            cerr << "N phải <= 50" << endl;
            return 2;
        }
    } catch (const exception &e) {
        cerr << e.what() << endl;
        return 2;
    }
    vector<Student> S_inputs;
    for (int i = 0; i < N; i++) {
        // cerr << "Nhập họ tên của sinh viên " << i + 1 << ":" << endl;
        string fullname;
        getline(cin, line);
        try {
            fullname = normalize_and_validate_name(line, 30);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
        // cerr << "Nhập lớp của sinh viên " << i + 1 << ":" << endl;
        string clazz;
        getline(cin, line);
        try {
            clazz = validate_ptit_clazz(line);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
        // cerr << "Nhập ngày sinh của sinh viên " << i + 1 << ":" << endl;
        tm date_of_birth{};
        getline(cin, line);
        try {
            date_of_birth = parse_date(line);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
        float gpaMark = 0;
        // cerr << "Nhập điểm GPA của sinh viên " << i + 1 << ":" << endl;
        getline(cin, line);
        try {
            gpaMark = parse_float(line);
            if (gpaMark < 0) {
                cerr << "Điểm GPA phải >= 0" << endl;
                return 2;
            }
            if (gpaMark > 4) {
                cerr << "Điểm GPA phải <= 4" << endl;
                return 2;
            }
            static regex float_regex(R"(^\s*(\d+)(?:\.(\d*?))?\s*$)");
            smatch match;
            if (regex_match(line, match, float_regex)) {
                string decimal_part = match[2].str();
                if (decimal_part.size() > 2) {
                    cerr << "Điểm GPA có nhiều nhất 2 chữ số sau dấu phẩy" << endl;
                    return 2;
                }
            }
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
        const Student student(fullname, clazz, date_of_birth, gpaMark);
        S_inputs.push_back(student);
    }
    // cerr << "Kết quả:" << endl;
    sort(S_inputs.begin(), S_inputs.end());
    for (const Student& student : S_inputs) {
        cout << student << endl;
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

std::string normalize_and_validate_name(const std::string &input, int max_length) {
    using namespace std;
    stringstream ss(trim_and_validate_name(input, max_length));
    string word, result;
    while (ss >> word) {
        string normalized_word;
        bool first_char = true;
        for (size_t i = 0; i < word.length();) {
            unsigned char c = word[i];
            if (c < 128) {
                if (first_char) {
                    normalized_word += toupper(c);
                    first_char = false;
                } else {
                    normalized_word += tolower(c);
                }
                i++;
            } else {
                if ((c & 0xE0) == 0xC0) {
                    normalized_word += word.substr(i, 2);
                    i += 2;
                } else if ((c & 0xF0) == 0xE0) {
                    normalized_word += word.substr(i, 3);
                    i += 3;
                } else if ((c & 0xF8) == 0xF0) {
                    normalized_word += word.substr(i, 4);
                    i += 4;
                }
                first_char = false;
            }
        }
        if (!result.empty()) result += " ";
        result += normalized_word;
    }
    if (result.empty()) {
        throw exit_code_exception(2, "Họ tên không được bỏ trống.");
    }
    return result;
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

std::string validate_ptit_clazz(const std::string &clazz) {
    using namespace std;
    /*
     * Hệ:
     * CQ = chính quy
     * TX = từ xa
     * DC = đại học cao đẳng
     * Ngành:
     * BC = Báo chí
     * TT = Truyền thông đa phương tiện
     * PT = Công nghệ đa phương tiện
     * GA = Thiết kế và phát triển Game
     * QT = Quản trị kinh doanh
     * MR = Marketing
     * ME = Marketing (chất lượng cao)
     * QC = Quan hệ công chúng
     * TM = Thương mại điện tử
     * TC = Công nghệ tài chính - Fintech
     * KT = Kế toán
     * AC = Kế toán chất lượng cao
     * KH = Khoa học máy tính
     * KD = Kỹ thuật dữ liệu
     * CN = Công nghệ thông tin
     * CE = Công nghệ thông tin CLC
     * CC = Cử nhân Công nghệ thông tin
     * VN = Công nghệ thông tin Việt - Nhật
     * AT = An toàn thông tin
     * DT = Công nghệ kỹ thuật Điện, điện tử
     * VT = Kỹ thuật Điện tử viễn thông
     * DK = Kỹ thuật Điều khiển và Tự động hóa
     *
     */
    static regex pattern(
        R"(^[A-Z](\d){2}(CQ|TX|DC)(BC|TT|PT|GA|QT|MR|ME|QC|TM|TC|KT|AC|KH|KD|CN|CE|CC|VN|AT|DT|VT|DK)(\d){2}-[A-Z]$)");
    if (!regex_match(clazz, pattern)) {
        throw exit_code_exception(2, "Tên lớp không đúng định dạng tên lớp của PTIT: WDDXXYYDD-W trong đó W là chữ cái in hoa, D là chữ số, XX là mã hệ, YY là mã ngành đào tạo");
    }
    return clazz;
}

std::tm parse_date(const std::string &dateStr) {
    using namespace std;
    tm tm = {};
    istringstream ss(dateStr);
    ss >> get_time(&tm, "%d/%m/%Y");
    if (ss.fail()) {
        throw exit_code_exception(2, "Định dạng ngày không hợp lệ (dd/mm/yyyy).");
    }
    return tm;
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

std::string print_date(const std::tm &date) {
    using namespace std;
    ostringstream oss;
    oss << setw(2) << setfill('0') << date.tm_mday << "/"
        << setw(2) << setfill('0') << (date.tm_mon + 1) << "/"
        << setw(4) << setfill('0') << (date.tm_year + 1900);
    return oss.str();
}


Student::Student(std::string fullname, std::string clazz, const std::tm &date_of_birth, const float gpa_mark)
        : fullname(std::move(fullname)),
          clazz(std::move(clazz)),
          dateOfBirth(date_of_birth),
          gpaMark(gpa_mark) {
    using namespace std;
    ++counter;
    std::ostringstream oss;
    oss << "B20DCCN" << setw(3) << setfill('0') << counter;
    this->code = oss.str();
}

bool Student::operator<(const Student &other) const {
    return gpaMark > other.gpaMark; // gpa giảm dần
}

std::ostream &operator<<(std::ostream &os, const Student &student) {
    using namespace std;
    os
            << student.code << " "
            << student.fullname << " "
            << print_date(student.dateOfBirth) << " "
            << student.clazz << " "
            << fixed << setprecision(2) << student.gpaMark;
    return os;
}
