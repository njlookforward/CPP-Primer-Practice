#ifndef BLOB_SHARED_PTR_HPP
#define BLOB_SHARED_PTR_HPP

#include <initializer_list>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <cstddef>
#include "Shared_ptr.hpp"
#include "exercise.hpp"

// 这里就是一种尝试，试试可不可以，这次的尝试解决了我之前的一个疑问，就是需不需要交叉include，现在的答案是不应该
// 而是直接在被include的文件中声明友元类即可，因为不需要用到，所以不需要定义，但是需要声明友元类
template<typename> class BlobPtr;
template<typename T>
class Blob {
    friend class BlobPtr<T>;

public:
    // 对于类容器类型，需要定义某些类型成员
    typedef T value_type;
    typedef typename std::vector<T>::size_type size_type;

    Blob(): _data(my_make_shared<std::vector<T>>()) {}
    Blob(std::initializer_list<T> il): _data(my_make_shared<std::vector<T>>(il)) {}
    Blob(const Blob &) = default;
    ~Blob() = default;

    template <typename Iterator>
    Blob(Iterator bgit, Iterator edit);

    bool empty() const  {   return _data->empty();  }
    size_type size() const   {   return _data->size();   }
    void push_back(const value_type &val)    {   _data->push_back(val);  }
    void push_back(value_type &&val)    {   _data->push_back(std::move(val));   }
    void pop_back();

    T& front();
    const T& front() const;
    T& back();
    const T& back() const;

    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;

private:
    void check(std::size_t index, const std::string &msg) const;

    Shared_ptr<std::vector<T>> _data;  // 指向vector数组的智能指针
};

template <typename T>
template <typename Iterator>
Blob<T>::Blob(Iterator bgit, Iterator edit):
    _data(my_make_shared<std::vector<T>>(bgit, edit)) {}

template<typename T>
inline void Blob<T>::check(std::size_t index, const std::string &msg) const
{
    if(index >= size())
        throw std::out_of_range(msg);
}

template<typename T>
inline void Blob<T>::pop_back()
{
    check(0, "pop_back from empty vector");
    _data->pop_back();
}

template <typename T>
inline T &Blob<T>::front()
{
    check(0, "front in then empty vector");
    return _data->front();
}

template<typename T>
inline const T& Blob<T>::front() const
{
    check(0, "front in the empty vector");
    return _data->front();
}

template<typename T>
inline T& Blob<T>::back()
{
    check(0, "search back in the empty vector");
    return _data->back();
}

template<typename T>
inline const T& Blob<T>::back() const
{
    check(0, "search back in the empty vector");
    return _data->back();
}

template<typename T>
inline T& Blob<T>::operator[](std::size_t sz)
{
    check(sz, "operator[] access invalid index in the vector");
    return (*_data)[sz];
}

template<typename T>
inline const T& Blob<T>::operator[](std::size_t sz) const
{
    check(0, "operator[] access invalid index in the vector");
    return (*_data)[sz];
}

#endif