#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <regex>
#include "b_49.h"

int main() {
    using namespace std;
    // cerr << "b_49: LIỆT KÊ TỪ KHÁC NHAU" << endl;
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
    for (const string& word : uniqueWords) {
        cout << word << endl;
    }
    return 0;
}


std::string to_lower(const std::string& s) {
    using namespace std;
    string result = s;
    transform(result.begin(), result.end(), result.begin(),
              [](unsigned char c){ return tolower(c); });
    return result;
}
