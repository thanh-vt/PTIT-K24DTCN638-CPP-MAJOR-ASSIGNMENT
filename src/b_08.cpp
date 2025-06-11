#include <iostream>
#include <vector>
#include "b_08.h"

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
std::vector<int> sieve(const int max);

int main() {
    using namespace std;
    // cerr << "b_08: LIỆT KÊ SỐ CÓ BA ƯỚC SỐ" << endl;
    string line;
    // cerr << "Nhập số bộ test T:" << endl;
    getline(cin, line);
    int T;
    try {
        T = parse_int(line);
    } catch(const exception &e) {
        cerr << e.what() << endl;
        return 2;
    }
    if (T < 1) {
        cerr << "T phải >= 1" << endl;
        return 2;
    }
    if (T > 100) {
        cerr << "T phải <= 100" << endl;
        return 2;
    }
    vector<int> inputs(T);
    // Dùng thuật toán sàng nguyên tố Eratosthenes để tìm các số nguyên tố đến 1000 (vì 1000^2 = 1,000,000)
    const vector<int> squares = sieve(1000);
    for (int i = 0; i < T; i++) {
        // cerr << "Nhập bộ test " << i + 1 << ":" << endl;
        getline(cin, line);
        int N;
        try {
            N = parse_int(line);
        } catch(const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
        if (N < 1) {
            cerr << "N phải >= 1" << endl;
            return 2;
        }
        if (N > 1000000) {
            cerr << "N phải <= 1000000" << endl;
            return 2;
        }
        inputs[i] = N;
    }
    // cerr << "Kết quả:" << endl;
    for (const int N: inputs) {
        bool first = true;
        for (const int x : squares) {
            if (x > N) break;
            if (!first) cout << " ";
            cout << x;
            first = false;
        }
        cout << endl;
    }
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

std::vector<int> sieve(const int max) {
    using namespace std;
    bool isPrime[max + 1];
    vector<int> squares; // Lưu p^2 với p nguyên tố
    fill(isPrime, isPrime + max + 1, true);
    isPrime[0] = isPrime[1] = false; // Số 0 và số 1 không phải số nguyên tố nên ta đánh dấu false cho hai vị trí này ngay từ đầu
    for (int i = 2; i * i <= max; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= max; j += i) {
                isPrime[j] = false;
            }
        }
    }
    for (int i = 2; i <= max; i++) {
        if (isPrime[i]) {
            squares.push_back(i * i);
        }
    }
    return squares;
}
