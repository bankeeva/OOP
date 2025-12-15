#pragma once
#include "Obeder.h"
#include <iostream>


class ObederReceipt
{
private:
    std::vector<Obeder> person;
public:
    ObederReceipt() = default;
    ~ObederReceipt() = default;
    void setPerson(const Obeder& per);
    std::vector<Obeder>& getPerson();
    void calcDebt();
};
