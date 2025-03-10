#include <ctime>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <functional>
#include <map>
#include <iterator>
#include "Sales_data.hpp"
#include "strBlob.hpp"
#include "exercise.hpp"
#include "Date.hpp"
using namespace std;

// exercise_14_1
// 在什么情况下，重载的运算符与内置运算符有区别，我不太明白这道题的意思。但是我有自己的理解
// 当重载的运算符函数作为成员函数时，显示的参数数量要比运算对象的数量少一个，因为隐含将调用对象绑定到this指针
// 重载的运算符函数作为非成员函数时，参数数量与运算对象数量一致。
// 对于自定义类来说，如果某一个操作的逻辑与可以用运算符表示，那么应该重载运算符函数，重载的运算符函数只是运算对象的类型
// 即函数的形参是自定义类类型；而运算符的逻辑含义，运算对象数量，结合律，优先级，调用的表达式形式都与内置运算符一致。
/* answer: difference: 1) 重载运算符的操作数至少有一个是class or 枚举类型的数据
 * 2) 重载运算符不保证求值顺序，例如对于&& ||失去短路求值的特性，两个操作数都要求值，而且不规定操作数的求值顺序
 * 3) same: 操作数数量和优先级结合律都不改变
*/

// exercise_14_2 is Sales_data.hpp
// exercise_14_3
// 非成员函数的运算符重载函数的调用要求至少有一个运算对象是类类型
// (a) " " == " " 调用const char*类型的operator==, 调用的是C++语言内置版本的==，比较两个指针，是可以的
// (b) invoke bool operator==(const string &, const string &);
// (c) invoke bool operator==(const vector<string> &, const vector<string> &);
// (d) invoke bool operator==(const string &, const string &);
void exercise_14_3()
{
    auto s1 = "cobble", s2 = "stone";
    cout << (s1 == s2) << endl;
}

// exercise_14_4
// 一般来说，= [] () -> * ++ -- operator type() const 复合赋值都应该是成员函数，而算数、关系、逻辑运算符这种具有对称性运算特征
// 运算符应该定义为非成员函数
// member function:(b)%= (c)++ (d)-> (h)()
// non-member function:(a) %  (e)<<  (f)&& (g)==

// exercise_14_5
// 是否应该在一个类中编写重载运算符函数，还是要看这个类具有的逻辑操作有哪些，一旦操作功能与运算符大体一致，就应该重载运算符
// for (a) Book
// overload >> << == != + - += -=

// exercise_14_6 in the Sales_data.hpp
// exercise_14_7 in the String.hpp 按照我自己的答案来，书上的答案没有说服力
// exercise_14_8 没有必要练习这道题
// exercise_14_9 in the Sales_data.hpp

// exercise_14_10
// (a) format is correct; 
// (b) the order of cin is wrong; cin >> isbn right; cin >> units, right. but input 24
// cin >> price, right; price = 0.95; 尽管可以输入数据可以成功，但是格式都是错误的
void exercise_14_10()
{
    // Sales_data sd;
    // cin >> sd;
    // cout << sd << endl;
    unsigned i;
    double d;
    cin >> i >> d;
    cout << i << endl << d << endl;
}

// exercise_14_11
// 重载的输入运算符基本逻辑没有错误，但是没有进行输入失败的处理，程序的鲁棒性很弱，万一出现输入错误
// 则Sales_data中存储的就是有问题的数据，在接下来的程序中使用这个Sales_data对象很有可能出现问题
// (a)仍然成功;  (b)也可以输入成功，但是得到的数据是有问题的，因为输入的数据顺序是颠倒的

// exercise_14_12 仍然没有必要去重复练习
// exercise_14_13 
// Sales_data还需要operator-运算符，因为可能需要计算局部数量的书籍的数据

// exercise_14_14
// 用复合赋值运算符来实现算术运算符是更有效的，因为在程序设计的世界中尽量减少造轮子，尽量组合函数来实现新的功能
// 这样的好处是首先不容易出错，而且通过将一个大功能切分成多个小功能实现，方便调试定位错误；而且一旦需要做出改进
// 只需要变动其中的几个小功能函数就可以，大的函数不需要做出任何改动，方便维护
/* 从头实现operator+与通过operator+=来实现的方式相比，没有任何性能优势，而且代码可读性后者更好，因此代码复用更好
*/

// exercise_14_15 也不需要进行重复练习
// exercise_14_16 in the strVec.hpp strBlob.hpp String.hpp
// exercise_14_17 也不需要练习

// exercise_14_18 in the String.hpp strVec.hpp strBlob.hpp
// exercise_14_19 也不需要练习
// exercise_14_20 in the Sales_data.hpp

// exercise_14_21
// 对于算术运算符使用复合赋值运算符进行实现的设计，我认为更好。因为复合赋值运算符是成员函数，可以直接访问数据成员
// 而用算术运算符实现算数逻辑，需要声明为友元函数才能访问数据成员，这样破坏了封装性；而且用算数运算符实现复合赋值运算
// 不仅需要创建临时的和对象，而且需要调用拷贝赋值运算符或者移动赋值运算符进行替换，不如直接定义
/*本题的方式性能上没有优势，而且可读性也不好*/

