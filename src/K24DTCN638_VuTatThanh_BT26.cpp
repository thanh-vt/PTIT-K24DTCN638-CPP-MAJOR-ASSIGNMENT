#include <fstream>
#include <iostream>
#include <string>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT26.h"

// BIẾN ĐỔI DÃY SỐ
int main() {
    using namespace std;
    const string filename = "K24DTCN638_VuTatThanh_BT26.txt";
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
        const int n = parse_int(line);
        if (n < 1) {
            cerr << "n phai nho lon hon hoac bang 1" << endl;
            return 2;
        }
        if (n > 1000) {
            cerr << "n phai nho hon hoac bang 1000" << endl;
            return 2;
        }
        if (!getline(file, line)) {
            cerr << "Khong co dong tiep theo" << endl;
            return 2;
        }
        vector<int> A = string_to_int_vector(line, n);
        int merge_count = min_merges_to_make_palindrome(A);
        cout << merge_count << endl;
    }
    file.close();

    return 0;
}

int min_merges_to_make_palindrome(std::vector<int>& arr) {
    const unsigned long n = arr.size();
    unsigned long left = 0, right = n - 1;
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
