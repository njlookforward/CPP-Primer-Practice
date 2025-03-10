#ifndef DATE_HPP
#define DATE_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <vector>

class Date {
    friend std::ostream &operator<<(std::ostream &os, const Date &date);
    friend std::istream &operator>>(std::istream &is, Date &date);
    friend bool operator==(const Date &lhs, const Date &rhs);
    friend bool operator<(const Date &lhs, const Date &rhs);

public:
    Date() = default;
    Date(int y, int m, int d): _year(y), _month(m), _day(d) {}

    // 由于Date只有3个int类型的数据成员，因此浅拷贝就可以满足需求，没必要定义拷贝赋值和移动赋值运算符
    // 但是为了再练习一下，可以定义
    Date& operator=(const Date &rhs) = default;
    Date& operator=(Date &&rhs) = default;
    Date& operator=(const std::string &date);

    explicit operator bool() const;

private:
    int _year = 2025;
    int _month = 2;
    int _day = 1;
};

std::ostream &operator<<(std::ostream &os, const Date &date);
std::istream &operator>>(std::istream &is, Date &Date);
bool operator==(const Date &lhs, const Date &rhs);
bool operator!=(const Date &lhs, const Date &rhs);
bool operator<(const Date &lhs, const Date &rhs);
bool operator<=(const Date &lhs, const Date &rhs);
bool operator>(const Date &lhs, const Date &rhs);
bool operator>=(const Date &lhs, const Date &rhs);

bool isLeapYear(int year);

#endif