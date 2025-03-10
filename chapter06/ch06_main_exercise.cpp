#include "Chapter6.hpp"

void exercise_6_1()
{
    // 实参是argument，主调函数调用函数时所传递的参数，用来初始化形参 
    // 形参是parameter，是定义函数时，参数列表中的局部变量，用来接收主调函数所传递的实参
}

//exercise_6_3 is prog_1_function

void exercise_6_4()
{
    // 交互程序
    cout << "Please input a number which you want to get factoial: ";
    int num;
    cin >> num;
    cout << num << "! = " << factorial(num) << endl;

    cout << "Please input a number which you want to get absolute: ";
    cin >> num;
    cout << "|" << num << "| = " << exercise_6_5_absolute(num) << endl; // now exercise_6_5 don't in the scope, must declaration
}

int exercise_6_5_absolute(int val)
{
    return abs(val);    // abs()在<cmath>标准库中
}

void exercise_6_6()
{
    // parameter和local object都是随着函数被调用而重新建立，分配内存然后进行初始化，随着函数返回而销毁，也称作自动对象
    // local static object是在一开始程序经过局部静态对象的定义时分配内存进行初始化，之后就一直常驻内存，即使函数调用结束也不会销毁
    // 而且内存中保留此次函数调用是此静态对象最终的值
    srand((unsigned) time(NULL));
    for (size_t i = 0; i < 5; i++)
    {
        count_calls(rand() % 20);
    }
}

// exercise_6_7 就是在函数中采用局部静态对象进行累加

void exercise_6_10()
{
    srand(static_cast<unsigned>(time(NULL)));
    int ival1 = rand() % 20;
    auto start_clock = clock();
    while((clock() - start_clock) / CLOCKS_PER_SEC < 1);
    int ival2 = rand() % 20;
    cout << "before swap: ival1 = " << ival1
         << " ival2 = " << ival2 << endl;
    Swap(&ival1, &ival2);
    cout << "after swap:  ival1 = " << ival1
         << " ival2 = " << ival2 << endl;
}

// exercise_6_11 == prog3
void exercise_6_12()
{
    srand(static_cast<unsigned>(time(NULL)));
    int ival1 = rand() % 20;
    auto start_clock = clock();
    while((clock() - start_clock) / CLOCKS_PER_SEC < 1);
    int ival2 = rand() % 20;
    cout << "pass by reference: " << endl
         << "before swap: ival1 = " << ival1
         << " ival2 = " << ival2 << endl;
    Swap(ival1, ival2);
    cout << "after swap:  ival1 = " << ival1
         << " ival2 = " << ival2 << endl;
    // 我认为使用引用参数比指针参数更好，因为可以省去很多麻烦，使用指针参数还要验证其有效性，防止使用空指针，解引用也比较麻烦
    // 引用就不需要担心这些问题，直接使用即可
}

void exercise_6_14()
{
    // 当需要在函数中改变所传递的实参时，应该pass by reference,当实参类型是自定义类型或者标准库类型时，也应该尽量使用pass by reference
    // 这样可以减少拷贝开销，我不认为存在不应该使用引用参数的情况，即使是不需要改变所传递的实参，也可以使用常量引用
}

// exercsie_6_15
// find_char()第三个参数必须是普通引用，这样才能改变所传递的实参；
// 由于不需要改变标准库类型string，但是采用引用参数可以避免拷贝开销，所以使用常量引用，既可以避免所传递的实参被修改，也可以避免拷贝开销 
// occurs必须是普通引用，才能被修改，常量引用无法修改变量的值
// 所传递的字符ch，是内置类型，没必要使用引用类型
// 若string s是普通引用，一方面迷惑代码的浏览者，二是开发者可能不经意间修改字符串的值
// occurs若是常量引用，则无法修改变量的值，一旦修改，会出现编译报错

void exercise_6_17()
{
    cout << "Please input a string whichever you want:" << endl;
    string str;
    getline(cin, str);
    if(checkUpper(str))
        convertLower(str);
    cout << "after change, str is" << endl
         << str << endl;
// 我使用的形参类型是不同的，因为checkUpper只需要读字符串，不需要改变，因此采用常量引用参数
// 但是convertLower需要将字符串中的大写字母改为小写，因此采用普通引用才能进行写操作
}

// exercise_6_20
// 当不需要对参数进行写操作时，应该采用常量引用形参形式
// 本应该是常量引用的形参设置为了普通引用，一是没法接受常量对象，包括字面值表达式，大大减弱了适用范围
// 二是可能导致不经意的写操作

