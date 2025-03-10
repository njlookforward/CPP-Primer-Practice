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

Sales_data &Sales_data::operator=(const std::string &newIsbn)
{
    // 我认为Sales_data的数据是一体的，因此需要都变
    _isbn = newIsbn;
    _units_sold = 0;
    _revenue = 0.0;

    return *this;
}

Sales_data &Sales_data::operator+=(const Sales_data &rhs)
{
    // 此函数默认两者的isbn是相同的
    _units_sold += rhs._units_sold;
    _revenue += rhs._revenue;

    return *this;
}
// Sales_data &operator+=(const Sales_data &rhs)
// {
//     *this = *this + rhs;

//     return *this;
// }

Sales_data &Sales_data::operator-=(const Sales_data &rhs)
{
    // 仍然默认两者isbn是相同的
    // 减法不同于加法，一定要在大的集合中减去其中包括的小集合，因此需要判断两者能够进行减法
    if(_units_sold < rhs._units_sold || _revenue < rhs._revenue)
        throw out_of_range("subtractor is invalid.");
    
    _units_sold -= rhs._units_sold;
    _revenue -= rhs._revenue;

    return *this;
}

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
    // 输入运算符一定要有输入错误管理
    // 最好的方式是由IO标准库自己来标示IO流发生的错误
    double unitPrice;
    is >> rhs._isbn >> rhs._units_sold >> unitPrice;
    if(is)
        rhs._revenue = rhs._units_sold * unitPrice;
    else
        rhs = Sales_data(); // 因为不能将isbn与两个非法数据放在一体，数据正确性是一体的，用默认构造函数可以至少保证数据整体正确性
    
    return is;
}

std::ostream &operator<<(std::ostream &os, const Sales_data &rhs)
{
    os << "isbn:\t" << rhs._isbn << endl
       << "units_sold:\t" << rhs._units_sold << endl
       << "revenue:\t" << rhs._revenue << endl
       << "unitPrice:\t" << rhs.sold_average(); // 输出运算符不要添加格式化操作，将选择权交给用户

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
    sum += rhs;
    return sum;
}

// exercise_14_21
// Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs)
// {
//     // 默认情况下lhs与rhs的isbn是相同的
//     Sales_data sum(lhs.isbn());
//     sum._units_sold = lhs._units_sold + rhs._units_sold;
//     sum._revenue = lhs._revenue + rhs._revenue;

//     return sum;
// }

Sales_data operator-(const Sales_data &lhs, const Sales_data &rhs)
{
    Sales_data res = lhs;
    res -= rhs;

    return res;
}

bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs)
{
    return lhs.isbn() == rhs.isbn();
}

bool operator==(const Sales_data &lhs, const Sales_data &rhs)
{
    return lhs.isbn() == rhs.isbn() && 
           lhs._units_sold == rhs._units_sold &&
           lhs._revenue == rhs._revenue;
}

bool operator!=(const Sales_data &lhs, const Sales_data &rhs)
{
    return !(lhs == rhs);
}
