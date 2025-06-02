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
    const std::string filename = "K24DTCN638_VuTatThanh_BT32.txt";
    std::ifstream file(filename); // Mở file để đọc
    if (!file) {
        std::cerr << "Khong the mo file input " << filename << std::endl;
        return 1;
    }

    std::string line;
    if (!std::getline(file, line)) {
        std::cerr << "Khong co dong tiep theo" << std::endl;
        return 2;
    }
    const int total_tests = parse_int(line);
    if (total_tests < 1 || total_tests > 100) {
        std::cerr << "T phai lon hon hoac bang 1 va nho hon hoac bang 100" << std::endl;
        return 2;
    }
    for (int i = 0; i < total_tests; i++) {
        if (!std::getline(file, line)) {
            std::cerr << "Khong co dong tiep theo" << std::endl;
            return 2;
        }
        // Xử lý dòng đọc được
        std::regex ws_re(" +");  // tách chuỗi bởi khoảng trắng
        std::sregex_token_iterator iter(line.begin(), line.end(), ws_re, -1);
        std::sregex_token_iterator end;
        std::vector<std::string> result(iter, end);
        if (result.size() != 2) {
            std::cerr << "Input phai co 2 so n, m" << std::endl;
            return 2;
        }
        const int n = parse_int(result.at(0));
        if (n < 0) return 2;
        if (n > 100000) {
            std::cerr << "n phai nho hon hoac bang 100000" << std::endl;
            return 2;
        }
        const int m = parse_int(result.at(1));
        if (m < 0) return 2;
        if (m > 100000) {
            std::cerr << "n phai nho hon hoac bang 100000" << std::endl;
            return 2;
        }
        if (!std::getline(file, line)) {
            std::cerr << "Khong co dong tiep theo" << std::endl;
            return 2;
        }
        std::vector<int> A = string_to_int_vector(line, n);
        for (int e : A) {
            if (e > 100000) {
                std::cerr << "Phan tu cua A phai nho hon hoac bang 100000" << std::endl;
                return 2;
            }
        }

        if (!std::getline(file, line)) {
            std::cerr << "Khong co dong tiep theo" << std::endl;
            return 2;
        }
        std::vector<int> B = string_to_int_vector(line, m);
        for (int e : B) {
            if (e > 100000) {
                std::cerr << "Phan tu cua B phai nho hon hoac bang 100000" << std::endl;
                return 2;
            }
        }
        std::set<int> unionSet;  // Dùng set để loại trùng và tự sắp xếp
        std::unordered_set<int> Bset;  // Dùng để tra cứu nhanh cho intersection
        std::set<int> intersectionSet;

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

        for (int x : unionSet) std::cout << x << " ";
        std::cout << std::endl;

        for (int x : intersectionSet) std::cout << x << " ";
        std::cout << std::endl;
    }
    file.close();

    return 0;
}

// Hàm tìm hợp hai mảng đã sắp xếp
std::vector<int> find_union_array(const std::vector<int>& A, const std::vector<int>& B) {
    std::vector<int> result;
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
    std::vector<int> result;
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