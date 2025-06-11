#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <functional>
#include <vector>
#include "b_17.h"

int main() {
    using namespace std;
    // cerr << "b_17: ĐẦU CUỐI GIỐNG NHAU" << endl;
    string line;
    // cerr << "Nhập số bộ test T:" << endl;
    getline(cin, line);
    int T;
    try {
        T = parse_int(line);
        if (T < 1) {
            cerr << "T phải >= 1" << endl;
            return 2;
        }
        if (T > 100) {
            cerr << "T phải <= 100" << endl;
            return 2;
        }
    } catch (const exception &e) {
        cerr << e.what() << endl;
        return 2;
    }
    vector<string> s_inputs(T);
    for (int i = 0; i < T; i++) {
        // cerr << "Nhập bộ test " << i + 1 << ":" << endl;
        string S;
        getline(cin, S);
        if (S.empty()) {
            cerr << "Length(S) phải >= 1" << endl;
            return 2;
        }
        if (S.size() > 1000) {
            cerr << "Length(S) phải <= 1000" << endl;
            return 2;
        }
        static function<bool(char)> validate_func = [](const char c) {
            return std::islower(static_cast<unsigned char>(c));
        };
        if (!std::all_of(S.begin(), S.end(), validate_func)) {
            cerr << "k phải >= 1 và <= 26" << endl;
            return 2;
        }
        s_inputs[i] = S;
    }
    // cerr << "Kết quả:" << endl;
    for (int i = 0; i < T; i++) {
        const string& s = s_inputs[i];
        const int count = count_substring_begin_end_equals(s);
        cout << count << endl;
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

int count_substring_begin_end_equals(const std::string &S) {
    using namespace std;
    vector<int> freq(26, 0);
    for (const char c : S) {
        freq[c - 'a']++;
    }

    int result = 0;
    for (const int f : freq) {
        if (f > 0) {
            result += static_cast<int>(f) * (f + 1) / 2;
        }
    }
    return result;
}
