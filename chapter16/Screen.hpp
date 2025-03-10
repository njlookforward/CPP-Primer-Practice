#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <iostream>
#include <string>

// 不要害怕，不要怕麻烦，写出来了就不怕了
// exercise_16_14 练习非类型模板函数
template <int, int> class Screen;   // Bug：这个前置声明忘记了
template <int H, int W>
std::ostream &operator<<(std::ostream &os, const Screen<H, W> &s);
template <int H, int W>
std::istream &operator>>(std::istream &is, Screen<H, W> &s);
template <int H, int W>
class Screen {
    friend std::ostream &operator<< <H, W>(std::ostream &os, const Screen<H, W> &s);
    friend std::istream &operator>><H, W>(std::istream &is, Screen<H, W> &s);
public:
    Screen(): _contents(H * W, ' ') {}
    Screen(char c): _contents(H * W, c) {}
    ~Screen() = default;

    // 接下来如何设计类的问题了，就是围绕数据成员定义自己的各种接口
    // get rarely access contents in the cursor
    char get() const {  return _contents[_cursor]; }    // 隐式内联
    inline char get(int r, int c) const;                // 显式内联

    // modify _cursor or other index's character
    Screen &set(char);              // 类外定义也是内联函数
    Screen &set(int, int, char);
    Screen &move(int r, int c)  {   _cursor = r * W + c;    return *this;   }
    Screen &clear(char = bkground);

private:
    // Bug: 对于const成员函数返回自身，返回类型应该是const Screen<>&
    const Screen& display(std::ostream &os) const;

    int _cursor = 0;
    std::string _contents;

    static const char bkground = ' ';   // 只能针对const/constexpr静态数据成员进行类内初始化，也需要在类外进行定义
};

template <int H, int W>
const char Screen<H, W>::bkground;  // 类外定义时就不需要再次进行初始化了

template <int H, int W>
inline char Screen<H, W>::get(int r, int c) const 
{
    int row = r * W;
    return _contents[row + c];
}

template <int H, int W>
inline Screen<H, W>& Screen<H, W>::set(char ch)
{
    _contents[_cursor] = ch;
    return *this;
}

template <int H, int W>
inline Screen<H, W>& Screen<H, W>::set(int r, int c, char ch)
{
    _contents[r * W + c] = ch;
    return *this;
}

template <int H, int W>
inline Screen<H, W>& Screen<H, W>::clear(char ch)
{
    _contents = std::string(H * W, ch);
    return *this;
}

template <int H, int W>
inline const Screen<H, W>& Screen<H, W>::display(std::ostream &os) const
{
    for(int i = 0; i < H; ++i)
    {
        // Bug: substr()记错了，substr(pos, n);
        if(i < H - 1)
            os << _contents.substr(i * W, W) << std::endl;
        else
            os << _contents.substr(i * W, W);
    }
    return *this;
}

template <int H, int W>
std::ostream &operator<<(std::ostream &os, const Screen<H, W> &s)
{
    s.display(os);
    return os;
}

template <int H, int W>
std::istream &operator>>(std::istream &is, Screen<H, W> &s)
{
    std::string str;
    is >> str;
    s._contents = str.substr(0, H*W);
    return is;
}

#endif