#include <vector>
#include <list>
#include <string>
#include <array>
#include "exercise.hpp"
#include "Vec.hpp"
// #include "Vec_copy_Iterator.hpp"
#include "Blob_Shared_ptr.hpp"
#include "Unique_ptr.hpp"
#include "Screen.hpp"
using namespace std;

// exercise_16_1
// 实例化定义：当在代码中使用函数模板或者类模板，编译器在编译阶段会根据传入的模板参数实例化对应的模版参数的
// 函数或类的定义，这就是模板实例化的过程
// answer: 在调用函数模板时，编译器会根据传入的函数实参推断出模板实参，然后用模板实参代替模板参数创建出模板的一个新的
// 实例，也就是一个真正的可以被调用的函数，这个过程称为实例化

// exercise_16_2 compare fcn in the exercise.hpp
// exercise_16_3
// 对Sales_data调用compare函数，刚开始时能够编译通过。原因是执行到less<T>()的时候Sales_data转换成了double类型
// 进行operator<，因此能够通过，但是我将Sales_data的类型转换运算符设置为显示类型转换运算符后，执行到Binary_compare时会出现问题
// 因为Sales_data没有定义operator<

void exercise_16_4(int argc, char **argv)
{
    checkArgs(argc, 2);
    ifstream infile;
    OpenInputFile(infile, argv[1]);
    // ifstream infile("..\\..\\..\\data\\absInt");

    vector<int> ivec;
    ReadIntoContainer(infile, ivec);

    cout << "Please input a value to find: ";
    int val;
    cin >> val;
    auto resIter = Find(ivec.cbegin(), ivec.cend(), val);
    // 做程序一定要严谨，而不是偷懒
    if(resIter != ivec.cend())
        cout << "result is " << *resIter << endl;
    else
        cout << "Sorry, " << val << " don't in the vector" << endl;

    auto resIter2 = Find_if(ivec.cbegin(), ivec.cend(),
            [](int val) { return val == 25; });
    if(resIter2 != ivec.cend())
        cout << "result2 is " << *resIter2 << endl;
    else
        cout << "Sorry, don't find requested value in the vector" << endl;

    infile.close();
}

void exercise_16_4_str(int argc, char **argv)
{
    checkArgs(argc, 2);
    ifstream infile;
    OpenInputFile(infile, argv[1]);
    // ifstream infile("..\\..\\..\\data\\absInt");

    list<string> slst;
    ReadIntoContainer(infile, slst);

    cout << "Please input a value to find: ";
    string val;
    cin >> val;
    auto resIter = Find(slst.cbegin(), slst.cend(), val);
    // 做程序一定要严谨，而不是偷懒
    if(resIter != slst.cend())
        cout << "result is " << *resIter << endl;
    else
        cout << "Sorry, " << val << " don't in the string list" << endl;

    auto resIter2 = Find_if(slst.cbegin(), slst.cend(),
            [](const string &val) { return val.size() > 5; });
    if(resIter2 != slst.cend())
        cout << "result2 is " << *resIter2 << endl;
    else
        cout << "Sorry, don't find requested value in the string list" << endl;

    infile.close();
}

void exercise_16_5_6_7(int argc, char **argv)
{
    checkArgs(argc, 2);
    ifstream infile;
    OpenInputFile(infile, argv[1]);

    // 直接使用普通数组的形式，但是要部分特例化函数模板ReadIntoContainer，要能够用于数组
    int iarr[8] = {};
    ReadIntoContainer(infile, iarr);
    print(iarr);
    for(auto pi = Begin(iarr); pi != End(iarr); ++pi)
        cout << *pi << " ";
    cout << endl
         << Size(iarr) << endl;

    // string sarr[8];
    // ReadIntoContainer(infile, sarr);
    // print(sarr);
    // Bug5:因为定义iarr[ivec.size()]，定义数组大小应该用常量表达式，这样在编译期就能知道数组的大小
    // 但是我采用的是ivec.size()，这是到运行期才能知道数组的大小，然而函数模板是在编译期进行实例化
    // 因此编译器在编译期阶段无法自行推断传入的数组参数的大小，因此就无法实例化，因此报错

    // for(auto pa = Begin(sarr); pa != End(sarr); ++pa)
    //     cout << *pa << " ";
    // cout << endl;

    infile.close();
}

