#ifndef STRBLOB_HPP
#define STRBLOB_HPP

#include <iostream>
#include <memory>
// #include <vector>
// #include <string>
#include <initializer_list>
#include <stdexcept>
#include "strVec.hpp"

// strBlob类是一个可以共享的可变数组类
class strBlobPtr;
class ConstStrBlobPtr;
class strBlob {
    friend std::ostream &operator<<(std::ostream &os, const strBlob &sb);
    friend class strBlobPtr;
    friend class ConstStrBlobPtr;

public:
    // strBlob() : _data(std::make_shared<std::vector<std::string>>()) {}
    strBlob(): _data(std::make_shared<strVec>()) {}
    explicit strBlob(std::initializer_list<std::string> il) :    // initializer_list is also class template
    _data(std::make_shared<strVec>(il)) {}

    strBlob(strVec *pvs): _data(pvs) {}   // 为了满足TextQuery的构造函数的形式，再添加一个新的
    // strBlob(const strBlob &rhs) : _data(rhs._data) {}    // 拷贝语义是类指针形式
    // exercise_13_26 拷贝语义是类值形式
    strBlob(const strBlob &rhs)
    : _data(std::make_shared<strVec>(*rhs._data)) {}
    ~strBlob() {}

    // exercise_13_26
    strBlob &operator=(const strBlob &rhs);

    size_t size() const {   return _data->size();   }
    bool empty() const  {   return _data->empty();  }
    std::string &front();
    std::string &back();
    const std::string &front() const;   // can use const qualifier to overload
    const std::string &back() const;

    // exercise_13_55
    void push_back(const std::string &str) {    _data->push_back(str);  }
    void push_back(std::string &&str)   {   _data->push_back(std::move(str));   }

    void pop_back();
    std::string &operator[] (size_t pos);
    // 之前出现了ERROR，说明const对象只能调用const成员函数，因此要考虑的更完善一些
    const std::string &operator[] (size_t pos) const;
    strBlobPtr begin();
    strBlobPtr end();
    // error because strBlobPtr only has prepend declaration, no definition
    strBlobPtr begin() const;
    strBlobPtr end() const;

private:
    void check(size_t, const std::string &) const;

    // std::shared_ptr<std::vector<std::string>> _data;    // 智能指针指向可被多个strBlob对象共享的vector<string>
    std::shared_ptr<strVec> _data;
};

std::ostream &operator<<(std::ostream &os, const strBlob &sb);

class strBlobPtr {
    friend bool BlobEqual(const strBlobPtr &lhs, const strBlobPtr &rhs);
public:
    strBlobPtr(): _pos(0) {}
    strBlobPtr(strBlob &sb, size_t pos = 0): _pd(sb._data), _pos(pos)
    { /* std::cout << "strBlob &" << std::endl; */    }
    // exercise_12_22
    // 为了能够让strBlobPtr绑定到const strBlob，方法一是使用构造函数重载
    strBlobPtr(const strBlob &csb, size_t pos = 0): _pd(csb._data), _pos(pos)
    {   /*std::cout << "const strBlob &" << std::endl;*/  }

    strBlobPtr(const strBlobPtr &rhs): _pd(rhs._pd), _pos(rhs._pos) {}
    ~strBlobPtr() {}

    // 对于恒定不变的strBlob不用想的太复杂，直接定义为const strBlobPtr csbp = ***;就可以，因此需要重载const*
    const std::string &operator*() const;
    std::string &operator*();
    strBlobPtr &operator++();
    strBlobPtr operator++(int);
    strBlobPtr &operator--();
    strBlobPtr operator--(int);
    const std::string &deref(size_t dis) const;

private:
    std::shared_ptr<strVec> check(size_t pos, const std::string &) const;

    std::weak_ptr<strVec> _pd;    // strBlob._data的伴随指针类
    size_t _pos;    // 指针的位置索引
};

inline bool BlobEqual(const strBlobPtr &lhs, const strBlobPtr &rhs)
{
    auto lsp = lhs._pd.lock(), rsp = rhs._pd.lock();
    // 只有shared_ptr and unique_ptr has operator==
    if(lsp == rsp)
        return (!lsp || lhs._pos == rhs._pos);  // 1.both is nullptr 2.the element pointed is same
    else
        return false;
}

inline bool BlobNoEqual(const strBlobPtr &lhs, const strBlobPtr &rhs)
{
    return !BlobEqual(lhs, rhs);
}

class ConstStrBlobPtr {
public:
    ConstStrBlobPtr(): _pos(0) {}
    ConstStrBlobPtr(const strBlob &csb, size_t pos = 0):_pcd(csb._data), _pos(pos) {}

    const std::string &operator*();
    ConstStrBlobPtr &operator++();

private:
    std::shared_ptr<strVec> check(const std::string &msg) const;

    std::weak_ptr<strVec> _pcd;
    size_t _pos;
};

#endif