#ifndef VEC_HPP
#define VEC_HPP

// 需要自定义vector类型，需要使用memory
// 没有那么困难，需要认真的去想，然后快速的行动
#include <memory>
#include <initializer_list>
#include <cstddef>
#include <utility>
#include <stdexcept>

template<typename T> class Vec {
public:
    typedef T value_type;

    Vec() = default;
    Vec(std::initializer_list<T> il);
    Vec(const Vec& rhs);
    Vec(Vec &&) noexcept;
    // Bug: 对于移动语义的函数不要忘记noexcept
    Vec &operator=(const Vec &rhs);
    Vec &operator=(Vec &&rhs) noexcept;

    ~Vec() noexcept {    clear();    }
    
    std::size_t size() const        {   return _first_free - _elements; }
    std::size_t capacity() const    {   return _cap - _elements;        }
    bool empty() const {    return _elements == _first_free;    }

    void push_back(const T&);
    void push_back(T &&);
    T* insert(T* pos, const T&);
    T* insert(T* pos, T&&);

    template <class... Args>
    void emplace_back(Args&&... args);

    void pop_back();

    // Bug3: 当Vec为空时就调用begin() or end() only return nullptr(0), 总会出错的，因此需要先进行判断
    // 其实应该单独定义为空时的问题
    T *begin();             
    const T *begin() const;
    T *end();               
    const T*end() const;    

private:
    std::pair<T*, T*> range_alloc_copy(const T*bgit, const T *edit);
    void clear();
    void check();

    static std::allocator<T> _alloc;    // 对于每一个实例化的类型，只有一个allocator就足够了

    T *_elements = nullptr;     
    T *_first_free = nullptr;
    T *_cap = nullptr;
};

template<typename T>
std::allocator<T> Vec<T>::_alloc;

template<typename T>
inline std::pair<T*, T*> Vec<T>::range_alloc_copy(const T*bgit, const T*edit)
{
    T *newElements = _alloc.allocate(edit - bgit);
    T *newEnd = std::uninitialized_copy(bgit, edit, newElements);
    return {newElements, newEnd};
}

template<typename T>
inline void Vec<T>::clear()
{
    if(_elements)
    {
        // 说明分配了内存，需要进行回收
        while (_first_free > _elements)
        {
            _alloc.destroy(--_first_free);
        }
        _alloc.deallocate(_elements, _cap - _elements);
        _elements = _first_free = _cap = nullptr;
    }
}

template<typename T>
inline void Vec<T>::check()
{
    if(!_elements)
    {
        _elements = _alloc.allocate(1);
        _first_free = _elements;
        _cap = _elements + 1;
    }
    if(_first_free == _cap)
    {
        auto newSize = size() * 2;
        T *newElements = _alloc.allocate(newSize);
        // T *newFirstFree = std::uninitialized_copy(_elements, _cap, newElements);
        // NO, 这里需要使用移动语义的构造函数
        T *newFirstFree = newElements;
        for(T *bgit = _elements; bgit < _first_free; ++bgit)
        {
            _alloc.construct(newFirstFree++, std::move(*bgit));
        }
        clear();
        _elements = newElements;
        _first_free = newFirstFree;
        _cap = _elements + newSize;
    }
}

// 记住这仍然是一种成员模板函数,要使用模板的写法
template<typename T>
inline Vec<T>::Vec(std::initializer_list<T> il) {
    auto newData = range_alloc_copy(il.begin(), il.end());
    _elements = newData.first;
    _first_free = _cap = newData.second;
}

// 因为已经进入Vec<T>的范围，因此参数不用写成Vec<T>
template<typename T>
inline Vec<T>::Vec(const Vec &rhs)
{
    // Bug1: 按照固有思维去写了。没有定义begin(rhs)，只是定义了rhs.begin()
    auto newData = range_alloc_copy(rhs.begin(), rhs.end());
    _elements = newData.first;
    _first_free = _cap = newData.second;
}

template<typename T>
inline Vec<T>::Vec(Vec &&rhs) noexcept
{
    // 移动语义就是转移资源，因此永远都不要想歪了，就是直接把资源转移走就行
    _elements = rhs._elements;
    _first_free = rhs._first_free;
    _cap = rhs._cap;

    rhs._elements = rhs._first_free = rhs._cap = nullptr;
}

