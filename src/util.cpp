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
        } catch (const exit_code_exception &e) {
            cerr << e.what() << endl;
            std::exit(e.getCode());
        } catch (const exception &e) {
            cerr << e.what() << endl;
        } catch (...) {
            cerr << "Lỗi không xác định" << endl;
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
    throw invalid_argument("Giới tính không hợp lệ (Nam / Nu).");
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

    for (size_t i = 0; i < trimmed.length();) {
        unsigned char c = trimmed[i];
        if (c < 128) { // ASCII character
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
                throw invalid_argument("Họ tên không được chứa ký tự khác chữ cái hoặc dấu cách.");
            }
            i++;
        } else {
            // Kiểm tra ký tự unicode bằng phép toán bitwise & (UTF-8)
            if ((c & 0xE0) == 0xC0) { // 2-byte unicode có dạng 110xxxxx 10xxxxxx <=> 110xxxxx(c) & 11100000(0xE0) = 11000000(0xC0)
                if (i + 1 >= trimmed.length()) {
                    throw invalid_argument("Họ tên chứa ký tự Unicode không hợp lệ.");
                }
                result += trimmed.substr(i, 2);
                letterCount++;
                inSpace = false;
                i += 2;
            } else if ((c & 0xF0) == 0xE0) { // 3-byte unicode có dạng 1110xxxx 10xxxxxx 10xxxxxx <=> 1110xxxx(c) & 11110000(0xF0) = 11100000(0xE0)
                if (i + 2 >= trimmed.length()) {
                    throw invalid_argument("Họ tên chứa ký tự Unicode không hợp lệ.");
                }
                result += trimmed.substr(i, 3);
                letterCount++;
                inSpace = false;
                i += 3;
            } else if ((c & 0xF8) == 0xF0) { // 4-byte unicode có dạng 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx <=> 11110xxx(c) & 11111000(0xF8) = 11110000(0xF0)
                if (i + 3 >= trimmed.length()) {
                    throw invalid_argument("Họ tên chứa ký tự Unicode không hợp lệ.");
                }
                result += trimmed.substr(i, 4);
                letterCount++;
                inSpace = false;
                i += 4;
            } else {
                throw invalid_argument("Họ tên chứa ký tự Unicode không hợp lệ.");
            }
        }
    }

    if (letterCount > max_length) {
        throw length_error(string("Họ tên vượt quá ") + to_string(max_length) + " ký tự.");
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
        // Handle Unicode characters
        string normalized_word;
        bool first_char = true;
        
        for (size_t i = 0; i < word.length();) {
            unsigned char c = word[i];
            if (c < 128) { // ASCII character
                if (first_char) {
                    normalized_word += toupper(c);
                    first_char = false;
                } else {
                    normalized_word += tolower(c);
                }
                i++;
            } else { // Unicode character (UTF-8)
                if ((c & 0xE0) == 0xC0) { // 2-byte sequence
                    normalized_word += word.substr(i, 2);
                    i += 2;
                } else if ((c & 0xF0) == 0xE0) { // 3-byte sequence
                    normalized_word += word.substr(i, 3);
                    i += 3;
                } else if ((c & 0xF8) == 0xF0) { // 4-byte sequence
                    normalized_word += word.substr(i, 4);
                    i += 4;
                }
                first_char = false;
            }
        }
        
        // Append to result
        if (!result.empty()) result += " ";
        result += normalized_word;
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
        throw invalid_argument("Định dạng ngày không hợp lệ (dd/mm/yyyy).");
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
        throw exit_code_exception(2, "Chuỗi nhập có nhiều hơn 1 ký tự");
    }
    const char c = line[0];
    if (isalpha(c)) {
        return c;
    }
    throw exit_code_exception(2, "Chuỗi nhập không phải là một chữ cái hợp lệ");
}

int parse_int(const std::string &line) {
    using namespace std;
    set_terminate(validation_termination);
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
    set_terminate(validation_termination);
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
    return -1;
}

float parse_float(const std::string &line) {
    using namespace std;
    set_terminate(validation_termination);
    try {
        size_t pos;
        const float x = stof(line, &pos);
        if (pos != line.size()) {
            throw exit_code_exception(2, "Chuỗi nhập có chứa các ký tự không hợp lệ");
        }
        return x;
    } catch (const invalid_argument &e) {
        throw exit_code_exception(2, "Chuỗi nhập không phải số kiểu float hợp lệ");
    } catch (const out_of_range &e) {
        throw exit_code_exception(2, "Số vượt quá phạm vi kiểu float");
    }
}

