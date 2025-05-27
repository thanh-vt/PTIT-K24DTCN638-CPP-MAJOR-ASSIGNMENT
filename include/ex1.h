#ifndef EX1_H
#define EX1_H
#include "ui.h"


class Ex1 final : public UI {
public:
    ~Ex1();
protected:
    void process() override;
};

#endif //EX1_H
