#include "b_45.h"
#include <iomanip>
#include <iostream>
#include <ostream>
#include <string>
#include <algorithm>
#include <utility>
#include "util.h"

int main() {
    using namespace std;
    // cerr << "b_45: TÌM KIẾM GIẢNG VIÊN" << endl;
    string line;
    cerr << "Nhập số giảng viên N:" << endl;
    bool is_valid = false;
    int N = 0;
    do {
        getline(cin, line);
        try {
            N = parse_int(line);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            continue;
        }
        if (N < 1) {
            cerr << "N phải >= 1" << endl;
            continue;
        }
        is_valid = true;
    } while (!is_valid);
    vector<Teacher> teachers;
    vector<string> Q_inputs;
    for (int i = 0; i < N; i++) {
        cerr << "Nhập họ tên của giảng viên " << i + 1 << ":" << endl;
        string fullname;
        do {
            try {
                is_valid = false;
                getline(cin, line);
                fullname = trim_and_validate_name(line, 50);
            } catch (const exception &e) {
                cerr << e.what() << endl;
                continue;
            }
            is_valid = true;
        } while (!is_valid);
        cerr << "Nhập bộ môn của giảng viên " << i + 1 << ":" << endl;
        string subject;
        do {
            try {
                is_valid = false;
                getline(cin, line);
                if (line.size() > 30) {
                    cerr << "Lớp không quá 30 ký tự" << endl;
                    continue;
                }
                subject = move(line);
            } catch (const exception &e) {
                cerr << e.what() << endl;
                continue;
            }
            is_valid = true;
        } while (!is_valid);
        Teacher teacher(fullname, subject);
        teachers.push_back(teacher);
    }
    cerr << "Nhập số truy vấn Q:" << endl;
    int Q = 0;
    do {
        getline(cin, line);
        try {
            Q = parse_int(line);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            continue;
        }
        if (Q < 1) {
            cerr << "Q phải >= 1" << endl;
            continue;
        }
        is_valid = true;
    } while (!is_valid);
    for (int i = 0; i < Q; i++) {
        cerr << "Nhập chuỗi truy vấn thứ " << i + 1 << endl;
        do {
            is_valid = false;
            getline(cin, line);
            if (trim(line).empty()) {
                cerr << "Chuỗi truy vẫn ko được bỏ trống" << endl;
                continue;
            }
            is_valid = true;
        } while (!is_valid);
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
