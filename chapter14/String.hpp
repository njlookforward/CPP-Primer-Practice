#ifndef STRING_HPP
#define STRING_HPP

// string就是动态变长的字符数组，和vector类似，只不过元素是字符而已，不要害怕，加油
#include <iostream>
#include <memory>
#include <cstring>
#include <utility>
#include <stdexcept>
#include <cctype>
#include <algorithm>

// 区分：C风格字符串以'\0'结尾，目的是以'\0'作为结束标志，而在string中，_first_free就是结束标志
// 因此从最初的目的为出发点进行思考，就会非常清晰，仍然是简化思考，我自己设计的String就是以_first_free
// 作为结束标志，至于像c_str()这种成员函数，返回C风格字符串，如何以'\0'结尾，仍然是简化思考，我假设
// 返回c_str的String都即将被销毁，而且只能被普通String对象调用，就好设计了，更优秀的设计自己目前想不到
// 仍然是业务中需要用到哪些函数，我就定义哪些函数，慢慢累加，就会设计得比较完整
// 看答案和我想的大差不差，以后的设计必须遵守一个原则，以String为例，既然已经确定_first_free作为字符串的结束标志
// 那么就要围绕_first_free进行设计，不要再想'\0'的事情，需要转换为c_str()时再去想如何在已有架构的基础上进行设计

class String {
    friend std::istream &operator>>(std::istream &is, String &str);
    friend std::istream &getline(std::istream &is, String &str);
    friend std::ostream &operator<<(std::ostream &os, const String &str);
public:
    String(): _elements(nullptr), _first_free(nullptr), _cap(nullptr) {}
    String(const char *cstr);

    String(const String &);
    String &operator=(const String &);

    String(String &&) noexcept;
    String &operator=(String &&) noexcept;

    ~String()   {   free(); }

    size_t size() const     {   return _first_free - _elements; }
    size_t capacity() const {   return _cap - _elements;    }
    bool empty() const      {   return !size(); }
    void push_back(char ch);
    void pop_back();
    char *begin()   {   return _elements;   }
    char *end()     {   return _first_free; }
    const char *begin() const   {   return _elements;   }
    const char *end() const     {   return _first_free; }
    const char *c_str();

    String &operator+=(const String &rhs);
    String &operator+=(const char &ch);

    char &operator[](std::size_t pos);
    char operator[](std::size_t pos) const;

private:
    void free();
    void check_space();
    void reallocate();
    std::pair<char *, char *> alloc_n_copy(const char *b, const char *e);


    char *_elements;
    char *_first_free;
    char *_cap;

    static std::allocator<char> _alloc; // 字符分配器
};

std::istream &operator>>(std::istream &is, String &str);
std::ostream &operator<<(std::ostream &os, const String &str);
std::istream &getline(std::istream &is, String &str);
bool operator<(const String &lhs, const String &rhs);
bool operator>(const String &lhs, const String &rhs);
bool operator<=(const String &lhs, const String &rhs);
bool operator>=(const String &lhs, const String &rhs);
bool operator==(const String &lhs, const String &rhs);
bool operator!=(const String &lhs, const String &rhs);
String operator+(const String &lhs, const String &rhs);

#endif