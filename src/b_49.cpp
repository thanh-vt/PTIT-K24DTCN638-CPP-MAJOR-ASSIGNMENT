#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include "b_49.h"

// LIỆT KÊ TỪ KHÁC NHAU
int main() {
    using namespace std;
    ifstream fin("VANBAN.in");
    if (!fin) {
        cerr << "Không thể mở file VANBAN.in" << endl;
        return 1;
    }
    set<string> uniqueWords;

    string line;
    while (getline(fin, line)) {
        istringstream iss(line);
        string word;
        while (iss >> word) {
            uniqueWords.insert(to_lower(word));
        }
    }

    // In ra kết quả
    for (const auto& word : uniqueWords) {
        cout << word << endl;
    }
    return 0;
}

// Hàm chuyển chuỗi về chữ thường
std::string to_lower(const std::string& s) {
    using namespace std;
    string result = s;
    transform(result.begin(), result.end(), result.begin(),
              [](unsigned char c){ return tolower(c); });
    return result;
}
