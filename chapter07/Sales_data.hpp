#ifndef SALES_DATA_HPP
#define SALES_DATA_HPP

#include <iostream>
#include <string>

// struct and class all are self-definition class keyword, just default public
struct Sales_data
{
    // 友元声明不受访问权限区域的限制，一般集中放在类定义内部的开头，友元没有传递性
    friend std::istream &read(std::istream &is, Sales_data &rhs);
    friend std::ostream &print(std::ostream &os, const Sales_data &rhs);

public:
    // Sales_data() = default; // 让编译器生成合成默认构造函数
    // Sales_data();
    // try delegating constructor 委托构造函数
    Sales_data(const std::string &isbn, unsigned soldCnt, double unitPrice);
    Sales_data(): Sales_data("", 0, 0) {    std::cout << "Sales_data()" << std::endl; }
    Sales_data(const std::string &isbn) : Sales_data(isbn, 0, 0) {  /*std::cout << "Sales_data(string)" << std::endl;*/ }
    Sales_data(std::istream &is) {   
        read(is, *this);
        /*std::cout << "Sales_data(istream&)" << std::endl;*/    }   // exercise_7_12

    std::string isbn() const    {   return _isbn;   }
    Sales_data &combine(const Sales_data &rhs); // 在类定义内部使用类自身作为返回值类型，由于是不完全类型
    // 因此只能使用类类型的指针或者引用

private:
    double sold_average() const;

    // 尽量使用类内初始值形式，= 或 {}进行赋值
    std::string _isbn;  // 书号
    unsigned _units_sold = 0;   // 售卖数量
    double _revenue = 0.0;    // 总收入
};

std::istream &read(std::istream &is, Sales_data &rhs);
std::ostream &print(std::ostream &os, const Sales_data &rhs);
Sales_data Add(const Sales_data &lhs, const Sales_data &rhs);

// exercise_7_26
inline double Sales_data::sold_average() const
{
    if(_units_sold)
        return _revenue / _units_sold;
    else
        return 0;
}

#endif  // SALES_DATA_HPP