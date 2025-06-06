#include <fstream>
#include <string>
#include <iomanip>
#include <iostream>
#include <functional>
#include <algorithm>
#include <regex>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT40.h"

// TRẺ NHẤT – GIÀ NHẤT
int main() {
    using namespace std;
    const string filename = "K24DTCN638_VuTatThanh_BT40.txt";
    ifstream file(filename); // Mở file để đọc
    if (!file) {
        cerr << "Khong the mo file input " << filename << endl;
        return 1;
    }
    string line;
    if (!getline(file, line)) {
        cerr << "Khong co dong tiep theo" << endl;
        return 2;
    }
    const int N = parse_int(line);
    if (N < 1 || N > 40) {
        cerr << "N phai lon hon 0 va nho hon 40" << endl;
        return 2;
    }
    vector<Person> people;

    regex ws_re(" +");  // regex tách chuỗi bởi khoảng trắng
    for (int i = 0; i < N; i++) {
        // Xử lý dòng đọc được
        if (!getline(file, line)) {
            cerr << "Khong co dong tiep theo" << endl;
            return 2;
        }
        sregex_token_iterator iter(line.begin(), line.end(), ws_re, -1);
        sregex_token_iterator end;
        vector<string> result(iter, end);
        if (result.size() != 2) {
            cerr << "Input phai co 2 chuoi con" << endl;
            return 2;
        }
        const string& name = result.at(0);
        const string& dateOfBirthStr = result.at(1);
        try {
            Person person(name, dateOfBirthStr);
            people.push_back(person);
        } catch (const exception &ex) {
            cerr << ex.what() << endl;
            return 2;
        }
    }

    function<bool(const Person&, const Person&)> compare_birth_date = [](const Person &p1, const Person &p2) {
        using namespace std;
        const tm t1 = p1.dateOfBirth;
        const tm t2 = p2.dateOfBirth;
        // Compare year
        if (t1.tm_year != t2.tm_year) return t1.tm_year > t2.tm_year;

        // Compare month
        if (t1.tm_mon != t2.tm_mon) return t1.tm_mon > t2.tm_mon;

        // Compare day
        if (t1.tm_mday != t2.tm_mday) return t1.tm_mday > t2.tm_mday;

        // Compare hour
        if (t1.tm_hour != t2.tm_hour) return t1.tm_hour > t2.tm_hour;

        // Compare minute
        if (t1.tm_min != t2.tm_min) return t1.tm_min > t2.tm_min;

        // Compare second
        return t1.tm_sec > t2.tm_sec;
    };

    // Sắp xếp theo ngày sinh từ trẻ nhất đến già nhất
    sort(people.begin(), people.end(), compare_birth_date);

    file.close();
    cout << people.front() << endl;
    cout << people.back() << endl;

    return 0;
}

Person::Person(const std::string &name, const std::string &dateOfBirthStr) {
    using namespace std;
    this->name = trim_and_validate_name(name, 15);
    this->dateOfBirth = parse_date(dateOfBirthStr);
}

std::ostream &operator<<(std::ostream &os, const Person &person) {
    using namespace std;
    os
            << person.name;
    return os;
}
