#include <iomanip>
#include <iostream>
#include <regex>
#include "util.h"

void validation_termination() {
    using namespace std;
    // Try to get the current exception
    if (auto eptr = std::current_exception()) {
        try {
            std::rethrow_exception(eptr);
        } catch (const ExitCodeException &e) {
            cerr << e.what() << endl;
            std::exit(e.getCode());
        } catch (const exception &e) {
            cerr << e.what() << endl;
        } catch (...) {
            cerr << "Unknown exception" << endl;
        }
    }
    std::exit(EXIT_FAILURE); // fallback
}

Gender parse_gender(const std::string &genderStr) {
    using namespace std;
    if (genderStr == "Nam") {
        return MALE;
    }
    if (genderStr == "Nu") {
        return FEMALE;
    }
    throw invalid_argument("Gioi tinh khong hop le (Nam / Nu).");
}

std::string print_gender(const Gender gender) {
    switch (gender) {
        case MALE:
            return "Nam";
        case FEMALE:
            return "Nu";
        default:
            return "";
    }
}

std::string trim(const std::string &str) {
    using namespace std;
    const size_t first = str.find_first_not_of(" \t\n\r\f\v");
    if (first == string::npos)
        return ""; // Chuỗi toàn khoảng trắng
    const size_t last = str.find_last_not_of(" \t\n\r\f\v");
    return str.substr(first, (last - first + 1));
}

std::string trim_and_validate_name(const std::string &input) {
    return trim_and_validate_name(input, 50);
}

std::string trim_and_validate_name(const std::string &input, const int max_length) {
    using namespace std;
    const string trimmed = trim(input);
    string result;
    int letterCount = 0;
    bool inSpace = false;

    for (const char c: trimmed) {
        if (isalpha(c)) {
            result += c;
            letterCount++;
            inSpace = false;
        } else if (isspace(c)) {
            if (!inSpace) {
                result += ' ';
                inSpace = true;
            }
        } else {
            throw invalid_argument("Ho ten khong duoc chua ky tu khac chu cai.");
        }
    }

    if (letterCount > max_length) {
        throw length_error(string("Ho ten vuot qua ") + to_string(max_length) + " chu cai.");
    }

    return result;
}

std::string normalize_and_validate_name(const std::string &input) {
    return normalize_and_validate_name(input, 50);
}

std::string normalize_and_validate_name(const std::string &input, const int max_length) {
    using namespace std;
    stringstream ss(trim_and_validate_name(input, max_length));
    string word, result;

    while (ss >> word) {
        // Convert to lowercase
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        // Capitalize first letter
        word[0] = toupper(word[0]);
        // Append to result
        if (!result.empty()) result += " ";
        result += word;
    }
    return result;
}

bool is_leap_year(const int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}


std::tm parse_date(const std::string &dateStr, const std::string &format) {
    using namespace std;
    tm tm = {};
    istringstream ss(dateStr);
    ss >> get_time(&tm, format.c_str());

    if (ss.fail()) {
        throw invalid_argument("Dinh dang ngay khong hop le (dd/mm/yyyy).");
    }
    return tm;
}


std::tm parse_date(const std::string &dateStr) {
    return parse_date(dateStr, "%d/%m/%Y");
}

std::string print_date(const std::tm &date, const std::string &format) {
    using namespace std;
    stringstream ss;
    ss << put_time(&date, format.c_str());
    return ss.str();
}

std::string print_date(const std::tm &date) {
    return print_date(date, "%d/%m/%Y");
}

char parse_char(const std::string &line) {
    using namespace std;
    set_terminate(validation_termination);
    if (line.size() != 1) {
        throw ExitCodeException(2, "Chuoi co nhieu hon 1 ky tu");
    }
    const char c = line[0];
    if (isalpha(c)) {
        return c;
    }
    throw ExitCodeException(2, "Chuoi khong phai chu cai hop le");
}

