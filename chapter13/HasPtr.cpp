#include "HasPtr.hpp"
using namespace std;

HasPtr::HasPtr(HasPtr &&rhs) noexcept
: _ps(rhs._ps), _index(rhs._index)
{
    rhs._ps = nullptr;
    // 移动资源之后，要保证右值能够安全析构
    // cout << "HasPtr(HasPtr &&)" << endl;
}

HasPtr &HasPtr::operator=(const HasPtr &rhs)
{
    cout << "HasPtr &HasPtr=(const HasPtr &)" << endl;
    // 一定要考虑到自赋值的情况，要考虑全面
    std::string *ptr = new std::string(*rhs._ps);
    delete _ps;
    _ps = ptr;
    _index = rhs._index;

    return *this;
}

HasPtr &HasPtr::operator=(HasPtr &&rhs) noexcept
{
    cout << "HasPtr &operator=(HasPtr &&)" << endl;

    if(this != &rhs)
    {
        delete _ps;
        _ps = rhs._ps;
        _index = rhs._index;
        rhs._ps = nullptr;

        // return *this;    // error, end of function don't have return value
    }
    return *this;
}

// HasPtr &HasPtr::operator=(HasPtr rhs)
// {
//     // cout << "HasPtr &operator=(HasPtr)" << endl;
//     using std::swap; // 这是必须写的，实现swap的函数重载，再库函数和自定义函数的匹配
//     swap(*this, rhs);
//     return *this;    // 永远不要忘记返回值
// }

void swap(HasPtr &lhs, HasPtr &rhs)
{
    using std::swap;
    swap(lhs._ps, rhs._ps);
    swap(lhs._index, rhs._index);

    cout << "swap(HasPtr &, HasPtr &)" << endl;
}

bool operator<(const HasPtr &lhs, const HasPtr &rhs)
{
    return *lhs._ps < *rhs._ps;
}

std::ostream &operator<<(std::ostream &os, const HasPtr &rhs)
{
    os << *rhs._ps;
    return os;
}

HasPtr fcn_rval(HasPtr hp)
{
    HasPtr ret = hp;
    ret.mystr() = "NANJIANG";

    return ret;
}

void swap(Phasptr &lhs, Phasptr &rhs)
{
    using std::swap;
    swap(lhs._ps, rhs._ps);
    swap(lhs._index, rhs._index);
    swap(lhs._cnt, rhs._cnt);
}

Phasptr &Phasptr::operator=(const Phasptr &rhs)
{
    ascendCnt(rhs);
    descendCnt();
    _ps = rhs._ps;
    _index = rhs._index;
    _cnt = rhs._cnt;

    return *this;
}

void Phasptr::descendCnt()
{
    if(--*_cnt == 0)
    {
        // 只要引用计数为0，就需要释放本对象所拥有的所有资源
        // 如果是被赋值运算符调用，一旦为0，也需要释放所有资源，然后指向别人的资源
        delete _ps;
        delete _cnt;
    }
}
