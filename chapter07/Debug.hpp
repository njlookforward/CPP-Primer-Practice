#ifndef DEBUG_HPP
#define DEBUG_HPP

// exercise_7_53
class Debug {
public:
    constexpr Debug(bool b = true):_hw(b), _io(b), _other(b) {}
    constexpr Debug(bool h, bool i, bool o) :
        _hw(h), _io(i), _other(o) {}
    
    constexpr bool any() const   {   return _hw || _io || _other;    }  // constexpr函数只有一条return语句，且参数和返回值都是字面值常量类型
    void set_io(bool b)     {   _io = b;    }
    void set_hw(bool b)     {   _hw = b;    }
    void set_other(bool b)  {   _other = b; }
    // exercise_7_54
    // set_## member不应该被声明为constexpr，因为set类成员的功能是修改数据成员，而constexpr是字面值常量对象，是无法被修改的
    // 因此这是冲突的

private:
    bool _hw;    // hardware error
    bool _io;    // io error
    bool _other; // other error
};

#endif  // DEBUG_HPP