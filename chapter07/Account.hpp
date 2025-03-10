#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include <string>

// exercise_7_57
class Account {
public:
    Account(const std::string name, double amount) : 
        _owner(name), _amount(amount) {}
    
    void calculate()    {   _amount += _amount * _interestRate; }
    static double rate()    {   return _interestRate;   }
    static void rate(double);

private:
    static double initRate();

    std::string _owner;
    double  _amount;
    static double _interestRate;
    static constexpr int _period = 5;
    double daily_tbl[_period];
};

#endif  // ACCOUNT_HPP