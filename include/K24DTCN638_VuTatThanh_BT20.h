#ifndef K24DTCN638_VUTATTHANH_BT20_H
#define K24DTCN638_VUTATTHANH_BT20_H
#include <string>
#include "util.h"

class ThiSinh {
public:
    ThiSinh(const std::string &ho_ten, const std::string &ngay_sinh, const float diem1, const float diem2, const float diem3,
        const float tong_diem)
        : hoTen(normalize_and_validate_name(ho_ten)),
          ngaySinh(validate_date(ngay_sinh)),
          diem1(diem1),
          diem2(diem2),
          diem3(diem3),
          tongDiem(tong_diem) {

    }

private:
    std::string hoTen;
    std::tm ngaySinh;
    float diem1;
    float diem2;
    float diem3;
    float tongDiem;
};

#endif //K24DTCN638_VUTATTHANH_BT20_H
