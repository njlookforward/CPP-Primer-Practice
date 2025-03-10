#include <iostream>
#include <vector>
#include <string>

using namespace std;

void exercise_4_3()
{
    // C++没有规定二元运算符的求值顺序，给编译器的优化留下了余地，是在代码生成效率和程序潜在缺陷之间进行了权衡
    // 我认为了这是可以接受的，像普通计算操作一样使用这些二元操作符，只有在一个复合表达式中对同一对象进行操作，且其中
    // 一个或多个操作改变了对象的值，这种情况下需要谨慎处理，用括号显示表达求值顺序，其他情况下可以很自然的处理
}

void exercise_4_5()
{
    cout << -30 / 3 * 21 % 4 << endl;
}

void exercise_4_7()
{
    // 溢出是计算后的数值超越了该值所属类型所能表示的最大值或者最小值
    int i = 2147483647 + 1,
        j = -100000 * 300000,
        k = 2015 * 2015 * 2015 * 2015;
}

void exercise_4_10()
{
    int ival;
    while (cin >> ival && ival != 42)
    {
        continue;
    }
    cout << "input format is error or ival is 42." << endl;
}

void exercise_4_17()
{
    // 1 相同点：都是将操作对象的值加1
    // 2 不同点：前置递增运算符：将操作数加1，然后返回左值，后置递增运算符将操作数加1，但是返回原始数据的副本，是右值
    // 后置递增运算符比前置递增运算符的优先级更高
}

void exercise_4_21()
{
    vector<int> ivec;
    int num;
    while (cin >> num)
        ivec.push_back(num);
    cout << "before promote" << endl;
    for (auto &&i : ivec)
        cout << i << " ";
    cout << endl << "after promote" << endl;

    for (auto &num : ivec)
    {
        num = num % 2 != 0 ? num * 2
                           : num;
        cout << num << " ";
    }
    cout << endl;
}

void exercise_4_22()
{
    vector<unsigned> scores;
    unsigned grade;
    while (cin >> grade && grade >= 0 && grade <= 100)
        scores.push_back(grade);
    cout << "use condition operator distinction:" << endl;
    for (auto &&grade : scores)
        cout << grade << " : "
             << (grade < 60 ? "fail"
                            : grade <= 75 ? "low pass"
                                          : grade < 90 ? "pass"
                                                       : "high pass") << endl;

    cout << endl << "use if-else-if distinction:" << endl;
    for (auto &&grade : scores)
    {
        cout << grade << " : ";
        if(grade < 60)
            cout << "fail" << endl;
        else if(grade <= 75)
            cout << "low pass" << endl;
        else if(grade < 90)
            cout << "pass" << endl;
        else
            cout << "high pass" << endl;
    }
    // 这种情况下我认为使用条件运算符更容易理解，更清晰更简洁，当然这是在嵌套3个条件运算符的基础上，再多的话可读性就大大降低了
}

void exercise_4_23()
{
    string s("word");
    string pl = s + (s[s.size() - 1] == 's' ? "" : "s");
}

void exercise_4_24()
{
    // 这道题我认为没有意义
}

void exercise_4_25()
{
    char ch = 'q';  // ch是带符号字符
    cout << "before reverse and move: " << static_cast<int>(ch) << endl;
    auto res = ~ch << 6;
    cout << "after reverse and move:  " << res << endl;

}

void exercise_4_28()
{
    cout << "bool: " << sizeof(bool) << endl
         << "char: " << sizeof(char) << endl
         << "unsigned char: " << sizeof(unsigned char) << endl
         << "wchar_t: " << sizeof(wchar_t) << endl
         << "char16_t: " << sizeof(char16_t) << endl
         << "char32_t: " << sizeof(char32_t) << endl
         << "short: " << sizeof(short) << endl
         << "int: " << sizeof(int) << endl
         << "unsigned: " << sizeof(unsigned) << endl
         << "long: " << sizeof(long) << endl
         << "long long: " << sizeof(long long) << endl
         << "float: " << sizeof(float) << endl
         << "double: " << sizeof(double) << endl
         << "long double: " << sizeof(long double) << endl
         << "int*: " << sizeof(int *) << endl;
}

void exercise_4_29()
{
    int x[10];
    int *p = x;
    cout << sizeof(x)/sizeof(*x) << endl    // 10
         << sizeof(p)/sizeof(*p) << endl;   // 2    
}

void exercise_4_31()
{
    // 前置递增递减运算符更符合自增自减的原意，而且返回的是左值，计算开销比后置版本更小
    // 永远要记住operator,的操作数是两个, 组成了一个表达式
    vector<int> ivec(10);
    vector<int>::size_type cnt = ivec.size();
    for(vector<int>::size_type ix = 0; ix != ivec.size(); ix++, cnt--)
        ivec[ix] = cnt;
    for (auto &&i : ivec)
        cout << i << " ";
    cout << endl;
}

void exercise_4_33()
{
    int x = 10, y = 20;
    bool someValue = true;
    someValue ? ++x, ++y : --x, --y;
    cout << "someValue: " << someValue << endl  // 1
         << "x: " << x << endl                  // 11
         << "y: " << y << endl;                 // 20
    
    someValue = false;
    someValue ? ++x, ++y : --x, --y;
    cout << "someValue: " << someValue << endl  // 0
         << "x: " << x << endl                  // 10
         << "y: " << y << endl;                 // 19
}

int main()
{
    // exercise_4_5();
    // exercise_4_7();
    // exercise_4_10();
    // exercise_4_21();
    // exercise_4_22();
    // exercise_4_23();
    exercise_4_25();
    // exercise_4_28();
    // exercise_4_29();
    // exercise_4_31();
    // exercise_4_33();

    return 0;
}