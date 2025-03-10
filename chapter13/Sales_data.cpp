#include "Sales_data.hpp"
using namespace std;    // 不要在头文件中使用，在源文件中使用。可以避免一些麻烦

// Sales_data::Sales_data():
    // _isbn(""), _units_sold(0), _revenue(0.0) {}

// Sales_data::Sales_data(const string &isbn) : _isbn(isbn) {}

Sales_data::Sales_data(const string &isbn, unsigned soldCnt, double unitPrice):
    _isbn(isbn), _units_sold(soldCnt), _revenue(soldCnt * unitPrice)
{
    //cout << "Sales_data(string, unsigned, double)" << endl;
}

// 需要将定义移到类的内部
// Sales_data::Sales_data(istream &is)
// {
//     read(is, *this);
// }

// Sales_data::Sales_data(const Sales_data &rhs):
    // _isbn(rhs._isbn), _units_sold(rhs._units_sold), _revenue(rhs._revenue) {}

Sales_data &Sales_data::combine(const Sales_data &rhs)
{
    // 默认两者的isbn是相同的
    _units_sold += rhs._units_sold;
    _revenue += rhs._revenue;

    return *this;
}

// Sales_data &Sales_data::operator=(const Sales_data &rhs)
// {
//     _isbn = rhs._isbn;
//     _units_sold = rhs._units_sold;
//     _revenue = rhs._revenue;

//     return *this;
// }
Sales_data &Sales_data::operator=(const Sales_data &) = default;

istream &read(istream &is, Sales_data &rhs)
{
    double unitPrice;
    is >> rhs._isbn >> rhs._units_sold >> unitPrice;
    if(unitPrice)
        rhs._revenue = rhs._units_sold * unitPrice;
    else
        rhs = Sales_data(rhs._isbn);
    
    return is;
}

ostream &print(ostream &os, const Sales_data &rhs)
{
    os << "isbn:\t" << rhs._isbn << endl
       << "units_sold:\t" << rhs._units_sold << endl
       << "revenue:\t" << rhs._revenue << endl
       << "unitPrice:\t" << rhs.sold_average();

    return os;
}

std::istream &operator>>(std::istream &is, Sales_data &rhs)
{
    double unitPrice;
    is >> rhs._isbn >> rhs._units_sold >> unitPrice;
    if(unitPrice)
        rhs._revenue = rhs._units_sold * unitPrice;
    else
        rhs = Sales_data(rhs._isbn);
    
    return is;
}

std::ostream &operator<<(std::ostream &os, const Sales_data &rhs)
{
    os << "isbn:\t" << rhs._isbn << endl
       << "units_sold:\t" << rhs._units_sold << endl
       << "revenue:\t" << rhs._revenue << endl
       << "unitPrice:\t" << rhs.sold_average()
       << endl;

    return os;
}

Sales_data Add(const Sales_data &lhs, const Sales_data &rhs)
{
    Sales_data sum(lhs);
    sum.combine(rhs);
    return sum;
}

Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs)
{
    Sales_data sum(lhs);
    sum.combine(rhs);
    return sum;
}

bool operator==(const Sales_data &lhs, const Sales_data &rhs)
{
    return lhs.isbn() == rhs.isbn();
}
