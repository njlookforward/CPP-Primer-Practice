#ifndef HASPTR_HPP
#define HASPTR_HPP

#include <iostream>
#include <string>

class HasPtr {
    // 我傻了，既然是交换lhs的数据，肯定是非const对象
    friend void swap(HasPtr &lhs, HasPtr &rhs);
    friend bool operator<(const HasPtr &, const HasPtr &);
    friend std::ostream &operator<<(std::ostream &os, const HasPtr &rhs);

public:
    HasPtr(const std::string s = std::string())
        : _ps(new std::string(s)), _index(0)
    {   /*std::cout << "HasPtr()" << std::endl;*/   }
    
    // exercise_13_5
    HasPtr(const HasPtr &rhs)
    : _ps(new std::string(*rhs._ps)), _index(rhs._index)
    {   /*std::cout << "HasPtr(const HasPtr &)" << std::endl;*/ }

    HasPtr(HasPtr &&rhs) noexcept;

    ~HasPtr() { delete _ps;  /*std::cout << "~HasPtr()" << std::endl;*/   }

    // exercise_13_8
    HasPtr &operator=(const HasPtr &rhs);
    HasPtr &operator=(HasPtr &&) noexcept;
    // HasPtr &operator=(HasPtr rhs);   // 当进行函数匹配时，出现二义性

    std::string &mystr() {  return *_ps;    }

private:
    std::string *_ps;
    int _index;     
};

void swap(HasPtr &lhs, HasPtr &rhs);
bool operator<(const HasPtr &lhs, const HasPtr &rhs);
std::ostream &operator<<(std::ostream &os, const HasPtr &rhs);

HasPtr fcn_rval(HasPtr hp);

// 拷贝语义是类指针形式
class Phasptr {
    friend void swap(Phasptr &lhs, Phasptr &rhs);
public:
    Phasptr(const std::string &s = std::string())
    : _ps(new std::string(s)), _index(0), _cnt(new size_t(1)) {}

    Phasptr(const Phasptr &php):_ps(php._ps), _index(php._index), _cnt(php._cnt)
    {   ascendCnt(php); }

    Phasptr &operator=(const Phasptr &rhs);

    ~Phasptr() {    descendCnt();   }

private:
    // tool private function
    void ascendCnt(const Phasptr &php)  {   ++*php._cnt;    }
    void descendCnt();

    std::string *_ps;
    size_t    _index;
    size_t     *_cnt;   // 通过动态内存实现数据通信
};

void swap(Phasptr &lhs, Phasptr &rhs);

#endif