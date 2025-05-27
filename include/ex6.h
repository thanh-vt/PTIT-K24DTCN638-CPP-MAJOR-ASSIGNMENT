#ifndef EX6_H
#define EX6_H
#include "ui.h"


class Ex6 final : public UI {
public:
    ~Ex6();

protected:
    void process() override;

private:
    static bool is_prime(int n);
};


#endif //EX6_H