// exercise_16_8
// C++程序员喜欢使用!=而不是<，是因为使用!=对函数模板或者类模板中参数要求更低一些，大部分自定义类型或者标准库类型
// 都会重载自己的operator!=/==运算符，但可能不会重载operator<运算符，比如容器的迭代器类型iterator只重载了!=/==
// 没有重载<。因此更喜欢使用!=
// answer: 理解泛型编程的一个重点：算法对类型的要求决定了算法的适用范围
// 泛型编程的一个目标是：算法是“通用的”，能够使用于不同的类型。标准库容器类型都定义了==/!=运算符，只有很少的容器定义了<运算符，因此尽量
// 使用==/!=而不是<可以减少所设计的泛型算法适用容器的限制

// exercise_16_9
// 一个函数模板就是一个公式，用来生成特定类型的函数；一个类模板也是一族类的蓝图，用来生成特定的类类型。
// 不管函数模板还是类模板，其定义都要从关键字template开始，然后是模板参数列表，列表不能为空。使用函数模板时
// 若编译器可以从传入的实参推断出模板参数类型，那么不需要指定模板参数；但是使用类模板定义对象，需要指定模板参数
// answer: 简单来说，函数模板就是可以实例化出特定函数的模板，类模板就是可以实例化出特定类的模板。从形式上来说，
// 只是要以关键字template开头，后接模板参数列表；在使用上，函数模板与普通函数类似，使用时编译器会根据调用从函数实参中推断出
// 模板实参的参数类型进行实例化，类模板类似于普通类，但是必须显示指出模板实参来实例化类模板。

// exercise_16_10
// 当一个类模板被实例化时，这是在编译期发生的事情，编译器会生成对应模板实参的类定义
// answer: 当使用一个类模板时，我们必须显式提供模板实参列表，编译器将它们绑定到模板参数，来替换类模板定义中模板参数出现的地方
// 这样就实例化出一个特定的类。随后我们使用的就是这个特定的类。

// exercise_16_11 in the book
// answer: 我们应该牢记，类模板的名字不是一个类型名，只有实例化之后才能形成类型，而实例化是必须要提供模板实参的
// 这个规则有一个例外，就是类模板作用域内，可以不提供模板实参，直接使用模板名。

// exercise_16_12 in the Blob.hpp and BlobPtr.hpp
// exercise_16_13
// 我为BlobPtr的相等与关系运算符选择一对一实例化的友好关系
// answer：对于相等和关系运算符，对每个BlobPtr实例与用相同类型实例化的运算符建立一对一的友好关系

void exercise_16_14_15()
{
    Screen<5, 3> myScreen;
    // cout << myScreen << endl;
    myScreen.move(4, 0).set('#');

    Screen<5, 5> nextScreen('X');
    cout << nextScreen.move(4, 0).set('#') << endl;

    cout << myScreen.set('#') << endl;

    cout << myScreen.clear('Z') << endl;
    cout << myScreen.move(4, 0).set('#') << endl;
    cout << myScreen.clear('Z') << endl;

    cin >> myScreen;
    cout << myScreen << endl;
}

void exercise_16_16_int(int argc, char **argv)
{
    checkArgs(argc, 2);
    ifstream infile;
    OpenInputFile(infile, argv[1]);

    Vec<int> ivec;
    ReadIntoContainer(infile, ivec);
    Vec<int> ivec2{1, 1, 2, 3, 5, 8, 13, 21};
    cout << "ivec1: ";
    display(cout, ivec);
    cout << "ivec2: ";
    display(cout, ivec2);

    Vec<int> ivec3(ivec2);
    Vec<int> ivec4({1, 2, 3, 4});
    cout << "ivec3: ";
    display(cout, ivec3);
    cout << "ivec4: ";
    display(cout, ivec4);

    ivec4 = ivec;
    cout << "after ivec4 = ivec1: ";
    display(cout, ivec4);

    ivec3 = {1, 4, 9, 16};
    cout << "after ivec3 move operator=: ";
    display(cout, ivec3);

    ivec3.push_back(25);
    ivec3.push_back(36);
    cout << "after push_back: ";
    display(cout, ivec3);

    ivec3.pop_back();
    display(cout, ivec3);

    infile.close();
}

