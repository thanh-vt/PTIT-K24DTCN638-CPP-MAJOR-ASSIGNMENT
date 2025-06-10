#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include "util.h"
#include "b_42.h"

int main() {
    using namespace std;
    cout << "b_42: SẮP XẾP SINH VIÊN THEO LỚP" << endl;
    string line;
    cout << "Nhập số sinh viên N:" << endl;
    bool is_valid = false;
    int N = 0;
    do {
        getline(cin, line);
        try {
            N = parse_int(line);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            continue;
        }
        if (N < 1) {
            cerr << "N phải >= 1" << endl;
            continue;
        }
        if (N > 1000) {
            cerr << "N phải <= 1000" << endl;
            continue;
        }
        is_valid = true;
    } while (!is_valid);
    vector<Student> S_inputs;


    return 0;
}



