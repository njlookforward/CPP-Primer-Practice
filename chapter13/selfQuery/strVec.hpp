#ifndef STRVEC_HPP
#define STRVEC_HPP

// #include <string>
#include "String.hpp"
#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <utility>
#include <algorithm>
// 定义自己的动态数组，难度降低一些，动态数组中只保存字符串，能够根据需要自己动态扩充内存
// 类值拷贝语义，一定要仔细思考如何管理动态空间

// 按照普通vector的接口去设计
class strVec {
public:
    strVec(): _elements(nullptr), _first_free(nullptr), _cap(nullptr) {}
    strVec(size_t sz);
    strVec(const std::initializer_list<String> il);

    strVec(const strVec &);
    strVec &operator=(const strVec &rhs);

    ~strVec() { free(); }

    size_t capacity() const {   return _cap - _elements;    }
    size_t size() const {   return _first_free - _elements; }
    bool empty() const  {   return size() == 0; }
    void push_back(const String &val);
    void pop_back();

    String *begin() {  return _elements;   }
    String *end()   {  return _first_free; }
    // error，否则传入const strVec &, 返回的string *会丢失const限定符
    const String *begin() const {  return _elements;   }
    const String *end() const {    return _first_free; }

    String &front() {  return *_elements;  }
    String &back()  {  return *(_first_free - 1);  }
    const String &front() const {  return *_elements;  }
    const String &back() const  {  return *(_first_free - 1);  }

    String &operator[] (size_t pos);
    const String &operator[] (size_t pos) const;

    // exercise_13_39
    void reserve(size_t sz);
    void resize(size_t sz, const String &str = String());

private:
    // tool private function
    void free();
    void reallocTwice();
    void check_space();
    std::pair<String *, String *> alloc_n_copy(String *b, String *e);

    String *_elements;     // 指向动态数组的第一个元素的指针
    String *_first_free;   // 指向第一个空闲指针
    String *_cap;          // 指向所分配空间的下一个位置

    static std::allocator<String> _alloc;  // 空间配置器，被所有strVec所共有，因为只是用来分配和释放空间用的，不需要保存数据
};

std::ostream &print(std::ostream &os, const strVec &rhs);

#endif