void exercise_6_21()
{
    // 指针的类型应该是const int *
    srand(static_cast<unsigned>(time(NULL)));
    int ival1 = rand() % 100;
    auto start_clock = clock();
    while((clock() - start_clock) / CLOCKS_PER_SEC < 1);
    int ival2 = rand() % 100;
    cout << ival1 << " and " << ival2 << " the Bigger is "
         << Bigger(ival1, &ival2) << endl;
}

void exercise_6_22()
{
    srand(static_cast<unsigned>(time(NULL)));
    int ival1 = rand() % 100;
    int ival2 = rand() % 100;
    int *pi1 = &ival1, *pi2 = &ival2;
    cout << "*pi1 = " << *pi1
         << "   *pi2 = " << *pi2 << endl;
    SwapPointer(pi1, pi2);
    cout << "after swap " << endl
         << "*pi1 = " << *pi1
         << "   *pi2 = " << *pi2 << endl;
}

void exercise_6_23()
{
    int j[2] = {2, 3};
    print(begin(j), end(j));
    print(j, end(j) - begin(j));
}

void exercise_6_27()
{
    int sum = sumOfList({1, 1, 2, 3, 5, 8, 13});
    cout << "sum is " << sum << endl;
}

// exercise_6_29
// 应该声明为引用类型，这样一旦列表中的元素是标准库类型或者自定义类型，可以避免拷贝开销

// exercise_6_31
// 返回函数内部的局部对象时，返回的引用无效
// 返回绑定函数内部的局部对象的引用无效，同时返回函数内部的字面值表达式等局部临时对象也无效

void exercise_6_33()
{
    vector<int> ivec{1, 1, 2, 3, 5, 8, 13, 21};
    recursivePrint_shun(ivec.cbegin(), ivec.cend());
    recursivePrint_ni(ivec.cbegin(), ivec.cend());
}

void exercise_6_42()
{
    string str1 = "success", str2 = "failure";
    cout << "single format: " << endl 
         << make_plural(1, str1) << endl
         << make_plural(1, str2) << endl
         << endl << "plural format: " << endl
         << make_plural(2, str1, "es") << endl
         << make_plural(2, str2) << endl;
}

// exercise_6_45
// 内联函数是逻辑短小精悍且经常被调用的函数，通过设置为内联函数，可以在函数调用点展开，而不需要有调用函数开销，因此设置为内联函数
// exercise_6_46
void exercsie_6_46()
{
    bool ret = isShorter("nanjiang", "nan");
// 编辑后说明不能将isShorter定义成constexpr函数，因为在函数内部需要调用string标准库类的函数，这不是一个字面值常量能够做的事情
}

void exercise_6_47()
{
    vector<int> ivec{1, 1, 2, 3, 5, 8, 13, 21};
    recur_ndebug_print(ivec.cbegin(), ivec.cend());
}

// exercise_6_49
// 候选函数是同名函数的集合
// 可行函数是无论参数数量还是参数类型形参都与给定的实参相容的函数集合
void exercise_6_51()
{
    // f(2.56,42);
    f(42);
    f(42,0);
    f(2.56, 3.14);
}

void exercise_6_54()
{
    vector<int (*) (int, int)> pfvec;
    pfvec.push_back(exer54);
    // cout << pfvec[0](1, 1) << endl;

    pfvec.push_back(Add);
    pfvec.push_back(Minus);
    pfvec.push_back(Mutiply);
    pfvec.push_back(Divide);

    for (auto &&pf : pfvec)
    {
        cout << pf(6, 3) << endl;
    }
}

int main(int argc, char* argv[])
{
    // exercise_6_4();
    // exercise_6_6();
    // exercise_6_10();
    // exercise_6_12();
    // exercise_6_17();
    // exercise_6_21();
    // exercise_6_22();
    // exercise_6_23();
    // exercise_6_25

    // if(argc >= 3)
    // {
    //     cout << "program accept two argument, catch two argument to a string is: " << endl;
    //     string res;
    //     res += argv[1]; // remember argv[0] is executable file, not useful argument
    //     res += argv[2];
    //     cout << res << endl;
    // }
    // for(int i=1; i<argc; ++i)
    // {
    //     cout << argv[i] << endl;
    // }
    // cout << endl;

    // exercise_6_27();
    // exercise_6_33();
    exercise_6_42();
    // exercise_6_47();
    // exercise_6_51();
    // exercise_6_54();

    return 0;
}