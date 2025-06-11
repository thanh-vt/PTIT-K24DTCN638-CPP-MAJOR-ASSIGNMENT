#include <iostream>
#include <ostream>
#include <string>
#include <algorithm>
#include <utility>
#include <regex>
#include <exception>
#include "b_46.h"

int main() {
    using namespace std;
    // cerr << "b_46: DANH SÁCH DOANH NGHIỆP NHẬN SINH VIÊN THỰC TẬP - 1" << endl;
    string line;
    // cerr << "Nhập số doanh nghiệp N:" << endl;
    getline(cin, line);
    int N;
    try {
        N = parse_int(line);
        if (N < 1) {
            cerr << "N phải >= 1" << endl;
            return 2;
        }
    } catch (const exception &e) {
        cerr << e.what() << endl;
        return 2;
    }
    vector<Enterprise> E_inputs;
    for (int i = 0; i < N; i++) {
        // cerr << "Nhập mã của doanh nghiệp " << i + 1 << ":" << endl;
        string code;
        try {
            getline(cin, line);
            if (line.size() > 150) {
                cerr << "Mã doanh nghiệp không quá 10 ký tự" << endl;
                return 2;
            }
            if (line.find(' ') != std::string::npos) {
                cerr << "Mã doanh nghiệp không được có khoảng trắng" << endl;
                return 2;
            }
            code = move(line);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
        // cerr << "Nhập tên của doanh nghiệp " << i + 1 << ":" << endl;
        string fullname;
        try {
            getline(cin, line);
            if (line.size() > 150) {
                cerr << "Tên doanh nghiệp không quá 150 ký tự" << endl;
                return 2;
            }
            fullname = move(line);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
        // cerr << "Nhập số sinh viên thực tập có thể nhận của doanh nghiệp " << i + 1 << ":" << endl;
        int numberOfInterns;
        try {
            getline(cin, line);
            numberOfInterns = parse_int(line);
            if (numberOfInterns > 1000) {
                cerr << "Số sinh viên có thể nhận không quá 1000" << endl;
                return 2;
            }
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
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