void exercise_16_16_string(int argc, char **argv)
{
    checkArgs(argc, 2);
    ifstream infile;
    OpenInputFile(infile, argv[1]);

    Vec<string> svec1;
    ReadIntoContainer(infile, svec1);
    cout << "svec1: ";
    display(cout, svec1);
    Vec<string> svec2{"a", "an", "the"};
    cout << "svec2: ";
    display(cout, svec2);

    Vec<string> svec3(svec2);
    cout << "svec3: ";
    display(cout, svec3);
    Vec<string> svec4({"nanjiang", "tianjin"});
    cout << "svec4: ";
    display(cout, svec4);

    svec4 = svec1;
    cout << "after 4=1&: ";
    display(cout, svec4);
    svec3 = {"hello", "world"};
    cout << "after 3 = &&: ";
    display(cout, svec3);

    svec2.push_back("now");
    svec2.push_back("how");
    svec2.emplace_back(10, 'c');
    svec2.emplace_back(string("nan") + "jiang");
    cout << "after 2push: ";
    display(cout, svec2);
    svec2.pop_back();
    display(cout, svec2);

    infile.close();
}

// exercise_16_17
// 声明为typename的模板类型参数与声明为class的模板类型参数是一样的，两者没有任何求别
// 当在定义类模板时，需要使用模板类的类型成员时，需要在前面使用typename显式地告诉编译器我们此时需要的是
// 模板类的类型成员而不是静态数据成员
// typename还有其他用途，当对模板类型参数使用作用域限定符::来访问其成员时，如T::value_type，在实例化之前
// 可能无法辨认访问的是静态数据成员还是类型成员，需要在名字前面加上typename,如typename T::value_type()
// 表明value_type是一个类型成员，这里创建了一个value_type类型的对象，并进行了值初始化

// exercise_16_18
// (a) template<typename T, typename U, typename V> void f1(T, U, V); // 必须指出U是模板类型参数还是非类型参数
// (b) template<typename T = int> T f2(T &);    // 模板参数名不能重用，这里重用T作为函数参数名
// (c) template<typename T> inline T foo(T, unsigned int*); // inline必须在typename的后面
// (d) template <typename T> T f4(T, T);    // 没有指定函数模板的返回类型
// (e) right, 模板参数类型Ctype覆盖了类型别名char

void exercise_16_19_20(int argc, char **argv)
{
    checkArgs(argc, 2);
    ifstream infile;
    OpenInputFile(infile, argv[1]);
    shared_ptr<ifstream> pfile(&infile, [] (ifstream *pf) { pf->close(); });

    // Vec<int> ivec;
    // ReadIntoContainer(infile, ivec);
    // display_v2(ivec);
    // display_v3(ivec);

    // Vec<string> svec;
    vector<string> svec;
    ReadIntoContainer(infile, svec);
    display_v2(svec);
    display_v3(svec);
}

// exercise_16_21 in the exercise.hpp
// exercise_16_22_23 in the TextQuery.hpp and TextQuery.cpp
// 当输入q离开单词查询时，TextQuery对象执行析构函数时，会调用DebugDelete的函数调用运算符

// exercise_16_24 in the Blob.hpp

// exercise_16_25
// extern template class vector<string>;    // 实例化声明
// template class vector<Sales_data>;       // 实例化定义
// extern说明不在本文件中进行实例化，而是在其他文件中实例化vector<string>
// 说明在本文件中实例化vector<Sales_data>，在其他文件中声明即可，使用本定义