int parse_int(const std::string &line) {
    using namespace std;
    set_terminate(validation_termination);
    try {
        return stoi(line);
    } catch (const invalid_argument &e) {
        throw ExitCodeException(2, "Chuoi khong phai so integer hop le");
    } catch (const out_of_range &e) {
        throw ExitCodeException(2, "So vuot qua pham vi integer");
    }
}

long parse_long(const std::string &line) {
    using namespace std;
    set_terminate(validation_termination);
    try {
        return stol(line);
    } catch (const invalid_argument &e) {
        throw ExitCodeException(2, "Chuoi khong phai so long hop le");
    } catch (const out_of_range &e) {
        throw ExitCodeException(2, "So vuot qua pham vi long");
    }
    return -1;
}

float parse_float(const std::string &line) {
    using namespace std;
    set_terminate(validation_termination);
    try {
        return stof(line);
    } catch (const invalid_argument &e) {
        throw ExitCodeException(2, "Chuoi khong phai so float hop le");
    } catch (const out_of_range &e) {
        throw ExitCodeException(2, "So vuot qua pham vi float");
    }
}

double parse_double(const std::string &line) {
    using namespace std;
    set_terminate(validation_termination);
    try {
        return stod(line);
    } catch (const invalid_argument &e) {
        throw ExitCodeException(2, "Chuoi khong phai so double hop le");
    } catch (const out_of_range &e) {
        throw ExitCodeException(2, "So vuot qua pham vi double");
    }
}

std::vector<int> string_to_int_vector(const std::string &s, const size_t size) {
    using namespace std;
    vector<int> result;
    istringstream iss(s);
    int number;
    while (result.size() < size && iss >> number) {
        result.push_back(number);
    }
    return result;
}

std::vector<long> string_to_long_vector(const std::string &s, const size_t size) {
    using namespace std;
    vector<long> result;
    istringstream iss(s);
    long number;
    while (result.size() < size && iss >> number) {
        result.push_back(number);
    }
    return result;
}

std::string validate_ptit_clazz(const std::string &clazz) {
    using namespace std;
    /*
     * Hệ:
     * CQ = chính quy
     * TX = từ xa
     * DC = đại học cao đẳng
     * Ngành:
     * BC = Báo chí
     * TT = Truyền thông đa phương tiện
     * PT = Công nghệ đa phương tiện
     * GA = Thiết kế và phát triển Game
     * QT = Quản trị kinh doanh
     * MR = Marketing
     * ME = Marketing (chất lượng cao)
     * QC = Quan hệ công chúng
     * TM = Thương mại điện tử
     * TC = Công nghệ tài chính - Fintech
     * KT = Kế toán
     * AC = Kế toán chất lượng cao
     * KH = Khoa học máy tính
     * KD = Kỹ thuật dữ liệu
     * CN = Công nghệ thông tin
     * CE = Công nghệ thông tin CLC
     * CC = Cử nhân Công nghệ thông tin
     * VN = Công nghệ thông tin Việt - Nhật
     * AT = An toàn thông tin
     * DT = Công nghệ kỹ thuật Điện, điện tử
     * VT = Kỹ thuật Điện tử viễn thông
     * DK = Kỹ thuật Điều khiển và Tự động hóa
     *
     */
    static regex pattern(
        R"(^[A-Z](\d){2}(CQ|TX|DC)(BC|TT|PT|GA|QT|MR|ME|QC|TM|TC|KT|AC|KH|KD|CN|CE|CC|VN|AT|DT|VT|DK)(\d){2}-[A-Z]$)");
    // use static regex to avoid regex compilation in every function call
    if (!regex_match(clazz, pattern)) {
        throw invalid_argument(
            "Ten lop khong dung dinh dang ten lop cua PTIT: WDDXXYYDD-W trong do W la chu cai in hoa, D la chu so, XX la ma he, YY la ma nganh dao tao");
    }
    return clazz;
}

std::string validate_tax_code(const std::string &taxCode) {
    using namespace std;
    if (taxCode.size() != 10 && all_of(taxCode.begin(), taxCode.end(), [](const unsigned char c){ return isdigit(c); })) {
        throw invalid_argument("Ma so thue phai gom 10 chu so");
    }
    return taxCode;
}
