#ifndef UNIQUE_PTR_HPP
#define UNIQUE_PTR_HPP

// 大胆尝试，不要害怕，一步一步走，一步一步想就可以实现的
#include <memory>
#include <stdexcept>

// 对于Unique_ptr来说，它是类模板，因此必须显示传入模板参数，而不是像函数模板那样编译器可以根据传入的参数隐式推断
template <typename T, typename Deleter = std::default_delete<T>>
class Unique_ptr {
public:
    Unique_ptr() = default;
    // 有问题，万一类型是函数指针呢，所以有问题，但可能也是自己想多了
    // 是自己想多了，如果使用Unique_ptr, 传入删除器类型，那么也必须向构造函数传递删除器初始化参数
    // 而且这样做是只要你使用删除器类型实例化Unique_ptr类模板了，就必须传入删除器对象用来初始化
    explicit Unique_ptr(T *p, Deleter d = Deleter()): _pv(p), _deleter(d) {}

    Unique_ptr(const Unique_ptr&) = delete;
    // Bug: 这种马虎错误，不能再犯了，竟然没有写=这个类型限定符，可恶啊
    Unique_ptr &operator=(const Unique_ptr &) = delete;
    // 移动控制语义我没有删除，因为unique_ptr可以使用返回值赋予新值

    ~Unique_ptr() {
        if(_pv)
            _deleter(_pv);
    }

    T& operator*() const {
        if(!_pv)
            throw std::runtime_error("deference is invalid because nullptr");
        return *_pv;
    }

    T* operator->() const {
        if(!_pv)
            throw std::runtime_error("Unique_ptr<T>::operator->() invalid: nullptr");
        return _pv;
    }

    // Bug: 我竟然没写operator，这才是类型转换运算符
    explicit operator bool() const { return _pv; }

    // BUG: 这个也写错了
    void reset(T *np) {
        if(_pv)
        {
            _deleter(_pv);
            // _pv = np;
        }
        _pv = np;   // 应该写在if的外面，因为如果Unique_ptr本来就是空的指针，可以直接赋值
    }

    T* release() {
        T* q = _pv;
        _pv = nullptr;
        return q;
    }

private:
    T *_pv = nullptr;
    Deleter _deleter;   // 这是与shared_ptr的不同，shared_ptr保存的是指针，而unique_ptr是直接是删除器的类型的函数对象
    // 这是在编译期完成的事情
};


#endif