// exercise_14_22 in the Sales_data.hpp
// exercise_14_23 in the strVec.hpp
// exercise_14_24_25 需要根据实际的逻辑编辑拷贝赋值运算符或者移动赋值运算符
void exercise_14_25()
{
    Date date;
    cout << date << endl;
    date = "2025-2-3";
    cout << date << endl;
}

// exercise_14_26 in the String.hpp strVec.hpp strBlob.hpp
// 内置指针就有operator[]，因此strBlobPtr是指针语义，当然可以定义operator[]

// exercise_14_27 in the strBlob.hpp
// exercise_14_28 in the strBlob.hpp

// exercise_14_29
// 不可能定义const版本的递增递减运算符的，因为递增递减运算符，无论是前置版本还是后置版本都需要改变数据成员
// 因此没有const版本

// exercise_14_30 in the strBlob.hpp
// exercise_14_31
// 因为定义的strBlobPtr使用默认的拷贝构造函数，拷贝赋值运算符、析构函数就足够了
// strBlobPtr的数据成员是weak_ptr and size_t,使用默认的拷贝控制操作就可以

void exercise_14_32()
{
    strBlob sb{"hi", "bye", "now"};
    strBlobPtr p(sb);
    *p = "okay";
    ptrStrBlobPtr ppsb(&p);
    cout << ppsb->size() << endl
         << p->size() << endl;
}

// exercise_14_33
// 一个重载的函数调用运算符根据形参数量决定有几个运算对象

void exercise_14_34()
{
    judgeObj judger;
    srand(static_cast<unsigned>(time(NULL)));
    int num = rand() % 100;
    cout << num << " " 
         << judger(num, "nanjiang", "NANJIANG") << endl;
}

void exercise_14_35_36(int argc, char **argv)
{
    ifstream ifs(argv[1]);
    if(!ifs)
    {
        cerr << "Sorry, cannot open " << argv[1] << endl;
        return;
    }

    InputLineString liner(ifs);
    vector<string> svec;
    string word;
    while (!(word = liner()).empty())
    {
        svec.push_back(word);
    }
    for (auto &w : svec)
    {
        cout << w << endl;
    }
}

void exercise_14_37(int argc, char **argv)
{
    ifstream ifs(argv[1]);
    if(!ifs)
    {
        cerr << "Sorry, cannot open " << argv[1] << endl;
        return;
    }

    vector<int> ivec;
    int num;
    while (ifs >> num)
    {
        ivec.push_back(num);
    }
    auto printer = [](int num) { cout << num << " "; };
    for_each(ivec.begin(), ivec.end(), printer);
    cout << endl;
    replace_if(ivec.begin(), ivec.end(), EqualVal(95), 1);
    for_each(ivec.begin(), ivec.end(), printer);
}

void exercise_14_38_39(int argc, char **argv)
{
    ifstream ifs;
    openfile(ifs, argv[1]);

    vector<string> svec;
    string word;
    while (ifs >> word)
    {
        svec.push_back(cleanup_str(word));
    }
    CheckLength gauge;
    for(std::size_t thresh = 1; thresh <= 10; ++thresh)
    {
        gauge.changeThresh(thresh);
        std::size_t cnt = count_if(svec.begin(), svec.end(), gauge);
        // auto iter = svec.begin();
        // while ((iter = find_if(iter, svec.end(), gauge)) != svec.end())
        // {
        //     ++cnt;
        //     ++iter;
        // }
        if(thresh < 10)
            cout << "In the string vector, the number of words whose length are equal to "
                 << thresh << " have " << cnt << " words." << endl;
        else
            cout << "In the string vector, the number of words whose length over 10"
                 << " have " << cnt << " words." << endl;
    }

    strLenBetween bounder(1, 9);
    strNotShorterThan lower(10);

    cout << "1~9 length words have " << count_if(svec.begin(), svec.end(), bounder) << endl
         << "over 10 length words have " << count_if(svec.begin(), svec.end(), lower) << endl;

    ifs.close();
}

// exercise_14_40 in the chapter10\\exercise.cpp
// exercise_14_41
// 我认为C++11引入lambda能够提高编程效率，lambda表达式就是一种匿名函数，通过将函数对象书写成lambda形式
// 能够更直观更精确；
// 我认为当需要小函数的时候，像在标准库算法中添加一元或者二元谓词的时候，可以使用lambda；
// 当函数逻辑相对较大的时候，我认为设计成函数对象会更好
/* lambda表达式是一种匿名的函数对象，lambda表达式是对函数对象的一种简单实用
 * 当代码需要一个简单的函数时，而且不会在其他地方再使用这个函数，这时使用lambda表达式更好
 * 当函数较大时，而且需要保存某些数据状态，而且需要多次使用时，使用函数对象更好
 */

