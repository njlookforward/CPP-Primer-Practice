#include "Sales_data.hpp"
#include <typeinfo>
#include <cxxabi.h>

using namespace std;

void exercise_2_1()
{
    // short是短整数，一般是2Byte，int是整数，一般是4B，long是长整数，一般是4Byte，int与long几乎没有区别
    // long long是扩展长整数，C++11新设立的，当数据超出int的表示范围时，选择用long long作为整数数据类型
    // long long是8Byte吗？
    // 由于不同整数的数据类型所占内存大小不同，因此所能表示的数据范围也不同，但都是带符号整数
    /****************/
    // 无符号整数只能表示大于等于0的整数，带符号整数能表示负数、0、正数；
    // float是单精度浮点数，double是双精度浮点数，float一般是4Byte，double一般是8Byte
    // double能表示的数据范围更大，精度更高，浮点数类型尽量选择double，两者的计算速度相差无几，甚至计算double类型的速度更快
}

void exercise_2_2()
{
    // 计算按揭贷款时，利率肯定是要选择double类型，而且小数点精度尽可能的提高，本金和付款可以选择float、double等类型
    // 尽可能使用double
}

void exercise_2_5()
{
    // (a) 'a' - char  L'a' - wchar_t "a" - char L"a" - wchar_t, char8bit, wchar_t16bit
    // auto d = 3.144; // d 是double类型
}

void exercise_2_7()
{
    std::cout << "Who goes with F\145rgus?\012" << 3.14e1L << std::endl;
}

void exercise_2_8()
{
    std::cout << "2\115\012" 
              << "2\t\x4d\012";
}

void exercise_2_18()
{
    double *pd = nullptr, d1 = 3.1415;
    pd = &d1;
    *pd = 5.26;
}

void exercise_2_19()
{
    // 1.定义引用时必须初始化，要绑定到类型匹配的对象，而定义指针时可以不初始化，可以初始化为空指针，不指向任何对象
    // 2.引用一旦定义后无法改变所绑定的对象，而指针是可以通过赋值操作改变指针的值，
    // 3.引用与指针都是复合类型，间接指向对象，引用一定有对象，而每次使用指针时要判断是否为空指针
}

void exercise_2_35()
{
    const int ci = 42;
    auto j = ci;
    const auto &k = ci;
    auto *p = &ci;
    const auto j2 = ci, &k2 = ci;
    std::cout << abi::__cxa_demangle(typeid(ci).name(), 0, 0, 0) << std::endl;    // const int
    std::cout << abi::__cxa_demangle(typeid(j).name(), 0, 0, 0) << std::endl;
    std::cout << abi::__cxa_demangle(typeid(k).name(), 0, 0, 0) << std::endl;
    std::cout << abi::__cxa_demangle(typeid(p).name(), 0, 0, 0) << std::endl;
    std::cout << abi::__cxa_demangle(typeid(j2).name(), 0, 0, 0) << std::endl;
    std::cout << abi::__cxa_demangle(typeid(k2).name(), 0, 0, 0) << std::endl;
    // std::cout << typeid(j).name() << std::endl;     // int
    // std::cout << typeid(k).name() << std::endl;     // const int&
    // std::cout << typeid(p).name() << std::endl;     // const int*
    // std::cout << typeid(j2).name() << std::endl;    // const int
    // std::cout << typeid(k2).name() << std::endl;    // const int&
}

void  exercise_2_37()
{
    int a = 3, b = 4;
    decltype(a) c = a;
    decltype(a = b) d = a;
    cout << abi::__cxa_demangle(typeid(c).name(), 0, 0, 0) << " = " << c << endl;   // int
    cout << abi::__cxa_demangle(typeid(d).name(), 0, 0, 0) << " = " << d << endl;   // int&
}

void exercise_2_38()
{
    // decltype与auto的区别：
    // 1.const问题：auto会忽略顶层const，还原为基础类型，decltype会保存顶层const
    // 2.reference问题：auto会忽略reference，还原为基础类型，decltype会保存reference
}

// struct Foo {};
void exercise_2_41()
{
    Sales_data sumBook;
    if(std::cin >> sumBook)
    {
        Sales_data curBook;
        while (std::cin >> curBook)
        {
            if(compareISBN(sumBook, curBook))
            {
                sumBook += curBook;
            }
            else
            {
                std::cout << sumBook;
                sumBook = curBook;
            }
        }
        std::cout << sumBook;
    }
    else
    {
        std::cerr << "No data?" << std::endl;
    }
}

int main()
{
    // exercise_2_7();
    // exercise_2_8();
    // exercise_2_18();
    // exercise_2_35();
    exercise_2_37();
    // exercise_2_41();
    // double slavery, wage; 
    // slavery = wage = 9999.99;

    return 0;
}