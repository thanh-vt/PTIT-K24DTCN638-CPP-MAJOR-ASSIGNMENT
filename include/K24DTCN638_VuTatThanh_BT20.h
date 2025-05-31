#ifndef K24DTCN638_VUTATTHANH_BT20_H
#define K24DTCN638_VUTATTHANH_BT20_H
#include <string>

struct Candidate {
    Candidate(const std::string &fullname, const std::string &dateStr,
        const std::string &subject1MarkStr, const std::string &subject2MarkStr, const std::string &subject3MarkStr);
    friend std::ostream& operator<<(std::ostream& os, const Candidate& candidate);
    std::string fullname;
    std::tm dateOfBirth;
    float subject1Mark;
    float subject2Mark;
    float subject3Mark;
    float totalMark;
};

#endif //K24DTCN638_VUTATTHANH_BT20_H
