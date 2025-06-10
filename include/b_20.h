#ifndef B_20_H
#define B_20_H
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

#endif //B_20_H
