#include <iostream>
#include <regex>
#include <sstream>
#include <functional>
#include "b_16.h"

int main() {
    using namespace std;
    // cerr << "b_16: NHỎ NHẤT - LỚN NHẤT" << endl;
    string line;
    // cerr << "Nhập 2 số m và s:" << endl;
    getline(cin, line);
    static regex ws_re(" +");
    // tách chuỗi bởi khoảng trắng, static để tránh compile lại regex nhiều lần khi chạy chương trình
    const sregex_token_iterator iter(line.begin(), line.end(), ws_re, -1);
    const sregex_token_iterator end;
    vector<string> result(iter, end);
    if (result.size() != 2) {
        cerr << "Chuỗi nhập phải có 2 số m, s" << endl;
        return 2;
    }
    int m, s;
    try {
        m = parse_int(result.at(0));
        if (m < 1) {
            cerr << "m phải >= 1" << endl;
            return 2;
        }
        if (m > 100) {
            cerr << "m phải <= 100" << endl;
            return 2;
        }
    } catch (const exception &e) {
        cerr << e.what() << endl;
        return 2;
    }
    try {
        s = parse_int(result.at(1));
        if (s < 0) {
            cerr << "s phải >= 0" << endl;
            return 2;
        }
        if (s > 900) {
            cerr << "s phải <= 900" << endl;
            return 2;
        }
    } catch (const exception &e) {
        cerr << e.what() << endl;
        return 2;
    }
    if (s == 0) {
        if (m == 1) cerr << "0 0" << endl;
        else cerr << "-1 -1" << endl;
        return 0;
    }

    if (s > 9 * m) { // giá trị tối đa của s = 9 * m
        cerr << "-1 -1\n";
        return 0;
    }
    // cerr << "Kết quả:" << endl;
    cout << find_min(m, s) << " " << find_max(m, s) << endl;
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

std::string find_min(const int m, const int s) {
    using namespace std;
    int sum = s;
    string minNum(m, '0');
    for (int i = 0; i < m; i++) {
        for (char d = (i == 0 ? '1' : '0'); d <= '9'; d++) {
            const int digit = d - '0';
            const int maxPossible = 9 * (m - i - 1);
            if (sum - digit <= maxPossible) {
                minNum[i] = d;
                sum -= digit;
                break;
            }
        }
    }
    return minNum;
}

std::string find_max(const int m, const int s) {
    using namespace std;
    int sum = s;
    string maxNum(m, '0');
    for (int i = 0; i < m; i++) {
        for (char d = '9'; d >= '0'; d--) {
            const int digit = d - '0';
            if (sum - digit >= 0) {
                maxNum[i] = d;
                sum -= digit;
                break;
            }
        }
    }
    return maxNum;
}
