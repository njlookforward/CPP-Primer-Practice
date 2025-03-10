#include "Account.hpp"

double Account::_interestRate = initRate();
constexpr int Account::_period; // 有类内初始值就不用再写一遍了

void Account::rate(double newRate)
{
    _interestRate = newRate;
}

double Account::initRate()
{
    return 0.024;
}