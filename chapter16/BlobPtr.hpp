#ifndef BLOBPTR_HPP
#define BLOBPTR_HPP

#include "Blob.hpp"

// 在这里要达成一个共识，就是BlobPtr就是一种类指针的函数模板
template<typename> class BlobPtr;   // 当不需要模板参数名字时是可以省略名字的
template<typename T>
bool operator==(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs);

template<typename T> class BlobPtr {
    friend bool operator==<T>(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs);

public:
    // Bug: 使用模板类型的类型成员，需要在前面加上typename
    typedef typename Blob<T>::size_type size_type;
    BlobPtr(): _index(0) {}
    BlobPtr(const Blob<T> &blob, size_type i = 0):
        _pdata(blob._data), _index(i) {}
    BlobPtr(const BlobPtr&) = default;
    ~BlobPtr() = default;

    T &operator*() const;   // 因为const BlobPtr<T>，只是常量指针，而不是指向常量的指针，因此应该返回正常引用
    BlobPtr &operator++();
    BlobPtr operator++(int);
    BlobPtr &operator--();
    BlobPtr operator--(int);
    
private:
    std::shared_ptr<std::vector<T>> check(size_type index, const std::string &msg) const;

    std::weak_ptr<std::vector<T>> _pdata;
    size_type _index;
};

template<typename T>
inline std::shared_ptr<std::vector<T>> BlobPtr<T>::check(size_type index, const std::string &msg) const
{
    auto sp = _pdata.lock();
    if(!sp)
        throw std::runtime_error("the Blob objectin that BlobPtr point has empired");
    if(index >= sp->size())
        throw std::out_of_range(msg);
    
    return sp;
}

template<typename T>
inline T& BlobPtr<T>::operator*() const
{
    auto sp =  check(_index, "dereference in the invalid index of vector");
    return (*sp)[_index];
}

template<typename T>
inline BlobPtr<T> &BlobPtr<T>::operator++()
{
    check(_index, "operator++ in the end of vector");
    ++_index;
    return *this;
}

template<typename T>
inline BlobPtr<T> BlobPtr<T>::operator++(int)
{
    BlobPtr tmp = *this;
    ++*this;    // 后置++使用前置++实现
    return tmp;
}

template<typename T>
BlobPtr<T> &BlobPtr<T>::operator--()
{
    --_index;
    check(_index, "operator-- past the beginner of vector");
    return *this;
}

template<typename T>
BlobPtr<T> BlobPtr<T>::operator--(int)
{
    BlobPtr<T> tmp = *this;
    --*this;
    return tmp;
}

template<typename T>
inline bool operator==(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs)
{
    auto sp1 = lhs._pdata.lock(),
         sp2 = rhs._pdata.lock();
    
    return sp1 == sp2 && lhs._index == rhs._index;
}

template<typename T>
inline bool operator!=(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs)
{
    return !(lhs == rhs);
}

#endif