#ifndef EXERCISE_HPP
#define EXERCISE_HPP

#include "strBlob.hpp"
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <stdexcept>
#include <functional>
#include "Sales_data.hpp"

class ptrStrBlobPtr {
public:
    ptrStrBlobPtr(strBlobPtr *pd): _pd(pd) {}

    strBlobPtr &operator->()
    {
        return *_pd;
    }

private:
    strBlobPtr *_pd;
};

struct absInt {
    int operator()(int val) const
    {
        return val < 0 ? -val : val;
    }
};

class PrintString {
public:
    PrintString(std::ostream &os = std::cout, char delim = ' '):
                _os(os), _delim(delim) {}
    void operator() (const std::string &s) const    // 为什么要是const成员函数，const不是限制的是用const对象吗
    {
        _os << s << _delim;
    }

private:
    std::ostream &_os;
    char _delim;
};

// exercise_14_34
struct judgeObj
{
    const std::string &operator() (int num, const std::string &lowercase, const std::string &uppercase) const
    {
        if(num & 1)
            return lowercase;   // 奇数返回小写
        else
            return uppercase;   // 偶数返回大写
    }
};

// exercise_14_35
class InputLineString {
public:
    InputLineString(std::istream &is = std::cin): _is(is) {}
    std::string operator() () const
    {
        std::string line;
        if(std::getline(_is, line))
            return line;
        else
            return std::string();
    }

private:
    std::istream &_is;
};

// exercise_14_37
class EqualVal {
public:
    EqualVal(int num): _base(num) {}
    bool operator() (int num) const
    {
        return _base == num;
    }
private:
    int _base;
};

// exercise_14_38
class CheckLength {
public:
    CheckLength(std::size_t thresh = 1): _threshold(thresh) {}
    void changeThresh(std::size_t newThresh)    {   _threshold = newThresh; }
    bool operator() (const std::string &str) const
    {
        if(_threshold < 10)
            return str.size() == _threshold;
        else
            return str.size() >= _threshold;
    }

private:
    std::size_t _threshold;
};

class strLenBetween {
public:
    strLenBetween(int min, int max): _minLen(min), _maxLen(max) {}
    bool operator() (const std::string &str) const
    {
        return str.length() >= _minLen &&
               str.length() <= _maxLen;
    }

private:
    int _minLen;
    int _maxLen;
};

class strNotShorterThan {
public:
    strNotShorterThan(int min): _minLen(min) {}
    bool operator() (const std::string &str) const
    {
        return str.length() >= _minLen;
    }

private:
    int _minLen;
};

void openfile(std::ifstream &ifs, const std::string &dir);
std::string cleanup_str(const std::string &word);

// exercise_14_43
bool Factor(int num, const std::vector<int> &ivec);

inline int add(int i, int j) {  return i + j;   }
class divide {
public:
    int operator() (int denominator, int divisor) const
    {   return denominator / divisor;   }
};

inline
Sales_data add(const Sales_data &lhs, const Sales_data &rhs) {  return Sales_data();    }

class smallInt {
    friend smallInt operator+(const smallInt &lhs, const smallInt &rhs);

public:
    smallInt(int val = 0): _val(val)
    {
        if(_val < 0 || _val > 255)
            throw std::out_of_range("Bad SmallInt Value.");
    }

    // 定义成显示类型转换运算符，防止发生未知的或者不希望的类型转换
    operator int() const {  return _val;    }

private:
    std::size_t _val;
};

inline smallInt operator+(const smallInt &lhs, const smallInt &rhs)
{
    smallInt sum;
    sum._val = lhs._val + rhs._val;
    return sum;
}

struct B;
struct A {
    // A() = default;
    // 一个类中最好只定义一个转换源是算数类型的构造函数或者转化目标是算数类型的类型转换运算符
    A(const B&) {   std::cout << "A::A(const B&)" << std::endl; }

    A(int = 0) {}
    A(double) {}

    operator int() const {  return 0;   }
    operator double() const {   return 0.0; }
};

struct B {
    operator A() const {    
        std::cout << "B::operator A() const" << std::endl;
        return A(); 
    }
};

// 一定要尽可能限制那些“显然正确”的非显示构造函数
struct C {
    C(int) {}
};

struct D
{
    D(int) {}
};

struct E
{
    E(double) {}
};

struct LongDouble
{
    LongDouble(double = 0.0) {  std::cout << "LongDouble::LongDouble(double)" << std::endl; }
    operator double() const {   return 0.0; }
    operator float() const  {   return 0.0; }
};

inline
LongDouble operator+(const LongDouble &ld, const smallInt &rhs)
{
    std::cout << "operator+(longdouble, smallint)" << std::endl;
    return ld.operator double() + rhs.operator int();
}

inline LongDouble operator+(const LongDouble &ld, double rhs)
{
    std::cout << "operator+(LongDouble, double)" << std::endl;
    return ld.operator double() + rhs;
}

inline bool sizeCompare(const std::string &str, std::string::size_type sz)
{
    return str.size() >= sz;
}

#endif