#ifndef K24DTCN638_VUTATTHANH_BT20_H
#define K24DTCN638_VUTATTHANH_BT20_H
#include <string>

struct Candidate {
    Candidate(std::string  fullname, const std::tm& dateOfBirth,
              float subject1Mark, float subject2Mark, float subject3Mark);
    friend std::ostream& operator<<(std::ostream& os, const Candidate& candidate);

    std::string fullname;
    std::tm dateOfBirth;
    float subject1Mark;
    float subject2Mark;
    float subject3Mark;
    float totalMark;
};

#endif //K24DTCN638_VUTATTHANH_BT20_H
