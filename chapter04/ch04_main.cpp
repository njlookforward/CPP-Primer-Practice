#include <iostream>
#include <vector>
#include <string>
#include "Sales_data.hpp"

using namespace std;

void prog1_operation_order()
{
    int i = 0;
    cout << i << " " << ++i << endl;    // 0 1
}

void prog2_arithmetic()
{
    int i = 1024;
    int k = -i;
    bool b = true;
    bool b2 = -b;   // true;
    // cout << sizeof(short) << endl;   // short has 2 Byte
    short short_value = 32767;  
    short_value += 1;   // 会发生溢出，变成负值
    cout << "after overflow short_value: " << short_value << endl;

    int ival1 = 21/6;   // 3
    int ival2 = 21/7;   // 3
    int ival = 42;
    double dval = 3.14;
    cout << ival % 12 << endl;  // 6
    // ival % dval;    // 取余/取模运算符的两个操作数必须是整数，否则会出现问题
    cout << 21 % 6 << endl      // 3
         << 21 % 7 << endl      // 0
         << -21 % -8 << endl    // -5
         << 21 % -5 << endl     // 1
         << 21 / 6 << endl  // 3
         << 21 / 7 << endl  // 3
         << -21 / -8 << endl    // 2
         << 21 / -5 << endl;    // -4
}

void prog3_conditional()
{
    int ival = 2;
    if(ival == true)
        cout << "bukeneng" << endl;
    else
        cout << "true promote into 1" << endl;
}

void prog4_assignment()
{
    int k = 0;
    // k = {3.14}; // C++11允许使用初始化列表作为赋值语句的右值
    vector<int> ivec;
    ivec = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    // assignment operator is right associativity
    int ival, *pi;
    // ival = pi = 0;  // error, int * can't assign int
    string str1, str2;
    str1 = str2 = "is string";  // meiwenti
}

void prog5_increment()
{
    int i = 0, j;
    j = ++i;
    j = i++;

    vector<int> ivec;
    int num;
    while (cin >> num)
    {
        ivec.push_back(num);
    }
    auto bit = ivec.cbegin();
    while (bit != ivec.cend())
    {   
        if(*bit >= 0)
            cout << *bit++ << " ";
        else
            ++bit;
    }
    cout << endl;
    cout << (ivec[i++] <= ivec[i]) << endl;

    vector<string> svec{"hello", "C++", "world"};
    auto sbit = svec.begin();
    cout << sbit++->size() << endl;
}

void prog6_condition()
{
    vector<unsigned> scores;
    int grade;
    while (cin >> grade)
        scores.push_back(grade);
    for(auto gradeit = scores.begin(); gradeit != scores.end(); ++gradeit)
        cout << *gradeit << " : " << (*gradeit < 60 ? "fail"
                                                    : *gradeit > 90 ? "high pass"   // ?:is right associativity
                                                                    : "pass") << endl;
        // 最多进行2-3次嵌套，否则无论可读性还是准确性都大打折扣
        // << 的优先级在+- 和 < 之间，而？：在<之后
}

void prog7_bit_operator()
{
    // 位运算的操作对象一般是无符号整数，这样移位操作的时候就可以不用管符号位
    unsigned char bits = 0233;
    ~bits;
    int movebits = bits << 8;
    movebits = bits << 31;
    bits >>= 3;

    bits = 0227;
    bits = ~bits;   // 自己大脑傻啦！！！位操作返回的是右值，不改变操作数本身

    unsigned b1 = 0145;
    unsigned b2 = 0257;
    unsigned andres = b1 & b2,
             yihuores = b1 ^ b2,
             orres = b1 | b2;
    b1 ^= b2;
    
    // 每一个整数有32位，因此采用位运算可以保留很多信息
    unsigned long quizl = 0;
    // 若是第27位学生通过了测试，则27位置为1
    quizl |= 1UL << 27;
    // 若是复查时发现第27位学生没有通过测试
    quizl &= ~(1UL << 27);
    // 如何检查第27位学生是否通过测试
    bool states = quizl & 1UL << 27;

    // follow expression specify <</>> precedence is between +- and <>
    cout << (42 < 10) << endl;
}

void prog8_sizeof()
{
    Sales_data data, *p;    
    auto sz = sizeof(Sales_data);   // sizeof(type) one usage
    sz = sizeof data;   // sizeof expression the second usage
    sz = sizeof p;
    sz = sizeof *p; // sizeof and * have same precedence
    sz = sizeof data._revenue;
    sz = sizeof Sales_data::_revenue;

    // sizeof can be used in calculate array's size
    int iarr[] = {0, 1, 2, 3, 4, 5, 6, 7};
    constexpr size_t iarr_size = sizeof(iarr) / sizeof(*iarr);  // sizeof(iarr) can directly calculate iarray's size, no pointer
    // int iarrCopy[iarr_size];
}

void prog9_explict_cast()
{
    int i = 3, j =5;
    double dval = static_cast<double>(i) / j;
    void *p = &dval;
    double *pd = static_cast<double *>(p);  // 只有type为引用类型时类型转换后得到的是左值，否则一般是右值
    cout << *pd << endl;

    // static_cast能进行有明确定义的类型转换，const_cast只能改变对象的底层const
    const char *cont = "Hello World";
    char *pc = const_cast<char *>(cont);
    // pc[0] = 'h'; // 向字符串常量中写数据发生错误，并抛出异常，发生未定义的行为
    cout << "char *pc = " << pc << endl;

    string str = static_cast<string>(cont);
    cout << "string str = " << str << endl;
    // str = const_cast<string>(cont); // error, const_cast只能修改对象的底层const属性

    // reinterpret_cast<>主要用于指针类型的转换，尽量不要使用，非常危险
    int *ip = &i;
    char *pchar = reinterpret_cast<char *>(ip);
    string str2(pchar); // 未定义的行为

    // 旧式的强制类型转换
    char *pc2 = (char *)ip;

    const string str3("nanjiang");
    const string *pcs = &str3;
    void *pv = reinterpret_cast<void*>(const_cast<string*>(pcs));
}

int main()
{
    // prog1_operation_order();
    // prog2_arithmetic();
    // prog3_conditional();
    // prog4_assignment();
    // prog5_increment();
    // prog6_condition();
    // prog7_bit_operator();
    // prog8_sizeof();
    prog9_explict_cast();

    return 0;
}