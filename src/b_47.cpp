#include <iostream>
#include "util.h"
#include "b_47.h"

int main() {
    using namespace std;
    cout << "b_47: LOẠI BỎ 100" << endl;

    string line;
    if (!getline(file, line)) {
        cerr << "Khong co dong tiep theo" << endl;
        return 2;
    }
    const int total_tests = parse_int(line);
    if (total_tests < 1 || total_tests > 100) {
        cerr << "T phải lon hon hoac bang 1 va nho hon hoac bang 100" << endl;
        return 2;
    }
    for (int i = 0; i < total_tests; i++) {
        // Xử lý dòng đọc được
        if (!getline(file, line)) {
            cerr << "Khong co dong tiep theo" << endl;
            return 2;
        }
        if (line.size() > 100000) {
            cerr << "Length(S) phải nho hon hoac bang 100000" << endl;
            return 2;
        }
        const int result = max_deleted_length(line);
        cout << result << endl;
    }

    file.close();

    return 0;
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
