#include <iostream>
#include <algorithm>
#include <regex>
#include <utility>
#include <sstream>
#include <ctime>
#include <exception>
#include <iomanip>
#include "b_40.h"

int main() {
    using namespace std;
    // cerr << "b_40: TRẺ NHẤT – GIÀ NHẤT" << endl;
    string line;
    // cerr << "Nhập số người N:" << endl;
    getline(cin, line);
    int N;
    try {
        N = parse_int(line);
        if (N < 1) {
            cerr << "N phải >= 1" << endl;
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
    vector<Person> P_inputs;
    for (int i = 0; i < N; i++) {
        // cerr << "Nhập tên và ngày sinh của người thứ " << i + 1 << ":" << endl;
        string name;
        tm date_of_birth{};
        getline(cin, line);
        try {
            static regex ws_re(" +");  // regex tách chuỗi bởi khoảng trắng
            sregex_token_iterator iter(line.begin(), line.end(), ws_re, -1);
            sregex_token_iterator end;
            vector<string> result(iter, end);
            if (result.size() != 2) {
                cerr << "Chuỗi nhập phải có 2 thông tin tên và ngày sinh" << endl;
                return 2;
            }
            name = trim_and_validate_name(result.at(0), 15);
            date_of_birth = parse_date(result.at(1));
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
        Person person(name, date_of_birth);
        P_inputs.push_back(person);
    }
    // cerr << "Kết quả:" << endl;
    sort(P_inputs.begin(), P_inputs.end());
    cout << P_inputs.front() << endl;
    cout << P_inputs.back() << endl;
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


Person::Person(std::string name, const std::tm &date_of_birth)
        : name(std::move(name)),
          dateOfBirth(date_of_birth) {
}

bool Person::operator<(const Person &other) const {
    using namespace std;
    const tm t1 = dateOfBirth;
    const tm t2 = other.dateOfBirth;
    if (t1.tm_year != t2.tm_year) return t1.tm_year > t2.tm_year;
    if (t1.tm_mon != t2.tm_mon) return t1.tm_mon > t2.tm_mon;
    if (t1.tm_mday != t2.tm_mday) return t1.tm_mday > t2.tm_mday;
    if (t1.tm_hour != t2.tm_hour) return t1.tm_hour > t2.tm_hour;
    if (t1.tm_min != t2.tm_min) return t1.tm_min > t2.tm_min;
    return t1.tm_sec > t2.tm_sec;
}

std::ostream & operator<<(std::ostream &os, const Person &person) {
    using namespace std;
    os
            << person.name;
    return os;
}
