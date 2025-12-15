#include "ObederReceipt.h"
#include <iostream>
#include <vector>


void ObederReceipt::setPerson(const Obeder& per)
{
    this->person.push_back(per);
}

std::vector<Obeder>& ObederReceipt::getPerson()
{
    return person;
}

bool compareUser(const Obeder& left, const Obeder& right)
{
    return left.getUser() <= right.getUser();
}

bool compareSum(const Obeder& left, const Obeder& right)
{
    return left.getSum() <= right.getSum();
}

void ObederReceipt::calcDebt()
{
    std::sort(this->getPerson().begin(), this->getPerson().end(), compareUser);
    int i = 0;
    while (i + 1 < this->getPerson().size())
    {
        if (this->getPerson()[i].getUser() == this->getPerson()[i + 1].getUser())
        {
            this->getPerson()[i].setSum(this->getPerson()[i].getSum() + this->getPerson()[i + 1].getSum());
            this->getPerson().erase(this->getPerson().begin() + i + 1);
        }
        else i++;
    }

    std::sort(this->getPerson().begin(), this->getPerson().end(), compareSum);
    const int len = this->getPerson().size();
    int lower = 0, upper = len - 1;
    while (lower < upper)
    {
        const long long debt = abs(std::min(this->getPerson()[lower].getSum(), this->getPerson()[upper].getSum()));
        this->getPerson()[lower].setSum(this->getPerson()[lower].getSum() + debt);
        this->getPerson()[upper].setSum(this->getPerson()[upper].getSum() - debt);

        std::cout << this->getPerson()[lower].getUser() << " -> " << this->getPerson()[upper].getUser()
        << " - " << debt / 100 << " р " << debt % 100 << " коп" << std::endl;

        if (this->getPerson()[lower].getSum() == 0) lower++;
        if (this->getPerson()[upper].getSum() == 0) upper--;
    }
}
