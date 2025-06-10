#include <algorithm>
#include <fstream>
#include <set>
#include <string>
#include <iostream>
#include "b_50.h"

int main() {
    using namespace std;
    // cerr << "b_50: HỢP VÀ GIAO CỦA HAI FILE VĂN BẢN" << endl;
    // Lấy từ từ mỗi file
    ifstream in1File("DATA1.in");
    if (!in1File) {
        cerr << "Không thể mở file DATA1.in " << endl;
        return 1;
    }
    set<string> s1 = collect_words_from_file(in1File);
    ifstream in2File("DATA2.in");
    if (!in2File) {
        cerr << "Không thể mở file DATA2.in " << endl;
        return 1;
    }
    set<string> s2 = collect_words_from_file(in2File);

    set<string> uni;
    set_union(s1.begin(), s1.end(), s2.begin(), s2.end(),
              inserter(uni, uni.begin()));

    set<string> inter;
    set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(),
                     inserter(inter, inter.begin()));

    // cerr << "Kết quả:" << endl;
    for (const string& word : uni)
        cout << word << " ";
    cout << endl;
    for (const string& word : inter)
        cout << word << " ";
    cout << endl;

    return 0;
}

// Hàm tách từ trong một file và lưu vào tập hợp
std::set<std::string> collect_words_from_file(std::ifstream &inFile) {
    using namespace std;
    set<string> wordSet;
    string word;
    while (inFile >> word) {
        wordSet.insert(word);
    }
    return wordSet;
}
