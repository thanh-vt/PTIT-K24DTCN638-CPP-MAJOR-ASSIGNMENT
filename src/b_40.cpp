#include <iostream>
#include <algorithm>
#include <regex>
#include <utility>
#include "util.h"
#include "b_40.h"

int main() {
    using namespace std;
    cerr << "b_40: TRẺ NHẤT – GIÀ NHẤT" << endl;
    string line;
    cerr << "Nhập số người N:" << endl;
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
        if (N > 100) {
            cerr << "N phải <= 100" << endl;
            continue;
        }
        is_valid = true;
    } while (!is_valid);
    vector<Person> P_inputs;

    for (int i = 0; i < N; i++) {
        cerr << "Nhập tên và ngày sinh của người thứ " << i + 1 << ":" << endl;
        string name;
        tm date_of_birth{};
        do {
            try {
                is_valid = false;
                getline(cin, line);
                static regex ws_re(" +");  // regex tách chuỗi bởi khoảng trắng
                sregex_token_iterator iter(line.begin(), line.end(), ws_re, -1);
                sregex_token_iterator end;
                vector<string> result(iter, end);
                if (result.size() != 2) {
                    cerr << "Chuỗi nhập phải có 2 thông tin tên và ngày sinh" << endl;
                    continue;
                }
                name = trim_and_validate_name(result.at(0), 15);
                date_of_birth = parse_date(result.at(1));
            } catch (const exception &e) {
                cerr << e.what() << endl;
                continue;
            }
            is_valid = true;
        } while (!is_valid);
        Person person(name, date_of_birth);
        P_inputs.push_back(person);
    }
    cerr << "Kết quả:" << endl;
    sort(P_inputs.begin(), P_inputs.end());
    cout << P_inputs.front() << endl;
    cout << P_inputs.back() << endl;
    return 0;
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
