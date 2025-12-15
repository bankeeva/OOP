#pragma once
#include <iostream>
#include <string>


class Obeder
{
private:
    std::time_t ts;
    std::string user_id;
    long long sum;
public:
    Obeder();
    void setTime(std::time_t t);
    void setUser(const std::string& ui);
    void setSum(long long summ);
    std::time_t getTime() const;
    std::string getUser() const;
    long long getSum() const;
};
