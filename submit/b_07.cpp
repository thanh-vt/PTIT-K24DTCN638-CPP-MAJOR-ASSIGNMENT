#include <iostream>
#include <vector>
#include "b_07.h"

int main() {
    using namespace std;
    // cerr << "b_07: ƯỚC SỐ NGUYÊN TỐ" << endl;
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
    for (int i = 0; i < T; i++) {
        // cerr << "Nhập bộ test " << i + 1 << ":" << endl;
        getline(cin, line);
        long N;
        try {
            N = parse_long(line);
        } catch(const exception &e) {
            cerr << e.what() << endl;
            return 2;
        }
        if (N < 1) {
            cerr << "N phải >= 1" << endl;
            return 2;
        }
        if (N > 10000000000) {
            cerr << "N phải <= 10000000000" << endl;
            return 2;
        }
        inputs[i] = N;
    }
    // cerr << "Kết quả:" << endl;
    for (const int N: inputs) {
        print_factorization(N);
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

long parse_long(const std::string &line) {
    using namespace std;
    try {
        size_t pos;
        const long x = stol(line, &pos);
        if (pos != line.size()) {
            throw exit_code_exception(2, "Chuỗi nhập có chứa các ký tự không hợp lệ");
        }
        return x;
    } catch (const invalid_argument &e) {
        throw exit_code_exception(2, "Chuỗi nhập không phải số kiểu long hợp lệ");
    } catch (const out_of_range &e) {
        throw exit_code_exception(2, "Số vượt quá phạm vi kiểu long");
    }
}

void print_factorization(long n) {
    using namespace std;
    while (n % 2 == 0) {
        cout << 2 << " ";
        n /= 2;
    }

    for (long i = 3; i * i <= n; i += 2) {
        while (n % i == 0) {
            cout << i << " ";
            n /= i;
        }
    }

    if (n > 2) {
        cout << n;
    }

    cout << endl;
}
