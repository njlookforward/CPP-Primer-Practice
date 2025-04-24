#include <atomic>
using std::atomic;

#include <iostream>
using std::cout; using std::endl;

struct A {
    float f;
    int i;
    long long ll;
};

/// @bug 出现链接错误，编译时需要加上编译参数-latomic， 添加libatomic库
/// @return 
int main()
{
    atomic<A> obj;
    cout << std::boolalpha << obj.is_lock_free() << endl;

    return 0;
}