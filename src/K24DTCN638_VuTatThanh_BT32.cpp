#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include <set>
#include <unordered_set>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT32.h"

// HỢP VÀ GIAO CỦA HAI DÃY SỐ -2
int main() {
    using namespace std;
    const string filename = "K24DTCN638_VuTatThanh_BT32.txt";
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
        // Xử lý dòng đọc được
        regex ws_re(" +");  // tách chuỗi bởi khoảng trắng
        sregex_token_iterator iter(line.begin(), line.end(), ws_re, -1);
        sregex_token_iterator end;
        vector<string> result(iter, end);
        if (result.size() != 2) {
            cerr << "Input phai co 2 so n, m" << endl;
            return 2;
        }
        const int n = parse_int(result.at(0));
        if (n < 0) return 2;
        if (n > 100000) {
            cerr << "n phai nho hon hoac bang 100000" << endl;
            return 2;
        }
        const int m = parse_int(result.at(1));
        if (m < 0) return 2;
        if (m > 100000) {
            cerr << "n phai nho hon hoac bang 100000" << endl;
            return 2;
        }
        if (!getline(file, line)) {
            cerr << "Khong co dong tiep theo" << endl;
            return 2;
        }
        vector<int> A = string_to_int_vector(line, n);
        for (int e : A) {
            if (e > 100000) {
                cerr << "Phan tu cua A phai nho hon hoac bang 100000" << endl;
                return 2;
            }
        }

        if (!getline(file, line)) {
            cerr << "Khong co dong tiep theo" << endl;
            return 2;
        }
        vector<int> B = string_to_int_vector(line, m);
        for (int e : B) {
            if (e > 100000) {
                cerr << "Phan tu cua B phai nho hon hoac bang 100000" << endl;
                return 2;
            }
        }
        set<int> unionSet;  // Dùng set để loại trùng và tự sắp xếp
        unordered_set<int> Bset;  // Dùng để tra cứu nhanh cho intersection
        set<int> intersectionSet;

        for (int x : A) unionSet.insert(x);
        for (int x : B) {
            unionSet.insert(x);
            Bset.insert(x); // Đưa B vào unordered_set để tìm nhanh
        }

        for (int x : A) {
            if (Bset.count(x)) {
                intersectionSet.insert(x);
            }
        }

        for (int x : unionSet) cout << x << " ";
        cout << endl;

        for (int x : intersectionSet) cout << x << " ";
        cout << endl;
    }
    file.close();

    return 0;
}

// Hàm tìm hợp hai mảng đã sắp xếp
std::vector<int> find_union_array(const std::vector<int>& A, const std::vector<int>& B) {
    using namespace std;
    vector<int> result;
    int i = 0, j = 0;
    const unsigned long n = A.size();
    const unsigned long m = B.size();

    while (i < n && j < m) {
        if (A[i] < B[j]) {
            result.push_back(A[i++]);
        } else if (A[i] > B[j]) {
            result.push_back(B[j++]);
        } else {
            result.push_back(A[i]);
            ++i; ++j;
        }
    }

    while (i < n) result.push_back(A[i++]);
    while (j < m) result.push_back(B[j++]);

    return result;
}

// Hàm tìm giao hai mảng đã sắp xếp
std::vector<int> find_intersection_array(const std::vector<int>& A, const std::vector<int>& B) {
    using namespace std;
    vector<int> result;
    int i = 0, j = 0;
    const unsigned long n = A.size();
    const unsigned long m = B.size();

    while (i < n && j < m) {
        if (A[i] < B[j]) {
            ++i;
        } else if (A[i] > B[j]) {
            ++j;
        } else {
            result.push_back(A[i]);
            ++i; ++j;
        }
    }

    return result;
}