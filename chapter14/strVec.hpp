#ifndef STRVEC_HPP
#define STRVEC_HPP

#include <string>
#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <utility>
#include <algorithm>
#include <iterator>
#include <iostream>
// 定义自己的动态数组，难度降低一些，动态数组中只保存字符串，能够根据需要自己动态扩充内存
// 类值拷贝语义，一定要仔细思考如何管理动态空间

// 按照普通vector的接口去设计
class strVec {
public:
    strVec(): _elements(nullptr), _first_free(nullptr), _cap(nullptr) {}
    strVec(size_t sz);
    strVec(const std::initializer_list<std::string> il);

    strVec(const strVec &);
    strVec &operator=(const strVec &rhs);

    // 定义移动操作时，又忘记了思考需不需要添加noexcept qualifier
    strVec(strVec &&) noexcept;
    strVec &operator=(strVec &&) noexcept;

    strVec &operator=(std::initializer_list<std::string> il);

    ~strVec() { free(); }

    size_t capacity() const {   return _cap - _elements;    }
    size_t size() const {   return _first_free - _elements; }
    bool empty() const  {   return size() == 0; }
    
    // 右值引用也可以用于其他成员函数，一般有常量左值引用和右值引用两个版本
    void push_back(const std::string &val);
    void push_back(std::string &&val);
    void pop_back();

    std::string *begin() {  return _elements;   }
    std::string *end()   {  return _first_free; }
    // error，否则传入const strVec &, 返回的string *会丢失const限定符
    const std::string *begin() const {  return _elements;   }
    const std::string *end() const {    return _first_free; }

    std::string &front() {  return *_elements;  }
    std::string &back()  {  return *(_first_free - 1);  }
    const std::string &front() const {  return *_elements;  }
    const std::string &back() const  {  return *(_first_free - 1);  }

    std::string &operator[] (std::size_t pos);
    const std::string &operator[] (std::size_t pos) const;

    // exercise_13_39
    void reserve(size_t sz);
    void resize(size_t sz, const std::string &str = std::string());

private:
    // tool private function
    void free();
    void reallocTwice();
    void check_space();
    std::pair<std::string *, std::string *> alloc_n_copy(const std::string *b, const std::string *e);

    std::string *_elements;     // 指向动态数组的第一个元素的指针
    std::string *_first_free;   // 指向第一个空闲指针
    std::string *_cap;          // 指向所分配空间的下一个位置

    static std::allocator<std::string> _alloc;  // 空间配置器，被所有strVec所共有，因为只是用来分配和释放空间用的，不需要保存数据
};

std::ostream &print(std::ostream &os, const strVec &rhs);
bool operator<(const strVec &lhs, const strVec &rhs);
bool operator>(const strVec &lhs, const strVec &rhs);
bool operator<=(const strVec &lhs, const strVec &rhs);
bool operator>=(const strVec &lhs, const strVec &rhs);
bool operator==(const strVec &lhs, const strVec &rhs);
bool operator!=(const strVec &lhs, const strVec &rhs);

#endif