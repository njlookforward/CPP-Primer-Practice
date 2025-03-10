#include "Date.hpp"
using namespace std;

std::ostream &operator<<(std::ostream &os, const Date &date)
{
    // 输出运算符中最好不要有格式化操作
    const char sep = '\t';
    os << "year: " << date._year << sep
       << "month: " << date._month << sep
       << "day: " << date._day;
    
    return os;
}

std::istream &operator>>(std::istream &is, Date &d)
{
    // 输入运算符中一定要有输入失败处理
    is >> d._year >> d._month >> d._day;
    if(!is)
        d = Date();
    
    return is;
}

bool operator==(const Date &lhs, const Date &rhs)
{
    return lhs._year == rhs._year &&
           lhs._month == rhs._month &&
           lhs._day == rhs._day;
}

bool operator!=(const Date &lhs, const Date &rhs)
{
    return !(lhs == rhs);
}

bool operator<(const Date &lhs, const Date &rhs)
{
    // if(lhs._year < rhs._year)
    //     return true;
    // else if(lhs._year == rhs._year)
    // {
    //     if(lhs._month < rhs._month)
    //         return true;
    //     else if(lhs._month == rhs._month)
    //     {
    //         if(lhs._day < rhs._day)
    //             return true;
    //         else
    //             return false;
    //     }
    //     return false;
    // }
    // else
    //     return false;

    // 这种写法直接用所有有效的方式进行判断，更加精简
    return (lhs._year < rhs._year) ||
           (lhs._year == rhs._year && lhs._month < rhs._month) ||
           (lhs._year == rhs._year && lhs._month == rhs._month && lhs._day < rhs._day);
}

bool operator<=(const Date &lhs, const Date &rhs)
{
    return lhs < rhs || lhs == rhs;
}

bool operator>(const Date &lhs, const Date &rhs)
{
    return !(lhs <= rhs);
}

bool operator>=(const Date &lhs, const Date &rhs)
{
    return !(lhs < rhs);
}

bool isLeapYear(int year)
{
    if(year % 400 == 0)
        return true;
    else if(year % 100 == 0)
        return false;
    else if(year % 4 == 0)
        return true;
    else
        return false;
    
    // return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
}

// Date &Date::operator=(const Date &rhs)
// {
//     _year = rhs._year;
//     _month = rhs._month;
//     _day = rhs._day;

//     return *this;
// }

// Date &Date::operator=(Date &&rhs) noexcept
// {
//     _year = std::move(rhs._year);
//     _month = std::move(rhs._month);
//     _day = std::move(rhs._day);

//     return *this;
// }

Date &Date::operator=(const std::string &date)
{
    // 可能将"1970-1-1"的数据赋值给对象
    istringstream iss(date);
    char ch1, ch2;
    iss >> _year >> ch1 >> _month >> ch2 >> _day;   // 真是厉害啊，直接格式化输入了

    if(!iss || ch1 != '-' || ch2 != '-')
        throw invalid_argument("Date::operator=(string): Bad input value");
    if(_month < 1 || _month > 12 || _day < 1 || _day > 31)
        throw invalid_argument("Date::operator=(string): Bad input value");

    return *this;
}

Date::operator bool() const
{
    // 需要判断日期的三个数据是否有效
    vector<vector<int>> daysOfMon = {
        {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
        {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
    };

    return _month >= 1 && _month <= 12 && _day >= 1 &&
           _day <= daysOfMon[isLeapYear(_year) ? 1 : 0][_month - 1];
}
