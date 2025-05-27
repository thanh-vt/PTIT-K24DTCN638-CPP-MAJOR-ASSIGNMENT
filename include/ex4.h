#ifndef EX4_H
#define EX4_H
#include "ui.h"


class Ex4 final : public UI {
public:
    ~Ex4();

protected:
    void process() override;

private:
    static bool has_equal_odd_even_digits(int n);
};


#endif //EX4_H
