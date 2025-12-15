#include "Obeder.h"
#include <iostream>
#include <string>


Obeder::Obeder() : ts(0), user_id(" "), sum(0) {}

void Obeder::setTime(const std::time_t t)
{
    this->ts = t;
}

void Obeder::setUser(const std::string& ui)
{
    this->user_id = ui;
}

void Obeder::setSum(const long long summ)
{
    this->sum = summ;
}

std::time_t Obeder::getTime() const{
    return this->ts;
}

std::string Obeder::getUser() const{
    return this->user_id;
}

long long Obeder::getSum() const{
    return this->sum;
}
