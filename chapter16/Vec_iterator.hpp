#ifndef VEC_ITERATOR_HPP
#define VEC_ITERATOR_HPP

#include <cstddef>
#include <iterator> // 为了能够使用迭代器类型标签

// 我认为可以同时进行iterator和const_iterator的类型推导
template<typename> class Vec_iterator;
template<typename T>
bool operator==(const Vec_iterator<T> &lhs, const Vec_iterator<T> &rhs);
template<typename T>
std::ptrdiff_t operator-(const Vec_iterator<T> &lhs, const Vec_iterator<T>&rhs);
template<typename T>
Vec_iterator<T> operator-(const Vec_iterator<T> &lhs, std::size_t length);
template<typename T>
class Vec_iterator {
    friend bool operator==<T>(const Vec_iterator<T> &lhs, const Vec_iterator<T> &rhs);
    friend std::ptrdiff_t operator-<T>(const Vec_iterator<T> &lhs, const Vec_iterator<T> &rhs);
    friend Vec_iterator<T> operator-<T>(const Vec_iterator<T> &lhs, std::size_t length);
public:
    // Bug: 需要定义迭代器的5大类型，才能被std::iterator_traits<>识别
    using value_type        = T;
    using different_type    = std::ptrdiff_t;
    using pointer           = T*;
    using reference         = T&;
    using iterator_category = std::random_access_iterator_tag;

    Vec_iterator(T *pv): _pval(pv) {}

    Vec_iterator& operator++();
    Vec_iterator operator++(int);
    Vec_iterator& operator--();

    pointer operator->()    {   return _pval;   }
    reference operator*();

private:
    T *_pval;
};

template<typename T>
Vec_iterator<T>& Vec_iterator<T>::operator++()
{
    ++_pval;
    return *this;
}

template<typename T>
Vec_iterator<T> Vec_iterator<T>::operator++(int)
{
    Vec_iterator tmp = *this;
    ++*this;
    return tmp;
}

template<typename T>
Vec_iterator<T>& Vec_iterator<T>::operator--()
{
    --_pval;
    return *this;
}

template<typename T>
T& Vec_iterator<T>::operator*()
{
    return *_pval;
}

template<typename T>
inline bool operator==(const Vec_iterator<T> &lhs, const Vec_iterator<T> &rhs)
{
    return lhs._pval == rhs._pval;
}

template<typename T>
inline bool operator!=(const Vec_iterator<T> &lhs, const Vec_iterator<T> &rhs)
{
    return !(lhs == rhs);
}

template<typename T>
Vec_iterator<T> operator-(const Vec_iterator<T> &lhs, std::size_t length)
{
    Vec_iterator<T> res = lhs;
    res._pval -= length;
    return res;
}

// 这个数字应该是一个实数，可正可负，应该使用ptrdiff_t
template<typename T>
std::ptrdiff_t operator-(const Vec_iterator<T> &lhs, const Vec_iterator<T>&rhs)
{
    return lhs._pval - rhs._pval;
}

template<typename> class Vec_const_iterator;
template<typename T>
bool operator==(const Vec_const_iterator<T> &lhs, const Vec_const_iterator<T> &rhs);
template<typename T>
std::ptrdiff_t operator-(const Vec_const_iterator<T> &lhs, const Vec_const_iterator<T>&rhs);
template<typename T>
class Vec_const_iterator {
    friend bool operator==<T>(const Vec_const_iterator<T> &lhs, const Vec_const_iterator<T> &rhs);
    friend std::ptrdiff_t operator-<T>(const Vec_const_iterator<T> &lhs, const Vec_const_iterator<T>&rhs);
public:
    // 常量迭代器的常量属性不是有元素类型体现的，是由指针类型和引用类型体现的
    using value_type        = T;
    using difference_type   = std::ptrdiff_t;
    using pointer           = const T*;
    using reference         = const T&;
    using iterator_category = std::random_access_iterator_tag;

    Vec_const_iterator(T *pv): _pval(pv) {}

    Vec_const_iterator& operator++();
    Vec_const_iterator operator++(int);

    reference operator*();
    pointer operator->()    {   return _pval;   }

private:
    const T *_pval;
};

template<typename T>
Vec_const_iterator<T>& Vec_const_iterator<T>::operator++()
{
    ++_pval;
    return *this;
}

template<typename T>
Vec_const_iterator<T> Vec_const_iterator<T>::operator++(int)
{
    Vec_const_iterator tmp = *this;
    ++*this;
    return tmp;
}

template<typename T>
const T& Vec_const_iterator<T>::operator*()
{
    return *_pval;
}

template<typename T>
inline bool operator==(const Vec_const_iterator<T> &lhs, const Vec_const_iterator<T> &rhs)
{
    return lhs._pval == rhs._pval;
}

template<typename T>
inline bool operator!=(const Vec_const_iterator<T> &lhs, const Vec_const_iterator<T> &rhs)
{
    return !(lhs == rhs);
}

template<typename T>
std::ptrdiff_t operator-(const Vec_const_iterator<T> &lhs, const Vec_const_iterator<T>&rhs)
{
    return lhs._pval - rhs._pval;
}

#endif

// 对于一个迭代器来说，最基本要实现的是++ * -> != ==
// 对于一个前向迭代器++, 双向迭代器++ -- 随机访问迭代器+ += - [] < <= > >=