void exercise_14_42()
{
    vector<int> ivec = {1, 1, 2, 3, 5, 8, 13};
    // 其实，函数对象也是函数，如何将函数对象放在标准库算法中就怎么放在bind中
    using placeholders::_1;
    count_if(ivec.begin(), ivec.end(), bind(greater<int>(), _1, 1024));

    auto NotEqualToPooh = bind(not_equal_to<string>(), _1, "Pooh");
    vector<string> svec = {"Nan", "jiang", "Pooh"};
    find_if(svec.begin(), svec.end(), NotEqualToPooh);
    auto Twice = bind(multiplies<int>(), _1, 2);
    vector<int> destvec;
    transform(ivec.begin(), ivec.end(), back_inserter(destvec), Twice);

    for (auto &n : ivec)
    {
        n = Twice(n);
        cout << n << " ";
    }
    cout << endl;
}

void exercise_14_43()
{
    cout << "Please input a number to check which factors: ";
    vector<int> factories = {2, 3};
    int num;
    while (cin >> num)
    {
        if(Factor(num, factories))
            cout << num << "\'s factory has 2 and 3." << endl;
        else
            cout << num << "\'s factory don't have 2 and 3." << endl;    
    }
}

void exercise_14_44()
{
    auto mod = [](int i, int j) {   return i % j;   };
    // int (*pf)(int, int) = add;
    auto lamAdd = [] (int i, int j) {   return add(i, j);   };
    function<int (int, int)> f1_add = lamAdd;
    function<int (int, int)> f2_mod(mod);
    function<int (int, int)> f3_divide = divide();
    function<int (int, int)> f4_multiply = [] (int i, int j) {  return i * j;   };
    function<int (int, int)> f5_minus = minus<int>();

    cout << f1_add(4, 2) << endl
         << f2_mod(4, 2) << endl
         << f3_divide(4, 2) << endl
         << f4_multiply(4,2) << endl;
    
    map<string, function<int (int, int)>> binops = {
            {"+", f1_add},
            {"-", f5_minus},
            {"*", f4_multiply},
            {"/", f3_divide},
            {"%", f2_mod}
    };

    cout << binops["+"](10, 5) << endl
         << binops["-"](10, 5) << endl
         << binops["*"](10, 5) << endl
         << binops["/"](10, 5) << endl
         << binops["%"](10, 5) << endl;

    int left, right;
    string ops;
    while(cin >> left >> ops >> right)
        cout << binops[ops](left, right) << endl;
}

// exercise_14_45 in the Sales_data.hpp
// 定义的Sales_data的类型转换运算符不管返回值是什么，没有任何意义
// exercise_14_46
// 我认为没有必要定义向string和double的类型转换运算符，两者之间没有代表性
/* 如果一定要定义这两个类型转换运算符的话，应该定义成explicit的，为了防止Sales_data对象在某些情况下
 * 被默认的转换成string或者double，可能导致意料之外的运算结果。
 */

// exercise_14_47
struct Integral
{
    operator const int();   // non-const mf; convert to const int from Integral
    operator int() const;   // const mf; convert to int from Integral
    // 前置在接受const int的地方才能够被使用；后者相对来说更通用一些
};

// exercise_14_48_49
// 不管是什么类类型，最好应该定义explicit的向bool类型转换运算符，可以用在条件表达式中
// 类似于while for ?: if中作为条件
/*我们需要将bool类型转换运算符定义成explicit，有意将其用在条件表达式中*/
void exercise_14_48_49()
{
    Date d;
    cin >> d;
    if(d)
        cout << d << endl;
    else
        cout << "Invalid date" << endl;
}

void exercise_14_50()
{
    LongDouble ld;

    // int ex1 = ld;   // ambiguous
    float ex2 = ld; // explicit
}

void calc(int) {}
void calc(LongDouble) {}

void exercise_14_51()
{
    double d = 1.2;
    calc(d);
    // 通过实验说明使用的是calc(int)，不需要调用函数，直接进行类型转换即可
    /* 会优先调用calc(int)，因为从double转换为int是标准类型转换
     * 而从double到LongDouble是转换到自定义类型，需要调用转换构造函数，因此前者优先级更高
     */
}

void exercise_14_52()
{
    LongDouble ld;
    smallInt si(1);
    // LongDouble sum1 = si + ld;
    // ambiguous: operator+(int, double) or operator+(int, float)
    LongDouble sum2 = ld + si;
}

void exercise_14_53()
{
    smallInt si = 1;
    double d = si.operator int() + 3.14;   // ambiguous
    // 显示的调用类型转换运算符即可
}

int main(int argc, char **argv)
{
    // exercise_14_3();
    // exercise_14_10();
    // exercise_14_25();
    // exercise_14_32();
    // exercise_14_34();
    // exercise_14_35_36(argc, argv);
    // exercise_14_37(argc, argv);
    // exercise_14_38_39(argc, argv);
    // exercise_14_42();
    // exercise_14_43();
    // exercise_14_44();
    exercise_14_48_49();
    // exercise_14_50();
    // exercise_14_51();
    // exercise_14_52();
    // exercise_14_53();

    return 0;
}