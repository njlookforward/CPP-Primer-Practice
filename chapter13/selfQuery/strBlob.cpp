#include "strBlob.hpp"

using namespace std;

strBlob &strBlob::operator=(const strBlob &rhs)
{
    if(this != &rhs)
        _data.reset(new strVec(*rhs._data));
    
    return *this;
}

String &strBlob::front()
{
    check(0, "front on empty vector<String>");

    return _data->front();
}

String &strBlob::back()
{
    check(0, "back on empty vector<String>");

    return _data->back();
}

const String &strBlob::front() const
{
    check(0, "front on empty vector<String>");

    return _data->front();
}

const String &strBlob::back() const
{
    check(0, "back on empty vector<String>");

    return _data->back();
}

void strBlob::pop_back()
{
    check(0, "pop_back in empty vector<String>");

    _data->pop_back();
}

String &strBlob::operator[](size_t pos)
{
    check(pos, "error position to query in vector<String>");

    return (*_data)[pos];
}

const String &strBlob::operator[](size_t pos) const
{
    return (*_data)[pos];
}

strBlobPtr strBlob::begin()
{
    return strBlobPtr(*this);
}

strBlobPtr strBlob::end()
{
    return strBlobPtr(*this, size());
}

strBlobPtr strBlob::begin() const
{
    return strBlobPtr(*this);
}

strBlobPtr strBlob::end() const
{
    return strBlobPtr(*this, size());
}

void strBlob::check(size_t sz, String msg) const
{
    if(sz >= _data->size())
        throw out_of_range(msg.c_str());
}

std::ostream &operator<<(std::ostream &os, const strBlob &sb)
{
    for (const auto &entry : *sb._data)
    {
        os << entry << " ";
    }
    return os;
}

const String &strBlobPtr::operator*() const
{
    auto ret = check(_pos, "dereference past end of strBlob");
    return (*ret)[_pos];
}

String &strBlobPtr::operator*()
{
    shared_ptr<strVec> sp = check(_pos,"dereference fail");
    return (*sp)[_pos];
}

strBlobPtr &strBlobPtr::operator++()
{
    check(_pos, "increment past end of strBlobPtr");
    ++_pos;

    return *this;
}

strBlobPtr strBlobPtr::operator++(int)
{
    check(_pos, "behind increment past end of strBlobPtr.");
    strBlobPtr tmp(*this);
    ++_pos;
    return tmp;
}

strBlobPtr &strBlobPtr::operator--()
{
    --_pos;
    check(_pos, "decrease excel the bound.");
    return *this;
}

strBlobPtr strBlobPtr::operator--(int)
{
    strBlobPtr ret(*this);
    --_pos;
    // if pos = -1, the value conveyed to check is a tremendous value because pos is size_t type, -1 is max
    check(_pos, "decrease excel the bound.");
    return ret;
}

const String &strBlobPtr::deref(size_t dis) const
{
    auto sp = check(_pos + dis, "dereference of a distance excel the bound.");
    return (*sp)[_pos + dis];
}

shared_ptr<strVec> strBlobPtr::check(size_t pos, String msg) const
{
    // 经过多重检查
    auto sp = _pd.lock();
    if(!sp)
        throw runtime_error("weak_ptr's point resource is being free.");
    if(pos >= sp->size())
        throw out_of_range(msg.c_str());
    
    return sp;
}

// const String &ConstStrBlobPtr::operator*()
// {
//     auto ret = check("dereference past end of strBlob");
//     return (*ret)[_pos];
// }

// ConstStrBlobPtr &ConstStrBlobPtr::operator++()
// {
//     check("increment past end of strBlob");
//     ++_pos;
//     return *this;
// }

// std::shared_ptr<strVec> ConstStrBlobPtr::check(const String &msg) const
// {
//     auto ret = _pcd.lock();
//     if(!ret)
//         throw runtime_error("weak_ptr's resource has been free.");
//     if(_pos >= ret->size())
//         throw out_of_range(msg);
    
//     return ret;
// }
