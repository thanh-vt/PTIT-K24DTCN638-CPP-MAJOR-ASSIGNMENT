#include <fstream>
#include <iostream>
#include <string>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT26.h"

// BIẾN ĐỔI DÃY SỐ
int main() {
    const std::string filename = "K24DTCN638_VuTatThanh_BT26.txt";
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
        int n = parse_int(line);
        if (n < 0) return 2;
        if (n > 1000) {
            std::cerr << "n phai nho hon hoac bang 1000" << std::endl;
            return 2;
        }
        if (!std::getline(file, line)) {
            std::cerr << "Khong co dong tiep theo" << std::endl;
            return 2;
        }
        std::vector<int> A = string_to_int_vector(line, n);
        int merge_count = min_merges_to_make_palindrome(A);
        std::cout << merge_count << std::endl;
    }
    file.close();

    return 0;
}

int min_merges_to_make_palindrome(std::vector<int>& arr) {
    const int n = arr.size();
    int left = 0, right = n - 1;
    int merges = 0;

    while (left < right) {
        if (arr[left] == arr[right]) {
            left++;
            right--;
        }
        else if (arr[left] < arr[right]) {
            arr[left + 1] += arr[left];
            left++;
            merges++;
        }
        else {
            arr[right - 1] += arr[right];
            right--;
            merges++;
        }
    }

    return merges;
}