// exercise_16_26
// NoDefault是一个没有默认构造函数的类，如果用于显示实例化vector<NoDefault>是不可以的
// answer: 显示实例化会实例化类模板的所有成员函数，包括它接受容器大小参数的构造函数。
// vector的这个构造函数会调用它的元素类型的默认构造函数对元素进行值初始化，而NoDefault没有默认构造函数
// 从而导致编译错误

// exercise_16_27
// 这道题我想错了，要修改自己认为类模板进行实例化的时间，当需要使用类模板时，类模板就已经用相应的模板参数进行实例化了
// 只有类模板中的成员函数，什么时候被用到，什么时候才会被实例化，但是类模板的数据成员是一定被实例化了的
// 一句话，类模板的实例化是在编译器完成的
// 因此(a) (b) (c) (f)已经用char double int string对Stack进行实例化了
// (d) (e)没有进行实例化，因此这些statement之前就已经完成了相应的实例化过程

void exercise_16_28_29_30(int argc, char **argv)
{
    checkArgs(argc, 3);
    ifstream infile1, infile2;
    OpenInputFile(infile1, argv[1]);
    OpenInputFile(infile2, argv[2]);
    Shared_ptr<ifstream> pfile(&infile1, [](ifstream *pf) { pf->close();  });

    Blob<int> ivec;
    Blob<int> ivec2{1, 1, 2, 3, 5, 8, 13, 21};
    int i;
    while(infile1 >> i)
        ivec.push_back(i);
    
    for(size_t i = 0; i < ivec.size(); ++i)
        cout << ivec[i] << " ";
    cout << endl;

    pfile.reset(&infile2, [](ifstream *pf) { pf->close();   });
    Blob<string> svec;
    string word;
    while(infile2 >> word)
        svec.push_back(word);
    
    for(size_t i = 0; i < svec.size(); ++i)
        cout << svec[i] << " ";
    cout << endl;

    Unique_ptr<string, DebugDelete> upstr(new string("nanjiang"), DebugDelete(cout));
    Unique_ptr<double> upd(new double(3.14));
    cout << *upd << endl;

    // Unique_ptr<string, DebugDelete> upstr2 = upstr;
}

// exercise_16_31 这道题真没理解是什么意思
// 将DebugDelete与自己定义的Unique_ptr结合使用，因为DebugDelete中的函数调用运算符operator()是模板函数
// Unique_ptr是类模板，因此在编译期，编译器根据传入的模板实参实例化类模板与函数模板，而这类模板中的成员函数和函数模板
// 都是内联函数，因此都是会被编译器处理为内联形式
// answer: 理解shared_ptr与unique_ptr使用删除器的方式。shared_ptr是在运行时绑定删除器，unique_ptr是在编译时绑定删除器
// unique_ptr有两个模板参数，一个是所管理的对象的类型，一个是删除器的类型。因此删除器类型是unique_ptr类型的一部分，在编译时
// 就可以知道，删除器可以直接保存在Unique_ptr对象中。通过这种方式，unique_ptr避免了间接调用删除器的运行时开销。而编译时还可以
// 将自定义的删除器，如DebugDelete编译为内联形式。我认为这个内联形式是指函数对象的调用运算符或者函数指针或者lambda表达式的函数调用运算符
// 编译为内联形式

// exercise_16_32_33
// 编译器只有对于函数模板能够进行模板实参推断，根据传入函数的实参的类型推断出模板参数类型，其中，允许对函数参数进行的
// 类型转换有两种，一种是非const类型向const类型的转换，一种如果函数形参不是引用类型，那么函数实参可以进行由数组或函数
// 向指针类型的转换
// answer: 在模板实参推断过程中，如果函数形参是模板类型参数，那么只能进行两种类型转换
// 一是，能进行从非const对象的引用或指针类型，到const对象的引用或指针类型的转换
// 二是，如果函数形参不是引用类型，那么能够进行从数组到指向数组首元素的指针的转换，或者从函数到函数类型的指针的转换

void exercise_16_34()
{
    // 这个调用是非法的，因为模板函数的形参是引用类型，而传入的函数形参，第一个是const char[3]
    // 第二个是const char[6]；因此无法进行统一的模板实参推断
    // compare("hi", "world");

    // 第二个调用是合法的，模板实参推断得出T = char[4]
    // compare("bye", "dad");
}

