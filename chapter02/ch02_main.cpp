#include "Sales_data.hpp"

void prog1_type_convert()
{
    bool b = 42;    // b = true
    int i = b;      // i = 1
    i = 3.14;       // i = 3
    double pi = i;  // pi = 3.0
    unsigned char c = -1;   // 按模计算的补数+1
    // signed char c2 = 256;   // signed char是8bit，最大能表示255，c2 = 0

    if(i)
        i = 0;
    
    // unsigned compute
    unsigned ui = 10;
    i = -42;
    std::cout << i+i << std::endl;
    std::cout << ui+i << std::endl; // 与无符号数计算，会将有符号数先转换为无符号数再计算2^32 - 42 + 10 = ui+i
    std::cout << ui-i << std::endl; // 42-2^32+10, 由于是负数，42 - 2^32 + 10 + 2^32 = 52 = 10 - (-42) = 52
    
    unsigned ui2 = 42;
    // 当从无符号数中减去一个数时，只要结果是正数，计算机的结果就是正确的，否则是取模后的结果
    std::cout << ui2 - ui << std::endl;
    std::cout << ui - ui2 << std::endl; // 10 - 42 = 2^32 - 42 + 10
    
    int i1 = 10, i2 = 42;
    std::cout << i1 - ui << std::endl;
    std::cout << ui - i1 << std::endl;
}

void pro2_literal()
{
    double pi = 3.14159;
    pi = 3.14159E0;
    pi = 0.;
    pi = 0e0;
    pi = .001;
    // 'a' "Hello World!"
    std::cout << "a really, really long string literal "
              << "that spans two lines" << std::endl;
    // 使用转义序列，可以八进制或十六进制设置
    std::cout << "Hi \x4dO\115\n" << "\vI'm your son.\7" << std::endl;
    // 可以通过前缀或后缀指定字面值类型
    wchar_t ch =  L'a';   // -- wchar_t
    char charr[] = u8"hi"; // -- UTF-8 string literal
    unsigned long long ull = 42ULL; // -- unsigned long long
    float f = 1E-3F;    // float
    double d = 3.14159L; // long double
}

void prog3_variable()
{
    // C++11加入了列表初始化，好处是使用列表初始化时若初始值存在丢失信息的风险，则编译器会报错
    int i1 = 0;
    int i2 = {1};
    int i3{2};  // list initialization
    int i4(3);

    long double ld = 3.1415926536;
    // int a{ld}, b = {ld};    // error, narrow convertion error
    int c(ld), d = ld;

    extern int i5;  // declaration
    // extern double pi = 3.1415926;   // definition
    int _ = 24;
}

// 说明全局/文件作用域和局部/块作用域的区别
int reused = 24;
void prog4_scope()
{
    int unique = 0;
    std::cout << reused << " " << unique << std::endl;
    int reused = 0;
    std::cout << reused << " " << unique << std::endl;  // block scope same name can override file scope
    std::cout << ::reused << " " << unique << std::endl;    // use :: specify file scope's same name
}

void prog5_reference()
{
    // reference is compound type, must initialization
    // &是声明符的一部分
    int i = 1024, i2 = 2048;
    int &r = i, r2 = i2;
    int i3 = 3072, &ri = i3;
    int &r3 = i3, &r4 = i2;
    // 除了const reference and base class reference, 所有的引用都要与所绑定对象的数据类型保持一致，不能绑定到字面值或者计算表达式的结果，只能绑定到对象
    // int &refVal1 = 10;  // error, cannot bind to a literal
    double pi = 3.14;
    // int &refVal2 = pi;  // cannot bind to a mismatch type
}

void prog6_pointer()
{
    // 除两种情况外，所有指针都要与所指对象的数据类型严格匹配
    // 一种是const pointer can point to non-const object, 另一种是base pointer can point to inheritant
    double dval = 3.14;
    double *pd = &dval;
    double *pd2 = pd;

    void *pv = &dval;
    pv = pd;

    // int *pi = pd;
    // pi = &dval;
    int *p1 = 0;
    int *p2 = nullptr;
    int *p3 = NULL;
    int zero = 0;
    // p3 = zero;
    pv = p1;

}

void prog7_compoundType()
{
    // 指向指针的指针
    int ival = 1024;
    int *pi = &ival;
    int **ppi = &pi;
    // 指向指针的引用
    int *&rpi = pi;
    std::cout << "direct val: " << ival << std::endl
              << "indirect val: " << *pi << std::endl
              << "double indirect val: " << **ppi << std::endl
              << "reference to poniter:" << *rpi << std::endl;
}

