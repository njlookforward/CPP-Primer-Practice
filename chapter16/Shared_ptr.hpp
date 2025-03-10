#ifndef SHARED_PTR_HPP
#define SHARED_PTR_HPP

#include <functional>
#include <stdexcept>
#include <utility>

template <typename T>
class Shared_ptr {
public:
    Shared_ptr() = default;
    // Bug: 对于单形参的构造函数，需要定义为explicit
    explicit Shared_ptr(T *p): _pv(p), _cnt(new int(1)) {}
    
    template <typename D>
    Shared_ptr(T *p, D deleter): _pv(p), _cnt(new int(1)), _fcn(deleter) {}

    Shared_ptr(const Shared_ptr &rhs):
        _pv(rhs._pv), _cnt(rhs._cnt), _fcn(rhs._fcn) {
            // ++*_cnt;
        // BUG: 没有考虑到空指针问题
        if(rhs._cnt) ++*_cnt;   // 对象也可能是一个空指针，因此需要确定
    }

    Shared_ptr(Shared_ptr &&rhs):
        _pv(rhs._pv), _cnt(rhs._cnt), _fcn(rhs._fcn) {
            rhs._pv = rhs._cnt = nullptr;
            rhs._fcn = nullptr;
    }

    ~Shared_ptr() { free(); }

    Shared_ptr &operator=(const Shared_ptr& rhs);

    T& operator*() const {
        if(!_pv)
            throw std::runtime_error("Shared_ptr<T>::operator*(): Shared_ptr has nullptr, deference is invalid");
        return *_pv;
    }

    T* operator->() const {
        if(!_pv)
            throw std::runtime_error("Shared_ptr<T>::operator->(): Shared_ptr has nullptr, point no objection");
        return _pv;
    }

    template <typename D = std::function<void(T*)>>
    void reset(T *p = nullptr, D deleter = D()) {
        free();
        _pv = p;
        _cnt = new int(1);
        _fcn = deleter;
    }

    explicit operator bool() {  return _pv; }   // 显示的bool类型转换运算符

private:
    void free();

    T *_pv = nullptr;
    int *_cnt = nullptr;
    std::function<void(T*)> _fcn;   // 因为使用的是function，保存可调用对象的指针或者复制可调用对象，运行时调用
};

template <typename T>
void Shared_ptr<T>::free() {
    if(_cnt)
    {
        --*_cnt;
        if(*_cnt == 0)
        {
            _fcn ? _fcn(_pv) : (delete _pv);
            delete _cnt;
            _pv =  nullptr;
            // Bug: 不能写成_pv = _cnt = nullptr的形式
            _cnt = nullptr;
            _fcn = nullptr;
        }
    }
}

template <typename T>
Shared_ptr<T>& Shared_ptr<T>::operator=(const Shared_ptr &rhs)
{
    if(rhs._cnt)
        ++*_cnt;
    free();
    _pv = rhs._pv;
    _cnt = rhs._cnt;
    _fcn = rhs._fcn;

    return *this;
}

template <typename T, typename... Args>
Shared_ptr<T> make_Shared(Args&&... args)
{
    return Shared_ptr<T>(new T(std::forward<Args>(args)...));
}

#endif

// Bug: 不能写成_pv = _cnt = nullptr的形式，因为两个指针的类型是不一样的，指针类型不同不能进行赋值