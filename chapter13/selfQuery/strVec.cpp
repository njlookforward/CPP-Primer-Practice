#include "strVec.hpp"
using namespace std;

allocator<String> strVec::_alloc;   // 定义

strVec::strVec(size_t sz)
{
    _elements = _alloc.allocate(sz);
    _first_free = _cap = uninitialized_fill_n(_elements, sz, String());
    // 要进行值初始化
}

strVec::strVec(const initializer_list<String> il)
{
    _elements = _alloc.allocate(il.size());
    _first_free = uninitialized_copy(il.begin(), il.end(), _elements);
    _cap = _first_free;
}

strVec::strVec(const strVec &rhs)
{
    _elements = _alloc.allocate(rhs.size());
    _first_free = _cap = uninitialized_copy(rhs.begin(), rhs.end(), _elements);
}

strVec &strVec::operator=(const strVec &rhs)
{
    // 这样直接释放旧内存空间，分配新内存空间，比我自己设想的若是赋值右侧对象的大小小于左侧对象的容量
    // 则通过一部分赋值，后一部分构造的形式，两种实现的性能没有差不少，直接释放和分配的方法仅仅是多了
    // 一次内存回收和内存分配，要是右侧对象的大小大于左侧容量的话，还多了赋值和构造的过程
    // 类值拷贝赋值
    auto newbgit = _alloc.allocate(rhs.size());
    auto endit = uninitialized_copy(rhs.begin(), rhs.end(), newbgit);
    free();

    _elements = newbgit;
    _first_free = _cap = endit;

    return *this;
}

void strVec::push_back(const String &val)
{
    check_space();
    _alloc.construct(_first_free++, val);
}

void strVec::pop_back()
{
    if(size())
        _alloc.destroy(--_first_free);
    else
        throw runtime_error("pop in the empty strVec.");
}

String &strVec::operator[](size_t pos)
{
    if(_elements + pos >= _first_free)
        throw out_of_range("strVec::operator[pos]: pos is invalid.");
    
    return *(_elements + pos);
}

const String &strVec::operator[](size_t pos) const
{
    if(_elements + pos >= _first_free)
        throw out_of_range("strVec::operator[pos]: pos is invalid.");
    
    return *(_elements + pos);
}

void strVec::reserve(size_t sz)
{
    // just allocate memeory, don't need to construct
    // 我只需要理会sz > cap()的情况，若是缩小capacity，则不需要理会
    if(sz > capacity())
    {
        auto newbg = _alloc.allocate(sz);
        auto newFirFree = newbg;
        // 如果一开始_elements == nullptr，该逻辑也是没有问题的
        for(auto iter = _elements; iter != _first_free; ++iter)
            _alloc.construct(newFirFree++, std::move(*iter));
        free();
        _elements = newbg;
        _first_free = newFirFree;
        _cap = newbg + sz;
    }
}

void strVec::resize(size_t sz, const String &str)
{
    // resize其实很简单
    if(sz < 0)
        throw runtime_error("strVec::resize(): sz < 0, sz is invalid.");
    if(sz < size())
    {
        while (size() > sz)
            _alloc.destroy(--_first_free);
    }
    else if(sz > size())
    {
        while (size() < sz)
            push_back(str);
    }
}

void strVec::free()
{
    // must assure _elements is valid
    if(_elements)
    {
        // while (_first_free != _elements)
        // {
        //     _alloc.destroy(--_first_free);
        // }

        // exercise_13_43
        for_each(_elements, _first_free, [] (const String &s) { _alloc.destroy(&s); });

        _alloc.deallocate(_elements, capacity());
    }
}

void strVec::reallocTwice()
{
    size_t newsz = size() ? size() * 2 : 1;
    auto newbgit = _alloc.allocate(newsz);
    auto newFirFree = newbgit;
    for(auto iter = _elements; iter != _first_free; ++iter)
    {
        _alloc.construct(newFirFree++, std::move(*iter));
    }

    free();
    _elements = newbgit;
    _first_free = newFirFree;
    _cap = _elements + newsz;
}

void strVec::check_space()
{
    if(size() == capacity())
        reallocTwice();
}

std::pair<String *, String *> strVec::alloc_n_copy(String *b, String *e)
{
    auto bgit = _alloc.allocate(e - b);
    return {bgit, uninitialized_copy(b, e, bgit)};
}

std::ostream &print(std::ostream &os, const strVec &rhs)
{
    for (auto &entry : rhs)
    {
        os << entry << String(" ");
    }

    return os;
}
