#include "String.hpp"
using namespace std;

allocator<char> String::_alloc;

String::String(const char *cstr)
{
    auto bound = alloc_n_copy(cstr, cstr + strlen(cstr));
    _elements = bound.first;
    _first_free = _cap = bound.second;
}

String::String(const String &rhs)
{
    auto bound = alloc_n_copy(rhs._elements, rhs._first_free);
    _elements = bound.first;
    _first_free = _cap = bound.second;

    cout << "String(const String &rhs)" << endl;
}

String &String::operator=(const String &rhs)
{
    cout << "String &operator=(const String &rhs)" << endl;

    auto bound = alloc_n_copy(rhs._elements, rhs._first_free);
    free();
    _elements = bound.first;
    _first_free = _cap = bound.second;

    return *this;
}

String::String(String &&rhs) noexcept
: _elements(rhs._elements), _first_free(rhs._first_free), _cap(rhs._cap)
{
    cout << "String(String &&)" << endl;

    rhs._elements = rhs._first_free = rhs._cap = nullptr;
}

String &String::operator=(String &&rhs) noexcept
{
    cout << "String &operator=(String &&)" << endl;
    if(this != &rhs)
    {
        free();
        _elements = rhs._elements;
        _first_free = rhs._first_free;
        _cap = rhs._cap;

        rhs._elements = rhs._first_free = rhs._cap = nullptr;
    }
    return *this;
}

void String::push_back(char ch)
{
    check_space();

    _alloc.construct(_first_free++, ch);
}

void String::pop_back()
{
    if(empty())
        throw runtime_error("String::pop_back() in the empty String.");
    
    _alloc.destroy(--_first_free);
}

const char *String::c_str()
{
    check_space();
    _alloc.construct(_first_free++, '\0');
    // 这里假设使用了c_str()的字符串，后面就不会被操作了

    return _elements;
}

String &String::operator+=(const String &rhs)
{
    if(size() + rhs.size() <= capacity())
    {
        _first_free = uninitialized_copy(rhs._elements, rhs._first_free, _first_free);
    }
    else
    {
        auto newbg = _alloc.allocate(size() + rhs.size());
        auto newFirFree = uninitialized_copy(_elements, _first_free, newbg);
        newFirFree = uninitialized_copy(rhs._elements, rhs._first_free, newFirFree);
        free();
        _elements = newbg;
        _first_free = _cap = newFirFree;
    }

    return *this;
}

String &String::operator+=(const char &ch)
{
    check_space();
    _alloc.construct(_first_free++, ch);
    return *this;
}

void String::free()
{
    if(_elements)   // 说明有申请的动态内存空间
    {
        while (_first_free != _elements)    // 说明有需要进行析构的元素
        {
            _alloc.destroy(--_first_free);
        }
        _alloc.deallocate(_elements, capacity());

        _elements = _first_free = _cap = nullptr;   // 出现error，动态数组释放后，必须变为nullptr
        // 否则会干扰到后续的重新分配。任何程序的设计都要逻辑完整，否则会出现数不清的问题
        // 对于free，就是要释放动态内存，然后让指针归零
    }
}

void String::check_space()
{
    if(_first_free == _cap)
        reallocate();
}

void String::reallocate()
{
    size_t newsz = size() ? size() * 2 : 1;
    auto newbg = _alloc.allocate(newsz);
    auto newFirFree = uninitialized_copy(_elements, _first_free, newbg);
    free();
    _elements = newbg;
    _first_free = newFirFree;
    _cap = newbg + newsz;
}

std::pair<char *, char *> String::alloc_n_copy(const char *b, const char *e)
{
    auto bgit = _alloc.allocate(e - b);
    return {bgit, uninitialized_copy(b, e, bgit)};
}

std::istream &operator>>(std::istream &is, String &str)
{
    // 不要给自己的思考增加难度，就从最基本的思考方向出发
    str.free(); // 出现error，每次重新输入时，都是一个覆盖的过程
    char ch;
    while (is.get(ch))
    {
        if(!isspace(ch))
            str.push_back(ch);
        else
            break;    
    }

    return is;
}

std::ostream &operator<<(std::ostream &os, const String &str)
{
    for (auto &ch : str)
    {
        os << ch;
    }
    return os;
}

std::istream &getline(std::istream &is, String &str)
{
    str.free(); // 出现error，每次的重新输入都是一个覆盖的过程
    char ch;
    while (is.get(ch))
    {
        if(ch != '\n')
            str.push_back(ch);
        else
            break;    
    }
    
    return is;
}

bool operator<(const String &lhs, const String &rhs)
{
    for(auto bg1 = lhs.begin(), bg2 = rhs.begin();
        bg1 != lhs.end() && bg2 != rhs.end(); ++bg1, ++bg2)
    {
        if(*bg1 < *bg2)
            return true;
        else if(*bg1 > *bg2)
            return false;
    }
    if(lhs.size() < rhs.size())
        return true;
    else
        return false;
}

bool operator==(const String &lhs, const String &rhs)
{
    if(lhs.size() != rhs.size())
        return false;
    for(auto bg1 = lhs.begin(), bg2 = rhs.begin();
        bg1 != lhs.end(); ++bg1, ++bg2)
    {
        if(*bg1 == *bg2)
            continue;
        else
            return false;
    }

    return true;
}

bool operator!=(const String &lhs, const String &rhs)
{
    return !(lhs == rhs);
}

String operator+(const String &lhs, const String &rhs)
{
    String sum(lhs);
    sum += rhs;

    return sum;
}