// exercise_16_35
// (a) T = char     (b) T = double
// (c) T = char     (d) 不合法，因为模板实参推断失败，第一个double，第二是float，无法得到一个统一的类型推断

// exercise_16_36
// (a) T = int*     (b) T1 = int*, T2 = int*    (c) T = const int*
// (d) T1 = const int*, T2 = const int*     (e) 非法调用，无法从int*和const int*中推断出参数类型
// (f) T1 = int*, T2 = const int*
void exercise_16_36()
{
    int i = 24, *pi = &i;
    int j = 42;
    const int *pci = &j;
    // auto ret = f1(pi, pci);
    // 通过实验，证明对于int*和const int*，不能进行模板实参推断，模板实参推断不能进行类型转换，即使是从non-const
    // 向const类型的转换也不行
}

// exercise_16_37
// 通过显示指定模板实参来调用max对象，比如std::max<int>(i, d) or std::max<double>(i, d)

// exercise_16_38
// Bug: 只能通过initializer_list来构造vector，不能直接使用列表，只有在定义vector<int>时才能够使用列表初始化
// initializer_list<int> il = {1,2,3};
// auto sp = make_shared<vector<int>>(il);
// 我们在调用make_shared模板函数时，必须显式指出要创建的shared_ptr智能指针要指向的对象的类型，然后在函数参数列表中
// 传入构造目标对象的参数，make_shared会根据这些类型调用目标对象的重载构造函数中最佳匹配的那一个构造函数

void exercise_16_39()
{
    cout << compare<string>("hello", "world");
}

// exercise_16_40
// 这个函数的本意是想通过算法表达式得到一个普通的元素类型，而不是元素的引用，因此函数是合法的
// 但是，传入函数的迭代器所指向元素类型应该是定义了operator+运算符的类型，而不能是其他类型，该函数有比较大的局限性
// 仍然应该使用std::remove_reference<>::type

void exercise_16_41()
{
    long lng = 123;
    double d = 3421.4312;
    cout << sum(lng, d) << endl;
}

// exercise_16_42
// (a) T = int&, val = int&
// (b) T = const int&, val = const int&
// (c) T = int, val = int&&

// exercise_16_43
// T = int&

// exercise_16_44
// 当模板函数中的参数声明为g(T)时
// (a) T = int, val = int;  (b) T = int, val = int;  (c) T = int, val = int;
// 当模板函数中的参数声明为g(const T&)时
// (a) T = int, val = const int&;  (b) T = int, val = const int&;  (c) T = int, val = const int&

// exercise_16_45
// g(42): T = int, vector<int>;
// g(i): T = int&, vector<int&>
// 注意，vector是如何管理他的元素的，vector维护一个动态内存空间，在其中保存它的元素。这就需要维护指向动态内存
// 空间的指针，这个指针的类型一定是保存的元素的类型。而引用不是对象，它没有实际地址，因此不能定义指向引用的指针
// 因此不能定义int &的vector，编译会失败

// exercise_16_46
// 在自定义strVec中，reallocate函数是将原来的空间扩大两倍，这个两倍大的空间是从新申请的，通过使用std::move()
// 调用string的移动构造函数，将旧空间中的string对象的资源转移到新的空间，因此不需要复制重新申请资源，而是通过移动语义
// 转移资源
// 调用string的移动构造函数，将数据从旧内存空间移动而不是复制到新的内存空间中，避免了不必要的数据拷贝操作

// exercise_16_47 in the exercise.hpp

// exercise_16_48 in the exercise.hpp

// exercise_16_49_50 不需要进行代码练习，很清晰
// g(42) g(T);     g(p) g(T*);     g(ci) g(T);     g(p2) g(T*);
// f(42) f(T);     f(p) f(T);     f(ci) f(T);     f(p2) f(const T*)

// exercise_16_51_52 in the exercise.hpp and ch16_main.cpp
// exercise_16_53 in the exercise.hpp and ch16_main.cpp

