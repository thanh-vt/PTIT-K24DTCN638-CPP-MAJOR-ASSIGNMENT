#include <iostream>
#include <string>
#include <algorithm>
#include "util.h"
#include "b_17.h"

int main() {
    using namespace std;
    cerr << "b_17: ĐẦU CUỐI GIỐNG NHAU" << endl;
    string line;
    cerr << "Nhập số bộ test T:" << endl;
    bool is_valid = false;
    int T = 0;
    do {
        getline(cin, line);
        try {
            T = parse_int(line);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            continue;
        }
        if (T < 1) {
            cerr << "T phải >= 1" << endl;
            continue;
        }
        if (T > 100) {
            cerr << "T phải <= 100" << endl;
            continue;
        }
        is_valid = true;
    } while (!is_valid);
    vector<string> s_inputs(T);
    for (int i = 0; i < T; i++) {
        cerr << "Nhập bộ test " << i + 1 << ":" << endl;
        string S;
        do {
            is_valid = false;
            getline(cin, S);
            if (S.empty()) {
                cerr << "Length(S) phải >= 1" << endl;
                continue;
            }
            if (S.size() > 1000) {
                cerr << "Length(S) phải <= 1000" << endl;
                continue;
            }
            static function<bool(char)> validate_func = [](const char c) {
                return std::islower(static_cast<unsigned char>(c));
            };
            if (!std::all_of(S.begin(), S.end(), validate_func)) {
                cerr << "k phải >= 1 và <= 26" << endl;
                continue;
            }
            s_inputs[i] = S;
            is_valid = true;
        } while (!is_valid);
    }
    cerr << "Kết quả:" << endl;
    for (int i = 0; i < T; i++) {
        const string& s = s_inputs[i];
        const int count = count_substring_begin_end_equals(s);
        cout << count << endl;
    }
    return 0;
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
