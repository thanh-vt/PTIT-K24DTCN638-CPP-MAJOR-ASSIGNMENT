#ifndef K24DTCN638_VUTATTHANH_BT46_H
#define K24DTCN638_VUTATTHANH_BT46_H

class Enterprise {
public:
    Enterprise(const std::string &code, const std::string &name, const std::string &numberOfInternsStr);

    friend std::ostream &operator<<(std::ostream &os, const Enterprise &enterprise);

private:
    std::string code;
    std::string name;
    int numberOfInterns;

public:
    // override toán tử so sánh để sắp xếp theo số lượng sinh viên thực tập và mã doanh nghiệp
    bool operator <(const Enterprise &other) const;
};

#endif //K24DTCN638_VUTATTHANH_BT46_H