void prog8_const()
{
    std::cout << "const int value:\t" << bufSize << std::endl;
    const int ci = 1024;
    const int &rci1 = ci;
    // rci1 = 512;   // error
    // int &ri = ci;   // error
    // 常量引用的特别之处
    int i = 42;
    const int &rci2 = i;    // const int& can bind to int
    int &ri1 = i;
    ri1 = 46;
    const int &rci3 = 43;   // const int& can bind ti literal
    const int &rci4 = 22 * 2;   // const int& can bind to expression's result
    // int &ri = 42;   // error, int& cannot bind to literal

    double d = 3.1415926;
    const int &rci5 = d;
    // const int tmp = d;
    // const int&rci5 = tmp;

    /*************pointer and const**************/
    // ponit to const
    const double pi = 3.14;
    // double *ptr = &pi;  // error
    const double *cptr = &pi;
    std::cout << "*cptr = " << *cptr << std::endl;
    // *cptr = 4.7;  // error
    cptr = &d;
    std::cout << "after alter: *cptr = " << *cptr << std::endl;
    
    // const pointer
    int errNum = 48;
    int *const curErr = &errNum;
    // curErr = &i;    // error
    const double *const ccptr = &pi;

    // top-level const and low-level const
    int *const p1 = &i;     // top const
    const int *p2 = &ci;    // low const
    const int *const p3 = p2;   // left const is low const, right const is top const
    const int &r11 = ci;    // reference const is all low const

    // int *p4 = p3;   // error, p3 has low const
    p2 = p3;
    p2 = &i;
    // int &r12 = ci;  // error
    const int &r13 = i;
}

constexpr int Size()
{   return 1024;    }

void prog9_constexpr()
{
    constexpr int mf = 20;  // complie const expression
    constexpr int limit = mf + 1;   // compile const expression
    constexpr int sz = Size();  // run-time const expression

    // notification: constexpr is only valid to pointer
    int i = 21;
    int j = 22;
    const int *p1 = &mf;
    int null = 0, *p2 = &null;
}

void prog10_typedef_auto()
{
    typedef double wages;
    typedef wages base, *pd;
    wages w1 = 21.99, w2 = 23.99;
    pd pdi1 = &w1;

    using NUM = int;    // 别名声明
    NUM n1 = 100;
    const pd cpd1 = &w2;    // top const
    // cpd1 = &w1;  // const poniter can not being changed

    // auto i=0, *pi = &i;
    // auto i2=0.0, pi = 3.14;
    // auto会忽略顶层const的属性
    int i = 24, &r = i;
    auto a = r; // a是int,不是&
    const int ci = 25, &cr = ci;
    auto b = ci;    // int
    auto c = cr;    // int
    auto d = &i;    // int*
    auto e = &ci;   //const int*
    // 把auto看做一种类型，加上const and reference
    const auto f = ci;  // const int
    auto &g = ci; 
    // g = 48;
    // auto &h = 42;
    const auto &j = 42;

    auto k = ci, &l = i;
    auto &m = ci, *p = &ci;
    // auto &n = i, *p2 = &ci;
    // exercise_2_34
    a = 44;
    b = 44;
    c = 44;
    // d = 44;
    // e = 44;
    // g = 44;
}

void prog11_decltype()
{
    const int ci = 24, &cr = ci;
    decltype(ci) x = 25;
    decltype(cr) y = x;
    // decltype(cr) z;

    // decltype with reference
    int i = 42, *p = &i, &r = i;
    decltype(r+1) a;
    decltype(*p) b = i; // error, b is reference
    decltype((i)) c = i;    // error, c is reference
    decltype(i) d;
}

void prog12_bookstore()
{
    Sales_data data1, data2;
    double price = 0;
    std::cin >> data1._bookNo >> data1._units_sold >> price;
    data1._revenue = data1._units_sold * price;
    std::cin >> data2._bookNo >> data2._units_sold >> price;
    data2._revenue = data2._units_sold * price;
    
    if(data1._bookNo == data2._bookNo)
    {
        unsigned totalCnt = data1._units_sold + data2._units_sold;
        double totalRevenue = data1._revenue + data2._revenue;
        std::cout << data1._bookNo << " " << totalCnt << " "
                  << totalRevenue << " ";
        if(totalCnt)
            std::cout << totalRevenue / totalCnt << std::endl;
        else
            std::cout << "no sale" << std::endl;
    }
    else
    {
        std::cerr << "Data must refer to same ISBN" << std::endl;
    }
}

int main()
{
    // prog1_type_convert();
    // pro2_literal();
    // prog3_variable();
    // prog4_scope();
    // prog5_reference();
    // prog6_pointer();
    // prog7_compoundType();
    // prog8_const();
    // prog9_constexpr();
    // prog10_typedef_auto();
    // prog11_decltype();
    prog12_bookstore();

    return 0;
}