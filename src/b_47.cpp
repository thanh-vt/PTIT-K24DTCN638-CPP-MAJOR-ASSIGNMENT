#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <regex>
#include <exception>
#include "b_47.h"


int main() {
    using namespace std;
    // cerr << "b_47: LOẠI BỎ 100" << endl;
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
    vector<string> S_inputs(T);
    for (int i = 0; i < T; i++) {
        // cerr << "Nhập bộ test " << i + 1 << ":" << endl;
        try {
            getline(cin, line);
            if (line.size() > 100000) {
                cerr << "Length(S) phải <= 100000" << endl;
                return 2;
            }
            if (!is_binary(line)) {
                cerr << "S chỉ bao gồm ký tự 0 và 1" << endl;
                return 2;
            }
            S_inputs[i] = move(line);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
    }
    // cerr << "Kết quả:" << endl;
    for (int i = 0; i < T; ++i) {
        const string& S = S_inputs[i];
        const int result = max_deleted_length(S);
        cout << result << endl;
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

bool is_binary(const std::string &str) {
    using namespace std;
    return all_of(str.begin(), str.end(), [](const char c) {
            return c == '0' || c == '1';
        });
}

int max_deleted_length(const std::string& s) {
    using namespace std;
    vector<int> mark(s.length(), 0); // đánh dấu vị trí bị xóa
    vector<char> stk;
    vector<int> pos; // lưu vị trí ký tự trong stack

    for (int i = 0; i < s.length(); ++i) {
        stk.push_back(s[i]);
        pos.push_back(i);

        // Kiểm tra xem 3 phần tử cuối stack có phải "100" không
        if (stk.size() >= 3) {
            int n = stk.size();
            if (stk[n - 3] == '1' && stk[n - 2] == '0' && stk[n - 1] == '0') {
                // Đánh dấu 3 vị trí bị xóa
                mark[pos[n - 3]] = 1;
                mark[pos[n - 2]] = 1;
                mark[pos[n - 1]] = 1;

                // Xóa khỏi stack
                stk.pop_back(); pos.pop_back();
                stk.pop_back(); pos.pop_back();
                stk.pop_back(); pos.pop_back();
            }
        }
    }

    // Tìm đoạn liên tiếp bị đánh dấu dài nhất
    int res = 0, cur = 0;
    for (int i = 0; i < s.length(); ++i) {
        if (mark[i]) {
            cur++;
            res = max(res, cur);
        } else {
            cur = 0;
        }
    }
    return res;
}
