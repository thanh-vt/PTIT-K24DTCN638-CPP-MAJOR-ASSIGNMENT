#include <fstream>
#include <iostream>
#include <string>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT27.h"

// CỬA SỔ TRƯỢT
int main() {
    using namespace std;
    const string filename = "K24DTCN638_VuTatThanh_BT27.txt";
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
    const int N = parse_int(line);
    if (N <= 3) {
        cerr << "N phai lon hon 3" << endl;
        return 2;
    }
    if (N >= 100) {
        cerr << "N phai nho hon 100" << endl;
        return 2;
    }
    vector<vector<int>>A(N, vector<int>(N));
    for (int j = 0; j < N; ++j) {
        if (!getline(file, line)) {
            throw runtime_error("Khong co dong tiep theo");
        }
        const vector<int> arr = string_to_int_vector(line, N);
        for (int k = 0; k < N; ++k) {
            const int e = arr[k];
            if (e < 1) {
                cerr << "Phan tu cua ma tran A phai la so nguyen duong" << endl;
                return 2;
            }
            if (e > 1000) {
                cerr << "Phan tu cua ma tran A phai nho hon hoac bang 1000" << endl;
            }
            A[j][k] = e;
        }
    }
    if (!getline(file, line)) {
        cerr << "Khong co dong tiep theo" << endl;
        return 2;
    }
    const int M = parse_int(line);
    if (M < 1) {
        cerr << "M phai lon hon 1" << endl;
        return 2;
    }
    if (M > 10) {
        cerr << "M phai nho hon 10" << endl;
        return 2;
    }
    vector<vector<int>>B(M, vector<int>(M));
    for (int j = 0; j < M; ++j) {
        if (!getline(file, line)) {
            throw runtime_error("Khong co dong tiep theo");
        }
        const vector<int> arr = string_to_int_vector(line, N);
        for (int k = 0; k < M; ++k) {
            const int e = arr[k];
            if (e < 0) {
                cerr << "Phan tu cua ma tran B phai lon hon hoac bang 0" << endl;
                return 2;
            }
            if (e > 20) {
                cerr << "Phan tu cua ma tran B phai nho hon hoac bang 20" << endl;
            }
            B[j][k] = e;
        }
    }
    file.close();
    const vector<vector<int>> result = print_convolution_matrix(A, B, M, N);
    // In ra ma trận kết quả
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << result[i][j];
            if (j < N - 1) cout << " ";
        }
        cout << endl;
    }
    return 0;
}

std::vector<std::vector<int>> print_convolution_matrix(const std::vector<std::vector<int>> &A, const std::vector<std::vector<int>> &B, const int M, const int N) {
    using namespace std;
    // Tạo ma trận kết quả
    vector<vector<int>> result(N, vector<int>(N, 0));
    // Tính tích chập
    for (int i = 0; i <= N - M; i += M) {
        for (int j = 0; j <= N - M; j += M) {
            // Lặp qua các phần tử trong cửa sổ trượt MxM
            for (int k = 0; k < M; k++) {
                for (int l = 0; l < M; l++) {
                    // Tính tích của mỗi phần tử tương ứng trong A và B
                    result[i + k][j + l] = A[i + k][j + l] * B[k][l];
                }
            }
        }
    }
    return result;
}
