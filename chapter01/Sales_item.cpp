#include "Sales_item.hpp"

Sales_item::Sales_item(const Sales_item &rhs)
    : _isbn(rhs._isbn), _uints_sold(rhs._uints_sold), _revenue(rhs._revenue) {}

Sales_item::Sales_item(std::istream &in)
{
    in >> *this;
}

double Sales_item::averageSold() const
{
    if(!_uints_sold)
        return 0.0;
    
    return _revenue / _uints_sold;
}

Sales_item& Sales_item::operator+=(const Sales_item &rhs)
{
    // default two isbn is equal
    _uints_sold += rhs._uints_sold;
    _revenue += rhs._revenue;

    return *this;
}

bool Sales_item::operator==(const Sales_item &rhs) const
{
    return _isbn == rhs._isbn &&
           _uints_sold == rhs._uints_sold &&
           _revenue == rhs._revenue;
}

bool Sales_item::operator!=(const Sales_item &rhs) const
{
    return !(*this == rhs);
}

std::istream& operator>>(std::istream &in, Sales_item &rhs)
{
    double price;
    in >> rhs._isbn >> rhs._uints_sold >> price;
    if(!in)
    {
        std::cerr << "Please input formulation is isbn -- soldCount -- revenue" << std::endl;
        rhs = Sales_item();
    }
    else
        rhs._revenue = rhs._uints_sold * price;
    return in;
}

std::ostream& operator<<(std::ostream &os, const Sales_item &rhs)
{
    os << "#BookISBN: " << rhs.isbn() << std::endl
       << "#TotalSoldCount: " << rhs.soldCount() << std::endl
       << "#revenue: " << rhs.totalRevenue() << std::endl
       << "#average: " << rhs.averageSold() << std::endl;
    
    return os;
}

Sales_item operator+(const Sales_item &lhs, const Sales_item &rhs)
{
    Sales_item tmp(lhs);
    tmp += rhs;

    return tmp;
}

bool checkCompare(const Sales_item &lhs, const Sales_item &rhs)
{
    return lhs.isbn() == rhs.isbn();
}
