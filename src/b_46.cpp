#include <iostream>
#include <ostream>
#include <string>
#include <algorithm>
#include <utility>
#include "util.h"
#include "b_46.h"

int main() {
    using namespace std;
    // cerr << "b_46: DANH SÁCH DOANH NGHIỆP NHẬN SINH VIÊN THỰC TẬP - 1" << endl;
    string line;
    cerr << "Nhập số doanh nghiệp N:" << endl;
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
    vector<Enterprise> E_inputs;
    for (int i = 0; i < N; i++) {
        cerr << "Nhập mã của doanh nghiệp " << i + 1 << ":" << endl;
        string code;
        do {
            try {
                is_valid = false;
                getline(cin, line);
                if (line.size() > 150) {
                    cerr << "Mã doanh nghiệp không quá 10 ký tự" << endl;
                    continue;
                }

                if (line.find(' ') != std::string::npos) {
                    cerr << "Mã doanh nghiệp không được có khoảng trắng" << endl;
                    continue;
                }
                code = move(line);
            } catch (const exception &e) {
                cerr << e.what() << endl;
                continue;
            }
            is_valid = true;
        } while (!is_valid);
        cerr << "Nhập tên của doanh nghiệp " << i + 1 << ":" << endl;
        string fullname;
        do {
            try {
                is_valid = false;
                getline(cin, line);
                if (line.size() > 150) {
                    cerr << "Tên doanh nghiệp không quá 150 ký tự" << endl;
                    continue;
                }
                fullname = move(line);
            } catch (const exception &e) {
                cerr << e.what() << endl;
                continue;
            }
            is_valid = true;
        } while (!is_valid);
        cerr << "Nhập số sinh viên thực tập có thể nhận của doanh nghiệp " << i + 1 << ":" << endl;
        int numberOfInterns = 0;
        do {
            try {
                is_valid = false;
                getline(cin, line);
                numberOfInterns = parse_int(line);
                if (numberOfInterns > 1000) {
                    cerr << "Số sinh viên có thể nhận không quá 1000" << endl;
                    continue;
                }
            } catch (const exception &e) {
                cerr << e.what() << endl;
                continue;
            }
            is_valid = true;
        } while (!is_valid);
        Enterprise enterprise(code, fullname, numberOfInterns);
        E_inputs.push_back(enterprise);
    }
    // cerr << "Kết quả:" << endl;
    sort(E_inputs.begin(), E_inputs.end());
    for (int i = 0; i < N; ++i) {
        const Enterprise& enterprise = E_inputs[i];
        cout << enterprise << endl;
    }
    return 0;
}

Enterprise::Enterprise(std::string code, std::string name, const int numberOfInterns)
    : code(std::move(code)), name(std::move(name)), numberOfInterns(numberOfInterns) {
}

bool Enterprise::operator<(const Enterprise &other) const {
    if (numberOfInterns != other.numberOfInterns)
        return numberOfInterns > other.numberOfInterns; // giảm dần
    return code < other.code; // tăng dần
}

std::ostream &operator<<(std::ostream &os, const Enterprise &enterprise) {
    using namespace std;
    os
            << enterprise.code << " "
            << enterprise.name << " "
            << enterprise.numberOfInterns;
    return os;
}
