#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <iostream>
#include <string>
#include <vector>

size_t _height = 1;
// exercise_7_23
class Screen {
    friend class Window_mgr;    // 友元类
    // friend void Window_mgr::clear(screenIndex); // 友元成员函数,不行的会出各种问题

public:
    using pos = std::string::size_type; // 类型成员，必须在使用之前进行定义

    // exercise_7_24
    Screen() = default;
    Screen(pos ht, pos wd): _height(ht), _width(wd), _contents(ht*wd, ' ') {}
    Screen(pos ht, pos wd, char ch):
        _height(ht), _width(wd), _contents(ht*wd, ch) {}
    Screen(pos ht, pos wd, const std::string &str):
        _height(ht), _width(wd), _contents(str) {}

    char get() const {   return _contents[_cursor];  }   // 隐式内联成员函数
    inline char get(pos ht, pos wd) const;  // 显式内联函数
    Screen &move(pos ht, pos wd);
    Screen &set(char ch);
    Screen &set(pos row, pos col, char ch);

    Screen &display(std::ostream &os)
    {
        std::cout << "Screen & edition: ";
        do_display(os);
        std::cout << std::endl;
        return *this;
    }
    const Screen &display(std::ostream &os) const
    {
        std::cout << "const Screen & edition: ";
        do_display(os);
        std::cout << std::endl;
        return *this;
    }

    // exercise_7_33
    pos size() const;

    // 验证mutable data member
    void some_member() const;

    // class scope
    Screen &dummy_fcn(pos _height)
    {
        // _cursor = _width * _height;  // is parameter
        // _cursor = _width * this->_height;    // is data member
        _cursor = _width * Screen::_height; // is data member
        // _cursor = _width * ::_height;   // global argument
        return *this;
    }

    void setHeight(pos);
    pos height = 0;

    Screen &clear(char = backgrd); // 可以用静态成员作为默认实参

private:
    void do_display(std::ostream &os) const {   os << _contents;    }

    pos _cursor = 0;       // 光标位置
    pos _height = 0;       // 高度
    pos _width  = 0;       // 宽度
    std::string _contents; // 屏幕内容

    mutable size_t _access_ctl = 0; // 被调用次数

    static const char backgrd;  
};

class Window_mgr {
public:
    // 由于是友元类，可以对指定位置的屏幕进行清屏
    using screenIndex = std::vector<Screen>::size_type;
    screenIndex insert(const Screen &s);
    void clear(screenIndex);

private:
    std::vector<Screen> screens{Screen(24, 80, "NanJiang is Practising C++")};
    // 因为要使用完整的Screen类型，因此不能用forward declaration
};

char Screen::get(pos ht, pos wd) const
{
    some_member();
    pos row = ht * _width;  // 行
    return _contents[row+wd];   // 行中的列
}

inline Screen &Screen::move(pos ht, pos wd)
{
    some_member();
    pos row = ht * _width;
    _cursor = row + wd;
    return *this;
}

inline Screen &Screen::set(char ch)
{
    _contents[_cursor] = ch;
    return *this;
}

inline Screen &Screen::set(pos row, pos col, char ch)
{
    _contents[row * _width + col] = ch;
    return *this;
}

// exercise_7_33
// 定义在类外部需要添加类作用域
inline Screen::pos
Screen::size() const
{
    return _height * _width;
}

inline void Screen::some_member() const
{
    ++_access_ctl;
    std::cout << "Screen::some_member() is called " << _access_ctl << " times." << std::endl;
}

inline Window_mgr::screenIndex
Window_mgr::insert(const Screen &s)
{
    screens.push_back(s);
    return screens.size() - 1;
}

inline void Window_mgr::clear(screenIndex i)
{
    Screen &s = screens[i];
    s._contents = std::string(s._height * s._width, ' ');
}

inline Screen::pos varify(Screen::pos var)
{
    return var - 1;
}

inline void Screen::setHeight(pos var)
{
    height = varify(var);
}

#endif  // SCREEN_HPP