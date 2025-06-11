#include <iomanip>
#include <iostream>
#include <ostream>
#include <string>
#include <algorithm>
#include <utility>
#include <vector>
#include <sstream>
#include "b_45.h"

int main() {
    using namespace std;
    // cerr << "b_45: TÌM KIẾM GIẢNG VIÊN" << endl;
    string line;
    // cerr << "Nhập số giảng viên N:" << endl;
    int N = 0;
    getline(cin, line);
    try {
        N = parse_int(line);
    } catch (const exception &e) {
        cerr << e.what() << endl;
        return 2;
    }
    if (N < 1) {
        cerr << "N phải >= 1" << endl;
        return 2;
    }
    vector<Teacher> teachers;
    vector<string> Q_inputs;
    for (int i = 0; i < N; i++) {
        // cerr << "Nhập họ tên của giảng viên " << i + 1 << ":" << endl;
        string fullname;
        try {
            getline(cin, line);
            fullname = trim_and_validate_name(line, 50);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
        // cerr << "Nhập bộ môn của giảng viên " << i + 1 << ":" << endl;
        string subject;
        try {
            getline(cin, line);
            if (line.size() > 30) {
                cerr << "Lớp không quá 30 ký tự" << endl;
                return 2;
            }
            subject = move(line);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
        Teacher teacher(fullname, subject);
        teachers.push_back(teacher);
    }
    // cerr << "Nhập số truy vấn Q:" << endl;
    int Q = 0;
    getline(cin, line);
    try {
        Q = parse_int(line);
    } catch (const exception &e) {
        cerr << e.what() << endl;
        return 2;
    }
    if (Q < 1) {
        cerr << "Q phải >= 1" << endl;
        return 2;
    }
    for (int i = 0; i < Q; i++) {
        cerr << "Nhập chuỗi truy vấn thứ " << i + 1 << endl;
        getline(cin, line);
        if (trim(line).empty()) {
            cerr << "Chuỗi truy vẫn ko được bỏ trống" << endl;
            return 2;
        }
        Q_inputs.push_back(move(line));
    }
    // cerr << "Kết quả:" << endl;
    for (int i = 0; i < Q; ++i) {
        const string& query = Q_inputs[i];
        cout << "DANH SACH GIANG VIEN THEO TU KHOA " << query << ":" << endl;
        for (const Teacher &teacher: teachers) {
            if (teacher.is_matched(query)) {
                cout << teacher << endl;
            }
        }
    }
    return 0;
}

Teacher::Teacher(std::string fullname, std::string subject):
    fullname(std::move(fullname)), subject(std::move(subject)){
    using namespace std;
    ++counter;
    std::ostringstream oss;
    oss << "GV" << setw(2) << setfill('0') << counter;
    this->code = oss.str();
    this->shortenedSubject = shorten(this->subject);
}

bool Teacher::is_matched(const std::string &query) const {
    using namespace std;
    return to_lower(fullname).find(to_lower(query)) != string::npos;
}

std::string Teacher::shorten(const std::string &s) {
    using namespace std;
    stringstream ss(s);
    string word, result;
    while (ss >> word) {
        result += toupper(word[0]);
    }
    return result;
}

std::string Teacher::to_lower(std::string s) {
    using namespace std;
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

std::ostream &operator<<(std::ostream &os, const Teacher &teacher) {
    using namespace std;
    os
            << teacher.code << " "
            << teacher.fullname << " "
            << teacher.shortenedSubject;
    return os;
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

std::string trim(const std::string &str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

std::string trim_and_validate_name(const std::string &input, int max_length) {
    std::string trimmed = trim(input);
    if (trimmed.empty() || trimmed.size() > static_cast<size_t>(max_length)) {
        throw exit_code_exception(2, "Invalid name length");
    }
    return trimmed;
}