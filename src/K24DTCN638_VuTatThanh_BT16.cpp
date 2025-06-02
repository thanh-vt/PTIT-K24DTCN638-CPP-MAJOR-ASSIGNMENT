#include <fstream>
#include <iostream>
#include <regex>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT16.h"

// NHỎ NHẤT - LỚN NHẤT
int main() {
    using namespace std;
    string filename = "K24DTCN638_VuTatThanh_BT16.txt";
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
    // Xử lý dòng đọc được
    regex ws_re(" +");  // ttách chuỗi bởi khoảng trắng
    sregex_token_iterator iter(line.begin(), line.end(), ws_re, -1);
    sregex_token_iterator end;
    vector<string> result(iter, end);
    if (result.size() != 2) {
        cerr << "Input phai co 2 so a, b" << endl;
        return 2;
    }
    int m = parse_int(result.at(0));
    int s = parse_int(result.at(1));
    if (m < 0 || s < 0) {
        return 2;
    }
    if (m > 100) {
        cerr << "m khong vuot qua 100\n";
        return 2;
    }
    if (s > 900) {
        cerr << "m khong vuot qua 900\n";
        return 2;
    }
    if (s == 0) {
        if (m == 1) cout << "0 0\n";
        else cout << "-1 -1\n";
        return 0;
    }

    if (s > 9 * m) {
        cout << "-1 -1\n";
        return 0;
    }
    cout << find_min(m, s) << " " << find_max(m, s) << endl;

    file.close();

    return 0;
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