#ifndef EXAMPLE_HPP
#define EXAMPLE_HPP

#include <vector>

class Example {
public:
    // 由于rate是non-const类型，只能在初始化的过程中被赋予值
    static double rate;
    static const int vecSize = 20;  // 只有静态常量成员可以在类内初始化。其他静态成员不能类内初始化
    static std::vector<double> vec;
    // 类内初始值只能= or {}进行赋值，用() is invalid because it is recognised function
    // 因此若要定义vec的容量在初始化的过程中进行定义
};

#endif  // EXAMPLE_HPP