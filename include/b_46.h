#ifndef B_46_H
#define B_46_H

class Enterprise {
public:
    Enterprise(std::string code, std::string name, int numberOfInterns);
    friend std::ostream &operator<<(std::ostream &os, const Enterprise &enterprise);

private:
    std::string code;
    std::string name;
    int numberOfInterns;

public:
    // override toán tử so sánh để sắp xếp theo số lượng sinh viên thực tập và mã doanh nghiệp
    bool operator <(const Enterprise &other) const;
};

#endif //B_46_H