// exercise_16_54
// 如果我们对一个没有operator<<运算符的对象调用print，会报错，没有办法调用其operator<<

// exercise_16_55 需要重点查看，这道题目前记住就好
// answer: 非可变参数版本定义在可变参数版本之后，也属于“定义可变参数版本时，非可变参数版本声明不在作用域中”
// 调用可变参数版本时会陷入无限递归
// 这里的无限递归，不是运行时的无限递归调用，而是编译时无限递归的包扩展，例如对于print(cout, i, s, 42);接下来的调用应该是
// print(cout, i, s) -> print(cout, i);最后一次调用应该是调用非可变参数版本，但是事实上会继续使用可变参数版本
// 调用print(cout)，这样就无法匹配任何模板函数了，编译失败

// exercise_16_56 in the exercise.hpp and ch16_main.cpp

// exercise_16_57
// 同样都是可变参数函数，但是p198页的是非模板函数，它具有局限性，只能传入string列表的数据
// 而采用可变参数模板函数的写法，可以传入多种数据类型的参数，适用范围更广泛，但是设计难度更大
// answer: 模板版本不要求参数类型一致，当不知道函数实参的数目也不知道具体的类型时，使用模板版本更好
// 而initializer_list版本适用于同一类型的多个参数的情况，当函数实参是另一种类型时，需要编写新的函数，工作量大
// 使用模板版本更好，只是设计难度更大，需要更多的模板知识保证代码正确，例如复杂的扩展模式。

// exercise_16_58 in the strVec.hpp and Vec.hpp

// exercise_16_59
// s是一个string左值变量，传入svec.emplace_back(s)后，类型推断后Args是string&
// 在_alloc的构造函数中，传入仍然是一个左值string，会调用相应的string拷贝构造函数

// exercise_16_60_61 in the exercise.hpp
// make_shared肯定是模板参数，他的模板参数列表是一个指针指向的目标对象的类型和构造这个对象的构造函数的参数列表类型
// 因此是一个typename加一个模板参数包Args；需要使用右值引用的函数参数包让编译器保留传入的实参的实际类型
// 通过new申请空间，将指针保留给对应的智能指针，要结合std::forward<Args>(args)...和参数包扩展传给new的构造函数
// 函数接收参数包，然后进行std::forward<>()形式的包扩展，然后转发给new，作为vector的构造函数的参数

// exercise_16_62 in the Sales_data.hpp and ch16_main.cpp

void exercise_16_63_64(int argc, char **argv)
{
    checkArgs(argc, 2);
    ifstream infile;
    OpenInputFile(infile, argv[1]);
    shared_ptr<ifstream> pfile(&infile, [](ifstream *pf) { pf->close(); });

    // vector<int> ivec;
    // ReadIntoContainer(infile, ivec);
    // while (true)
    // {
    //     cout << "Please input a number to count the occurrence of that or q to quit: ";
    //     string num;
    //     cin >> num;
    //     if(!cin || num == "q") break;
    //     cout << num << " occurs " << countOccur(ivec, stoi(num)) << endl;
    // }

    // vector<double> dvec;
    // ReadIntoContainer(infile, dvec);
    // while (true)
    // {
    //     cout << "Please input a number to count the occurrence of that or q to quit: ";
    //     string num;
    //     cin >> num;
    //     if(!cin || num == "q") break;
    //     cout << num << " occurs " << countOccur(dvec, stod(num)) << endl;
    // }

    // vector<string> svec;
    // ReadIntoContainer(infile, svec);
    // while (true)
    // {
    //     cout << "Please input a number to count the occurrence of that or q to quit: ";
    //     string num;
    //     cin >> num;
    //     if(!cin || num == "q") break;
    //     cout << num << " occurs " << countOccur(svec, num) << endl;
    // }

    // 有问题，是真不会了，我放弃了，可恶啊，以后一定要使用string，const char*太坑了
    // 真不会，我也不想会了，以后就是要用string啊，const char*太搞心态了
    // 哈哈哈哈，感谢自己，没有放弃，最终解决了这个问题。指针应该指向的是堆空间，而且strcmp记错了
    // vector<const char*> cvec;
    // cvec.push_back(new const char[6]{"hello"});
    // cvec.push_back(new const char[6]{"world"});
    // cvec.push_back(new const char[2]{"!"});
    // const char *p = new const char[6]{"nan"};
    // cout << p << " occurs " << countOccur(cvec, p) << " times." << endl;

    // delete [] p;
    // delete [] cvec[2];
    // delete [] cvec[1];
    // delete [] cvec[0];
    
    vector<char*> cvec;
    ReadIntoContainer(infile, cvec);
    char *p = new char[10];
    while (true)
    {
        cout << "Please input a number to count the occurrence of that or q to quit: ";
        string num;
        cin >> num;
        if(!cin || num == "q") break;
        strcpy(p, num.c_str());
        cout << num << " occurs " << countOccur(cvec, p) << endl;
    }
    delete [] p;
    freeVec(cvec);
}

