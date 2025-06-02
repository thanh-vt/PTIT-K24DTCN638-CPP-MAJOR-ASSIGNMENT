#include <fstream>
#include <iostream>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT30.h"

// TÁCH CHỮ SỐ
int main() {
    using namespace std;
    const string filename = "K24DTCN638_VuTatThanh_BT30.txt";
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
    const int total_tests = parse_int(line);
    if (total_tests < 1 || total_tests > 100) {
        cerr << "T phai lon hon hoac bang 1 va nho hon hoac bang 100" << endl;
        return 2;
    }
    for (int i = 0; i < total_tests; i++) {
        if (!getline(file, line)) {
            cerr << "Khong co dong tiep theo" << endl;
            return 2;
        }
        if (line.size() > 100000) {
            cerr << "Length(S) phai nho hon hoac bang 100000" << endl;
            return 2;
        }
        string result = calculate_result_string(line);
        cout << result << endl;
    }
    file.close();

    return 0;
}

std::string calculate_result_string(const std::string &S) {
    using namespace std;
    string result;
    // Mảng để đếm số lần xuất hiện của các chữ cái 'A'..'Z'
    vector<int> count(26, 0);
    int sum_digits = 0;

    // Duyệt qua xâu S
    for (const char c : S) {
        if (isalpha(c)) {
            count[c - 'A']++;  // Đếm số lần xuất hiện của chữ cái
        } else if (isdigit(c)) {
            sum_digits += c - '0';  // Tính tổng các chữ số
        }
    }

    // In ra các chữ cái theo thứ tự alphabet
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < count[i]; j++) {
            result += static_cast<char>(i + 'A');
        }
    }
    // Thêm tổng các chữ số vào kết quả
    result += to_string(sum_digits);
    return result;
}
