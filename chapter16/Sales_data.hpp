#ifndef SALES_DATA_HPP
#define SALES_DATA_HPP

#include <iostream>
#include <string>
#include <stdexcept>
#include <cstddef>

// struct and class all are self-definition class keyword, just default public

// Bug: hash是内置类型，不需要引用头文件，同时不需要重复声明
// template <typename T> class std::hash;
struct Sales_data
{
    friend class std::hash<Sales_data>;
    // 友元声明不受访问权限区域的限制，一般集中放在类定义内部的开头，友元没有传递性
    friend std::istream &read(std::istream &is, Sales_data &rhs);
    friend std::ostream &print(std::ostream &os, const Sales_data &rhs);
    friend std::istream &operator>>(std::istream &is, Sales_data &rhs);
    friend std::ostream &operator<<(std::ostream &os, const Sales_data &rhs);
    friend bool operator==(const Sales_data &lhs, const Sales_data &rhs);
    friend Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs);

public:
    Sales_data() = default; // 让编译器生成合成默认构造函数
    // Sales_data();
    // try delegating constructor 委托构造函数
    Sales_data(const std::string &isbn, unsigned soldCnt, double unitPrice);
    // Sales_data(): Sales_data("", 0, 0) {    std::cout << "Sales_data()" << std::endl; }
    Sales_data(const std::string &isbn) : Sales_data(isbn, 0, 0) {  /*std::cout << "Sales_data(string)" << std::endl;*/ }
    Sales_data(std::istream &is) {   
        read(is, *this);
        /*std::cout << "Sales_data(istream&)" << std::endl;*/    }   // exercise_7_12

    // Sales_data(const Sales_data &); // copy constructor
    Sales_data(const Sales_data &) = default;

    std::string isbn() const    {   return _isbn;   }
    Sales_data &combine(const Sales_data &rhs); // 在类定义内部使用类自身作为返回值类型，由于是不完全类型
    // 因此只能使用类类型的指针或者引用

    Sales_data &operator=(const Sales_data &rhs);
    // Sales_data &operator=(const Sales_data &) = default;
    Sales_data &operator=(const std::string &newIsbn);

    Sales_data &operator+=(const Sales_data &rhs);
    Sales_data &operator-=(const Sales_data &rhs);

    ~Sales_data() = default;

    explicit operator std::string() const {  return _isbn;   }
    explicit operator double() const {   return _revenue;    }

private:
    double sold_average() const;

    // 尽量使用类内初始值形式，= 或 {}进行赋值
    std::string _isbn;  // 书号
    unsigned _units_sold = 0;   // 售卖数量
    double _revenue = 0.0;    // 总收入
};

std::istream &read(std::istream &is, Sales_data &rhs);
std::ostream &print(std::ostream &os, const Sales_data &rhs);
std::istream &operator>>(std::istream &is, Sales_data &rhs);
std::ostream &operator<<(std::ostream &os, const Sales_data &rhs);
Sales_data Add(const Sales_data &lhs, const Sales_data &rhs);
Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs);
Sales_data operator-(const Sales_data &lhs, const Sales_data &rhs);
bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs);
bool operator==(const Sales_data &lhs, const Sales_data &rhs);
bool operator!=(const Sales_data &lhs, const Sales_data &rhs);

// exercise_7_26
inline double Sales_data::sold_average() const
{
    if(_units_sold)
        return _revenue / _units_sold;
    else
        return 0;
}

namespace std {
template <>
struct hash<Sales_data> {
    using result_type = std::size_t;
    using argument_type = Sales_data;

    result_type operator()(const Sales_data &item) const;
};

// 必须使用内联函数的方法，inline，否则会出现链接错误，只要在头文件中进行函数定义，必须设置为内联函数
inline hash<Sales_data>::result_type hash<Sales_data>::operator()(const Sales_data &item) const {
    // 记住hash<T>是一个类型，hash<T>()才是一个对象，然后调用函数调用运算符进行哈希计算
    return hash<string>()(item._isbn) ^
           hash<unsigned>()(item._units_sold) ^
           hash<double>()(item._revenue);
}
}

#endif  // SALES_DATA_HPP