double parse_double(const std::string &line) {
    using namespace std;
    set_terminate(validation_termination);
    try {
        size_t pos;
        const double x = stod(line, &pos);
        if (pos != line.size()) {
            throw exit_code_exception(2, "Chuỗi nhập có chứa các ký tự không hợp lệ");
        }
        return x;
    } catch (const invalid_argument &e) {
        throw exit_code_exception(2, "Chuỗi nhập không phải số kiểu double hợp lệ");
    } catch (const out_of_range &e) {
        throw exit_code_exception(2, "So vuot qua pham vi double");
    }
}

std::vector<int> string_to_int_vector(const std::string &s, const size_t size) {
    return string_to_int_vector(s, size, nullptr);
}

std::vector<int> string_to_int_vector(const std::string &s, const size_t size, const std::function<std::string(int, int)>& validate_func) {
    using namespace std;
    vector<int> result;
    istringstream iss(s);
    string token;
    int pos = 0;
    while (iss >> token) {
        int number;
        try {
            number = parse_int(token);
        } catch (const exception &e) {
            throw exit_code_exception(2, "Lỗi đọc phần tử thứ " + to_string(pos + 1) + ": " + string(e.what()));
        }
        if (validate_func != nullptr) {
            string err = validate_func(pos, number);
            if (!err.empty()) {
                throw exit_code_exception(2, "Lỗi đọc phần tử thứ " + to_string(pos + 1) + ": " + err);
            }
        }
        result.push_back(number);
        pos++;
    }
    if (result.size() > size) {
        throw exit_code_exception(2, "Dòng nhập có số lượng phần tử > " + to_string(size));
    }
    if (result.size() < size) {
        throw exit_code_exception(2, "Dòng nhập có số lượng phần tử < " + to_string(size));
    }
    return result;

}

std::vector<long> string_to_long_vector(const std::string &s, const size_t size) {
    return string_to_long_vector(s, size, nullptr);
}

std::vector<long> string_to_long_vector(const std::string &s, const size_t size, const std::function<std::string(int, long)> &validate_func) {
    using namespace std;
    vector<long> result;
    istringstream iss(s);
    string token;
    int pos = 0;
    while (iss >> token) {
        long number;
        try {
            number = parse_long(token);
        } catch (const exception &e) {
            throw exit_code_exception(2, "Lỗi đọc phần tử thứ " + to_string(pos + 1) + ": " + string(e.what()));
        }
        if (validate_func != nullptr) {
            string err = validate_func(pos, number);
            if (!err.empty()) {
                throw exit_code_exception(2, "Lỗi đọc phần tử thứ " + to_string(pos + 1) + ": " + err);
            }
        }
        result.push_back(number);
        pos++;
    }
    if (result.size() > size) {
        throw exit_code_exception(2, "Dòng nhập có số lượng phần tử > " + to_string(size));
    }
    if (result.size() < size) {
        throw exit_code_exception(2, "Dòng nhập có số lượng phần tử < " + to_string(size));
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
            "Tên lớp không đúng định dạng tên lớp của PTIT: WDDXXYYDD-W trong đó W là chữ cái in hoa, D là chữ số, XX là mã hệ, YY là mã ngành đào tạo");
    }
    return clazz;
}

std::string validate_tax_code(const std::string &tax_code) {
    using namespace std;
    static function<bool(char)> validate_func = [](const unsigned char c){ return isdigit(c); };
    if (tax_code.size() != 10 && all_of(tax_code.begin(), tax_code.end(), validate_func)) {
        throw invalid_argument("Mã số thuế phải bao gồm 10 chữ số");
    }
    return tax_code;
}

std::string validate_alphanumeric(const std::string &str) {
    using namespace std;
    static function<bool(char)> validate_func = [](const unsigned char c){ return isalnum(c); };
    if (!all_of(str.begin(), str.end(), validate_func)) {
        throw invalid_argument("Chuỗi chứa ký tự không phải chữ cái hoặc chữ số");
    }
    return str;
}

std::string validate_lower_alphanumeric(const std::string &str) {
    using namespace std;
    static function<bool(char)> validate_func = [](const unsigned char c){ return islower(c) || isdigit(c); };
    if (!all_of(str.begin(), str.end(), validate_func)) {
        throw invalid_argument("Chuỗi chứa ký tự không phải chữ cái in thường hoặc chữ số");
    }
    return str;
}

std::string validate_upper_alphanumeric(const std::string &str) {
    using namespace std;
    static function<bool(char)> validate_func = [](const unsigned char c){ return isupper(c) || isdigit(c); };
    if (!all_of(str.begin(), str.end(), validate_func)) {
        throw invalid_argument("Chuỗi chứa ký tự không phải chữ cái in hoa hoặc chữ số");
    }
    return str;
}