// exercise_16_65 in the exercise.hpp and ch16_main.cpp prog10

// exercise_16_66_67
// 综合看来，对于模板函数来说，应该使用函数模板特例化而不是使用函数重载，因为在接受T*的重载函数模板中
// 调用string版本，如果使用函数重载定义string版本，在T*版本的函数中调用string版本的debug_rep是无法调用的
// 只能调用模板函数的const T&版本；但如果使用模板特例化string版本，就可以调用到；
// answer: 函数模板肯定会影响函数匹配。当定义一个新的函数模板后，编译器在函数匹配过程中会将新的重载函数作为候选者之一来选择最佳匹配，
// 因此就要求我们小心设计，避免实际匹配不如我们所愿
// 模板特例化函数则不会影响函数匹配，他不是为编译器进行函数匹配时提供的一个新的选择，而是为模板的一个特殊实例提供的不同于原模板的特殊定义
// 本质上是接管了编译器在完成函数匹配后的部分实例化工作。即，当某个模板是最佳匹配时，且实例化为这个特殊实例，不再从原模板进行实例化，而是
// 直接使用这个特例化版本。因此特例化更加简单——当某个模板不符合我们的需求时，只需要设计满足需求的特例化版本即可。

int main(int argc, char **argv)
{
    // exercise_16_4(argc, argv);
    // exercise_16_4_str(argc, argv);
    // exercise_16_5_6_7(argc, argv);
    // exercise_16_14_15();
    // exercise_16_16_int(argc, argv);
    // exercise_16_16_string(argc, argv);
    exercise_16_19_20(argc, argv);
    // exercise_16_28_29_30(argc, argv);
    // exercise_16_39();
    // exercise_16_41();
    // exercise_16_63_64(argc, argv);

    return 0;
}

// exercise_16_64是我认为的最精华的题。这道题让我了解到，如果容器中保存的元素类型是指针，比如vector<char*>，那么
// 在对容器中添加元素时，这个指针必须是new返回的堆空间中的指针，因为在将vector<char*>在各个函数中进行传递进行处理
// 只有堆空间中的对象是可以被共享的，被共同访问和修改的。为什么元素类型是char*，而不是const char*呢？因为容器中所保留的
// 对象一般是需要进行修改的，因此指针所指向的对象的类型不能是const的，应该指向的是普通类型才能进行修改
// 一般来说，容器中如果元素类型是指针，应该声明为智能指针，而不是普通指针，如果是普通指针，需要记得释放申请的内存
// 这道题一直没做出来的一个重要原因就是strcmp的返回值记错了，当比较的两个字符数组相等时，返回的是0
// 当左值小于右值时，返回-1；当左值大于右值时，返回1。不能记混了
// 对于char*数组，strcmp and strcpy都是常用的函数，要好好记住

// exercise_16_66_67也特别好。说明对于模板函数来说，尽量定义特例化版本而不是进行函数重载

// Bug: 对于const成员函数返回自身，返回类型应该是const Screen<>&

// 通过实验，证明对于int*和const int*，不能进行模板实参推断，模板实参推断不能进行类型转换，即使是从non-const
// 向const类型的转换也不行