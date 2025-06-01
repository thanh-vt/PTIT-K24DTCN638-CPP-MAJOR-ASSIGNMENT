#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT25.h"

// QUAY MA TRẬN
int main() {
    const std::string filename = "K24DTCN638_VuTatThanh_BT25.txt";
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
        std::regex ws_re(" +");  // ttách chuỗi bởi khoảng trắng
        std::sregex_token_iterator iter(line.begin(), line.end(), ws_re, -1);
        std::sregex_token_iterator end;
        std::vector<std::string> result(iter, end);
        if (result.size() != 2) {
            std::cerr << "Input phai co 2 so nguyen duong" << std::endl;
            return 2;
        }
        int n = parse_int(result[0]);
        if (n < 0) return 2;
        if (n > 100) {
            std::cerr << "n phai nho hon hoac bang 100" << std::endl;
            return 2;
        }
        int m = parse_int(result[1]);
        if (m < 0) return 2;
        if (m > 100) {
            std::cerr << "m phai nho hon hoac bang 100" << std::endl;
            return 2;
        }

        std::vector<std::vector<int> > A(n, std::vector<int>(m));

        if (!std::getline(file, line)) {
            std::cerr << "Khong co dong tiep theo" << std::endl;
            return 2;
        }
        const std::vector<int> arr = string_to_int_vector(line, n * m);
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < m; ++k) {
                const int e = arr[j * m + k];
                if (e > 100000) {
                    std::cerr << "Phan tu phai nho hon hoac bang 100000" << std::endl;
                    return 2;
                }
                A[j][k] = e;
            }
        }
        rotate_matrix(A, n, m);
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < m; ++k) {
                std::cout << A[j][k] << " ";
            }
        }
        std::cout << std::endl;
    }
    file.close();

    return 0;
}

void rotate_matrix(std::vector<std::vector<int>>& mat, const int n, const int m) {
    int top = 0, bottom = n - 1, left = 0, right = m - 1;

    while (top < bottom && left < right) {
        // Lưu các phần tử của lớp hiện tại
        std::vector<int> temp;

        // Top row
        for (int i = left; i < right; ++i)
            temp.push_back(mat[top][i]);

        // Right column
        for (int i = top; i < bottom; ++i)
            temp.push_back(mat[i][right]);

        // Bottom row
        for (int i = right; i > left; --i)
            temp.push_back(mat[bottom][i]);

        // Left column
        for (int i = bottom; i > top; --i)
            temp.push_back(mat[i][left]);

        // Xoay phải 1 bước
        int last = temp.back();
        temp.pop_back();
        temp.insert(temp.begin(), last);

        // Gán lại các giá trị vào ma trận
        int idx = 0;

        // Top row
        for (int i = left; i < right; ++i)
            mat[top][i] = temp[idx++];

        // Right column
        for (int i = top; i < bottom; ++i)
            mat[i][right] = temp[idx++];

        // Bottom row
        for (int i = right; i > left; --i)
            mat[bottom][i] = temp[idx++];

        // Left column
        for (int i = bottom; i > top; --i)
            mat[i][left] = temp[idx++];

        top++;
        bottom--;
        left++;
        right--;
    }
}
