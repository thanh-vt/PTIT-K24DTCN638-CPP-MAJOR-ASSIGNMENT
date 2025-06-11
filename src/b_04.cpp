#include <complex>
#include <iostream>
#include "b_04.h"

class exit_code_exception : public std::exception {
    int code;
    std::string message;
public:
    explicit exit_code_exception(const int c, std::string m) : code(c), message(std::move(m)) {}
    int getCode() const { return code; }
    const char* what() const noexcept override {
        return message.c_str();
    }
};

// Function declarations
int parse_int(const std::string &line);
bool has_equal_odd_even_digits(int n);

int main() {
    using namespace std;
    // cerr << "b_04: CÂN BẰNG CHẴN LẺ" << endl;
    // cerr << "Nhập N:" << endl;
    string line;
    getline(cin, line);
    int N;
    try {
        N = parse_int(line);
    } catch (const exception &e) {
        cerr << e.what() << endl;
        return 2;
    }
    if (N <= 1) {
        cerr << "N phải > 1" << endl;
        return 2;
    }
    if (N >= 7) {
        cerr << "N phải < 7" << endl;
        return 2;
    }
    if (N % 2 != 0) {
        cerr << "N phải là số chẵn" << endl;
        return 2;
    }
    // cerr << "Kết quả:" << endl;
    const int start = static_cast<int>(pow(10, N - 1));
    const int end = static_cast<int>(pow(10, N)) - 1;
    int count = 0;
    for (int num = start; num <= end; ++num) {
        if (has_equal_odd_even_digits(num)) {
            count ++;
            cout << num << " ";
            if (count % 10 == 0) {
                cout << endl;
            }
        }
    }
    cout << endl;
    return 0;
}

// Function definitions
int parse_int(const std::string &line) {
    using namespace std;
    try {
        size_t pos;
        const int x = stoi(line, &pos);
        if (pos != line.size()) {
            throw exit_code_exception(2, "Chuỗi nhập có chứa các ký tự không hợp lệ");
        }
        return x;
    } catch (const invalid_argument &e) {
        throw exit_code_exception(2, "Chuỗi nhập không phải số kiểu integer hợp lệ");
    } catch (const out_of_range &e) {
        throw exit_code_exception(2, "Số vượt quá phạm vi kiểu integer");
    }
}

bool has_equal_odd_even_digits(int n) {
    int oddCount = 0, evenCount = 0;

    while (n > 0) {
        const int digit = n % 10;
        if (digit % 2 == 0)
            evenCount++;
        else
            oddCount++;
        n /= 10;
    }

    return oddCount == evenCount;
}