template<typename T>
inline Vec<T>& Vec<T>::operator=(const Vec &rhs)
{
    if(this != &rhs)
    {
        // 说明不是自复制，可以直接进行复制操作，首先要删除自身拥有的资源，再申请新的资源
        clear();
        auto newData = range_alloc_copy(rhs.begin(), rhs.end());
        _elements = newData.first;
        _first_free = _cap = newData.second;
    }

    return *this;
}

template<typename T>
inline Vec<T>& Vec<T>::operator=(Vec &&rhs) noexcept
{
    if(this != &rhs)
    {
        // 说明不是自复制
        clear();
        _elements = rhs._elements;
        _first_free = rhs._first_free;
        _cap = rhs._cap;
        rhs._elements = rhs._first_free = rhs._cap = nullptr;
    }

    return *this;
}

template<typename T>
inline void Vec<T>::push_back(const T &val)
{
    check();
    _alloc.construct(_first_free++, val);
}

template<typename T>
inline void Vec<T>::push_back(T &&val)
{
    check();
    _alloc.construct(_first_free++, std::move(val));
}

template<typename T>
inline T* Vec<T>::insert(T *pos, const T&val)
{
    // check();
    if(pos < _elements || pos > _first_free)
        throw std::out_of_range("Vec<T>::insert(T*, const T&) use invalid pos.");
    if(pos != _first_free)
    {
        auto revBgit = _first_free - 1;
        _alloc.construct(_first_free++, *revBgit);
        for(; revBgit > pos; --revBgit)
            *revBgit = *(revBgit - 1);
        *pos = val;
    } else
        _alloc.construct(_first_free++, val);

    return pos;
}

template<typename T>
inline T* Vec<T>::insert(T *pos, T&& val)
{
    // check();
    if(pos < _elements || pos > _first_free)
        throw std::out_of_range("Vec<T>::insert(T*, T&&) has invalid pos");
    
    if(pos != _first_free)
    {
        T* revBgit = _first_free - 1;
        _alloc.construct(_first_free++, *revBgit);
        for(; revBgit > pos; --revBgit)
            *revBgit = *(revBgit - 1);
        *pos = std::move(val);
    } else
        _alloc.construct(_first_free++, std::move(val));

    return pos;
}

template <typename T>
template <class... Args>
inline void Vec<T>::emplace_back(Args&&... args)
{
    check();
    _alloc.construct(_first_free++, std::forward<Args>(args)...);
}


template<typename T>
inline void Vec<T>::pop_back()
{
    if(!_elements || _first_free == _elements)
        throw std::runtime_error("pop_back in the empty Vec");
    _alloc.destroy(--_first_free);
}

template <typename T>
inline T *Vec<T>::begin()
{
    // if(!_elements)
    check();
    return _elements;
}

template <typename T>
inline const T *Vec<T>::begin() const
{
    if(!_elements)
        throw std::runtime_error("this Vec don't alloc any memory, so cann't use begin()");
    return _elements;
}

template <typename T>
inline T *Vec<T>::end()
{
    // if(!_elements)
    // Bug4:出现了逻辑错误，应该在end中扩充容量，如果在insert中扩充容量，那么数组范围已经变成新的了
    // 而end返回的是已经被删除的数组范围，因此肯定发生错误
    check();
    return _first_free;
}

template <typename T>
inline const T *Vec<T>::end() const
{
    if(!_elements)
        throw std::runtime_error("this Vec don't alloc any memory, so cann't use end()");
    return _first_free;
}

// 我一定要定义自己的Vec::iterator

#endif

// Bug1: 按照固有思维去写了。没有定义begin(rhs)，只是定义了rhs.begin()
// Bug2: 不能使用c++20标准，因为allocator的construct和destroy被移除了
// Bug3: 没有考虑到当Vec没有申请任何空间时，begin和end函数的处理情况
// 对于一个迭代器来说，最基本要实现的是++ * -> != ==
// 对于一个前向迭代器++, 双向迭代器++ -- 随机访问迭代器+ += - [] < <= > >=
 // Bug: 对于const_iterator来说，不需要check()，因为const_iterator只是读取数据，不会写入后者插入数据