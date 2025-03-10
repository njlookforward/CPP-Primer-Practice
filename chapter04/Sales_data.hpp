#ifndef SALES_DATA_HPP
#define SALES_DATA_HPP

#include <string>
#include <iostream>

struct Sales_data
{
    std::string _bookNo;
    unsigned _units_sold = 0;
    double _revenue = 0.0;
};

inline std::istream& operator>>(std::istream &is, Sales_data &rhs)
{
    double price = 0;
    is >> rhs._bookNo >> rhs._units_sold >> price;
    if(is)
        rhs._revenue = rhs._units_sold * price;
    
    return is;
}

inline bool compareISBN(const Sales_data &lhs, const Sales_data &rhs)
{
    if(lhs._bookNo == rhs._bookNo)
        return true;
    else
        return false;
}

inline Sales_data& operator+=(Sales_data &lhs, const Sales_data &rhs)
{
    lhs._units_sold = lhs._units_sold + rhs._units_sold;
    lhs._revenue = lhs._revenue + rhs._revenue;
    return lhs;
}

inline std::ostream& operator<<(std::ostream &os, const Sales_data &rhs)
{
    os << "ISBN:\t" << rhs._bookNo << std::endl
       << "units_sold:\t" << rhs._units_sold << std::endl
       << "revenue:\t" << rhs._revenue << std::endl;
    if(rhs._units_sold)
        os << "average_price:\t" << rhs._revenue/rhs._units_sold << std::endl;
    else
        os << "no sale" << std::endl;
    
    return os;
}

#endif