#include <algorithm>
#include <fstream>
#include <set>
#include <string>
#include <iostream>
#include "K24DTCN638_VuTatThanh_BT50.h"

// HỢP VÀ GIAO CỦA HAI FILE VĂN BẢN
int main() {
    using namespace std;
    // Lấy từ từ mỗi file
    set<string> s1 = collect_words_from_file("DATA1.in");
    set<string> s2 = collect_words_from_file("DATA2.in");

    // Hợp
    set<string> uni;
    set_union(s1.begin(), s1.end(), s2.begin(), s2.end(),
              inserter(uni, uni.begin()));

    // Giao
    set<string> inter;
    set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(),
                     inserter(inter, inter.begin()));

    // In hợp
    for (const string& word : uni)
        cout << word << " ";
    cout << endl;

    // In giao
    for (const string& word : inter)
        cout << word << " ";
    cout << endl;

    return 0;
}

// Hàm tách từ trong một file và lưu vào tập hợp
std::set<std::string> collect_words_from_file(const std::string& filename) {
    using namespace std;
    ifstream inFile(filename);
    set<string> wordSet;
    string word;
    while (inFile >> word) {
        wordSet.insert(word);
    }
    return wordSet;
}
