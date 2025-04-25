#include <atomic>
using std::atomic;

#include <iostream>
using std::cout; using std::endl;

struct A {
    float f;
    int i;
    long long ll;
};

struct B {
    int x;
    float y;
};

/// @bug 出现链接错误，编译时需要加上编译参数-latomic， 添加libatomic库
/// @attention 原子操作的可行性取决于具体的CPU架构，以及所实例化的类型结构能否满足该CPU架构对内存对齐条件的要求
int main()
{
    atomic<A> a;
    atomic<B> b;
    cout << std::boolalpha << a.is_lock_free() << endl
         << b.is_lock_free() << endl;
    /// @brief 经过试验，说明该CPU架构对无锁原子操作的最大大小为8bytes

    return 0;
}