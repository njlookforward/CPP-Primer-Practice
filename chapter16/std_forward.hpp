#ifndef STD_FORWARD_HPP
#define STD_FORWARD_HPP

#include <iostream>
#include <utility>
#include <memory>

// 做这个练习就是重复std::forward的单元练习，里面会涉及到可变模版参数、动态内存unique_ptr，自定义类的组合等等知识
struct A
{
    A(int &n)   {   std::cout << "lvalue overload, n = " << n << std::endl; }
    A(int &&n)  {   std::cout << "rvalue overload, n = " << n << std::endl; }
};

struct B
{
    // B的构造函数是一个模版函数，而且要保留实参的实际类型，必须用模版参数的右值引用
    template <typename T1, typename T2, typename T3>
    B(T1 &&n1, T2 &&n2, T3 &&n3):
        _a1{std::forward<T1>(n1)},
        _a2{std::forward<T2>(n2)},
        _a3{std::forward<T3>(n3)} {}
private:
    A _a1, _a2, _a3;
};

template <typename U, class T>
std::unique_ptr<U> make_unique1(T &&n)
{
    return std::unique_ptr<U>(new U(std::forward<T>(n)));
}

template <typename U, class ... Args>
std::unique_ptr<U> make_unique2(Args&& ... args)
{
    // unique_ptr<U>是不能够拷贝的，但唯一的例外就是可以作为函数的返回值，仍然保持唯一性
    return std::unique_ptr<U>(new U(std::forward<Args>(args) ...));
}

#endif