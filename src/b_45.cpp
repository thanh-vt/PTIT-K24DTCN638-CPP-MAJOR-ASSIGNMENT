#include "b_45.h"
#include <iomanip>
#include <iostream>
#include <ostream>
#include <string>
#include <algorithm>
#include "util.h"

int main() {
    using namespace std;
    cout << "b_45: TÌM KIẾM GIẢNG VIÊN" << endl;
    string line;
    if (!getline(file, line)) {
        cerr << "Khong co dong tiep theo" << endl;
        return 2;
    }
    const int total_tests = parse_int(line);
    if (total_tests < 1 || total_tests > 100) {
        cerr << "T phai lon hon hoac bang 1 va nho hon hoac bang 100" << endl;
        return 2;
    }
    vector<Teacher> teachers;
    for (int i = 0; i < total_tests; i++) {
        // Xử lý dòng đọc được
        string fullname, subject;
        if (!getline(file, fullname)) {
            cerr << "Khong co dong tiep theo" << endl;
            return 2;
        }
        if (!getline(file, subject)) {
            cerr << "Khong co dong tiep theo" << endl;
            return 2;
        }
        Teacher teacher(fullname, subject);
        teachers.push_back(teacher);
    }
    if (!getline(file, line)) {
        cerr << "Khong co dong tiep theo" << endl;
        return 2;
    }
    const int total_queries = parse_int(line);
    string query;
    for (int i = 0; i < total_queries; i++) {
        if (!getline(file, query)) {
            cerr << "Khong co dong tiep theo" << endl;
            return 2;
        }
        cout << "DANH SACH GIANG VIEN THEO TU KHOA " << query << ":" << endl;
        for (const auto &teacher: teachers) {
            if (teacher.is_matched(query)) {
                cout << teacher << endl;
            }
        }
    }
    file.close();
    return 0;
}

Teacher::Teacher(const std::string &fullname, const std::string &subject) {
    using namespace std;
    ++count;
    std::ostringstream oss;
    oss << "GV" << setw(2) << setfill('0') << Student::counter;
    this->code = oss.str();
    this->fullname = trim_and_validate_name(fullname, 50);
    if (subject.size() > 30) {
        throw invalid_argument("Bo mon khong qua 30 ky tu");
    }
    this->subject = subject;
    this->shortenedSubject = shorten(subject);
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
