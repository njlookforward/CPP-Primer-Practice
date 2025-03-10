#include <vector>
#include <iterator>
#include <algorithm>
#include "exercise.hpp"
#include "BinaryTree.hpp"
#include "HasPtr.hpp"
#include "strVec.hpp"
#include "TextQuery.hpp"
#include <cstring>
#include "String.hpp"
using namespace std;

// exercise_13_1
// copy constructor's formation is class(const class &);
// 拷贝构造函数使用同一个类类型的对象来初始化一个新的对象。一般用于拷贝初始化的场景，如下面所示
// 用=定义一个新的对象
// 将实参传递给函数中非引用类型的形参
// 函数返回非引用类型的对象
// 列表初始化数组中的元素或者聚合类中的成员

// exercise_13_2
// Sales_data::Sales_data(Sales_data rhs); why is invalid?
// 该函数本意是定义一个拷贝构造函数，但是形参采用的是非引用形式，当调用这个函数时，实参传递给形参也是拷贝初始化
// 继续调用这个函数，循环往复下去会无限调用自身，这是错误的，需要将形参定义成const Sales_data &

// exercise_13_3
// 当我们拷贝一个strBlob时，会调用strBlob的合成拷贝构造函数，其中调用shared_ptr<vector<string>>的拷贝构造函数
// 新建对象与源对象两者同时指向同一底层数据，shared_ptr的引用计数加一；
// 拷贝一个strBlobPtr时，调用strBlobPtr的合成拷贝构造函数，其中调用weak_ptr<vector<string>>的拷贝构造函数和拷贝size_t成员
// weak_ptr指向底层数据的引用计数不变

// exercise_13_4 write in the book
// exercise_13_5 is HasPtr.hpp

// exercise_13_6
// 拷贝赋值运算符是自定义类型的赋值运算符重载，一般形式式 T &operator=(const T &);作为公有成员函数
// 当用同一种类类型对象去赋值另一个对象时，调用拷贝赋值运算符
// 编译器合成的拷贝赋值运算符是逐成员赋值，memberwise assignment, 内置类型直接赋值，类类型调用其拷贝赋值运算符函数
// 当自定义类没有定义自己的拷贝赋值运算符，它的析构函数没有被删除或者定义为私有成员函数，而且如果他的数据成员中有自定义类型
// 这个自定义类型的数据成员含有自己的拷贝赋值运算符函数和正常的析构函数，即使也是合成的，
// 那么编译器可以为这个自定义类型合成拷贝赋值运算符函数

// exercise_13_7
// 将一个strBlob赋值给另一个strBlob，会调用拷贝赋值运算符函数，可能是合成的，其调用shared_ptr<vector<string>的拷贝赋值运算符函数 
// 左侧智能指针的引用计数减一，如果变为0，则会释放所指向的对象，指针指向右侧对象智能指针所指向的对象。
// 然后右侧对象的智能指针的引用计数加一;
// 如果赋值一个strBlobPtr，会调用其合成赋值运算符函数，size_t数据成员直接赋值，weak_ptr<vector<string>>数据成员
// 调用其赋值运算符函数，将指针指向右侧对象所指向的对象

// exercise_13_8 is HasPtr.hpp

// exercise_13_9
// 析构函数是对象即将被销毁时所调用的函数，一般类型是 ~T() {}，析构函数只能有一个，不能被重载;
// 析构函数所执行的操作与构造函数正好相反，先执行函数体，函数体中一般用来释放对象所申请的资源，然后逆序销毁各个数据成员
// 执行各个数据成员的析构函数;
// 当自定义类型中未显示定义析构函数，编译器会合成一个默认析构函数，形式为~T() {}; 只会是一个空函数体
// 合成析构函数主要完成析构函数体执行完后的析构部分，即逆序执行各个数据成员的析构函数，逐一销毁
// 当自定义类型未显示定义自己的析构函数，而且它的数据成员都有合法的析构函数，这时候可以合成析构函数

// exercise_13_10
// 当一个strBlob对象销毁时，会调用编译器生成的合成析构函数，函数体为空，执行析构部分，调用shared_ptr<vector<string>>
// 的析构函数，释放所指向的vector<string>对象；
// 当一个strBlobPtr对象销毁时，会调用编译器生成的析构函数，函数体为空，逆序销毁数据成员，先销毁size_t成员，什么都不用做
// 然后调用weak_ptr<vector<string>>的析构函数，完成销毁过程

// exercise_13_11 is HasPtr.hpp
// exercise_13_12
// implement three Sales_data's destructor

void exercise_13_13()
{
    X x1;   // default constructor
    X x2(x1);   // copy constructor
    X x3(std::move(x1));    // move constructor

    x1 = x2;    // copy assignment
    x2 = std::move(x3); // move assignment
    
    X x4 = x1;  // copy constructor

    // 实参传递
    cout << endl;
    fcn1_copy(x4);
    fcn1_copy(std::move(x4));   // x4,x3 is after move
    // 返回值是右值
    cout << endl;
    X x5 = fcn2_right_val();    // 编译器略过了拷贝构造函数的调用，直接进行默认初始化
    // 返回值是左值
    X x6 = fcn3_left_val(x5);
    // vector and array push_back
    cout << endl;
    vector<X> xvec;
    xvec.push_back(x6);
    X xarr[] = {x1, x2};

    cout << endl;
    X *px = new X;
    delete px;
}

// exercise_13_14
// 全是a的mysn的数值
// exercise_13_15
// numbered定义了自己的拷贝构造函数，因此发生拷贝构造时，每个新对象都有了自己的新的mysn值，因此会改变结果
// 调用函数采用传值方式，因此调用拷贝构造函数，结果是输出不一样的mysn值，不同于a，也不同于b，更不同于c。
// exercise_13_16
// 会改变输出结果，结果是a.mysn b.mysn c.mysn，因为采用传引用方式调用函数，不需要构造新对象

void exercise_13_17()
{
    numbered a, b = a, c = b;
    cout << "original: " << a.mysn << "\t"
         << b.mysn << "\t" << c.mysn << endl;
    fcn_print_num(a);
    fcn_print_num(b);
    fcn_print_num(c);
}

// exercise_13_18_19 is Exercise.hpp
// 不需要定义自己的拷贝控制函数，根据业务逻辑设定的

// exercise_13_20
// 对于TextQuery类，拷贝TextQuery对象时，调用合成拷贝构造函数，顺序调用数据成员的拷贝构造函数，首先是拷贝shared_ptr<vector<string>>
// 引用计数加一，智能指针指向相同的vector对象，然后调用map<string, shared_ptr<set<size_t>>>的拷贝构造函数，
// 拷贝一个map对象，完成拷贝初始化工作；当赋值一个TextQuery对象时，同样调用合成拷贝运算符函数，逐一调用数据成员的
// 拷贝赋值运算符函数；销毁一个TextQuery对象时，调用合成析构函数，函数体为空，然后逆序执行各个数据成员的析构函数
// 对于QueryResult类，执行类似的过程

// exercise_13_21
// 对于TextQuery and QueryResult两个类，我认为不需要自己定义他们的拷贝控制成员，使用编译器合成的就足够了。因为这两个类
// 的数据成员都已经设计好了自己的拷贝控制成员，我们只需要去调用就可以了

// exercise_13_22 is HasPtr.hpp
// exercise_13_23
// 在编写拷贝赋值运算符时，需要考虑全面，即使是自赋值也能正确运行，通过在销毁左侧对象资源之前复制右侧对象的资源

// exercise_13_24
// 如果HasPtr未定义析构函数，则会发生内存泄漏，每个对象被销毁时，不会释放自己申请的资源
// 如果HasPtr未定义拷贝构造函数，则会引发更大的问题，如果用一个HasPtr对象去初始化新的HasPtr对象，那么两个对象
// 会指向相同的string对象，而且没有引用计数机制，如果一个对象被销毁了，那么指向的string对象就被释放了，另一个HasPtr
// 中的string指针就变成了dangling pointer，一旦被使用，string是未知的，而且一旦HasPtr被销毁，还会造成同一指针被释放两次
// 行为是未知的。因此需要自定义拷贝控制成员

// exercise_13_25_26
// strBlob的拷贝构造函数需要利用右侧对象指针所指向的值来申请新空间创建一个新的智能指针；拷贝赋值运算符需要
// 利用reset来释放之前所指向的对象，然后申请新的空间，指向新的指针
// 由于使用智能指针来管理动态内存，所以对象销毁时可以自动释放资源，因此不需要自定义析构函数，调用shared_ptr数据成员的
// 析构函数就足够了

// exercise_13_27 is HasPtr.hpp's Phasptr

void exercise_13_28()
{
    // 类值方式拷贝字符串二叉树
    BinStrTree bt1;
    bt1.insert("Piglet");
    bt1.insert("Eeyore");
    bt1.insert("Roo");
    bt1.insert("Chris");
    bt1.insert("Pooh");
    bt1.insert("Tigger");
    bt1.insert("Kanga");

    BinStrTree bt2(bt1);
    cout << "inorder traverse bt1:" << endl;
    bt1.inorderTraversal();
    cout << endl
         << "inorder traverse bt2:" << endl;
    bt2.inorderTraversal();
    cout << endl;

    bt2.insert("Piglet");
    bt2.insert("Piglet");
    bt2.insert("Kanga");
    bt2.insert("Tigger");

    bt1 = bt2;
    cout << "inorder traverse bt1:" << endl;
    bt1.inorderTraversal();
    cout << endl
         << "inorder traverse bt2:" << endl;
    bt2.inorderTraversal();
    cout << endl;
}

// exercise_13_29
// swap(HasPtr&, HasPtr&)的调用不会导致递归循环，因为函数匹配，函数内部调用的是std::swap(std::string *&, std::string *&);
// and std::swap(size_t &, size_t &);因此使用的是不同的函数，不会发生递归循环

void exercise_13_30()
{
    HasPtr hp1("nanjiang"); // default constructor
    HasPtr hp2(hp1);        // copy constructor
    HasPtr hp3 = HasPtr("C++"); // move constructor,这种形式应该是编译器做了优化，绕过移动构造函数，直接默认构造函数

    hp1 = hp3;  // copy assignment operator
    hp3 = std::move(hp2);   // move assignment operator
}

void exercise_13_31()
{
    vector<HasPtr> hpvec;
    istream_iterator<string> bgit(cin), eof;
    copy(bgit, eof, back_inserter(hpvec));
    sort(hpvec.begin(), hpvec.end());
    ostream_iterator<HasPtr> outer(cout, " ");
    copy(hpvec.begin(), hpvec.end(), outer);
    cout << endl;
}

// exercise_13_32
// 定义类指针拷贝语义的Phasptr的swap函数也会提高交换函数的性能，但是不如类值拷贝语义提升的那么大
// 避免的创建交换媒介对象temp，减少了多次调整引用计数的操作，直接交换指针和引用计数即可

// exercise_13_33
// 因为我们不仅要添加要保存的文件夹的真实地址，还要操作folder添加消息，因此要想能够操作传入函数的实参，必须
// 传引用参数或者传入指针，本次设计为传引用参数。不能传入Folder，这是复制的值，不能修改原值；也不能传入const Folder &
// 我们就无法修改Folder,添加我们的Message指针

// exercise_13_34 is Message.hpp and Message.cpp

// exercise_13_35
// 如果Message使用合成的拷贝控制成员，仅仅是改动Message的数据成员，无法同步更新Folder对象
// Folder中保存的Message *的集合就是错误的，无法通过Folder访问message

// exercise_13_36 is Folder.hpp and Folder.cpp
// exercise_13_37 is Message.hpp and Message.cpp

// exercise_13_38
// 仍然是从工作效率的角度去考虑，拷贝控制成员的主要目的是操作_folders成员更新对应的Message *,一般形式的拷贝赋值运算符操作
// 只需要删除左侧folder集合中Message指针，然后将Message添加到右侧对象的folder集合中，两次簿记操作；而采用拷贝并交换技术
// 实现拷贝赋值运算符，创建形参和销毁形参需要两次簿记操作，中间的交换过程需要四次簿记操作，共六次簿记操作，没有必要。

// exercise_13_39_40 is strVec.hpp and strVec.cpp
void exercise_13_39_40()
{
    vector<string> svec = {"Piglet", "Eeyore", "Roo", "Chris", "Kanga", "Pooh", "Tigger"};
    cout << "size(): " << svec.size() << endl
         << "capacity(): " << svec.capacity() << endl << endl;
    svec.reserve(20);
    cout << "size(): " << svec.size() << endl
         << "capacity(): " << svec.capacity() << endl;
    
    svec.resize(16);
    cout << "size(): " << svec.size() << endl
         << "capacity(): " << svec.capacity() << endl << endl
         << "Now, let's trial strVec:" << endl;
    
    strVec sv = {"Piglet", "Eeyore", "Roo", "Chris", "Kanga", "Pooh", "Tigger"};
    cout << "size(): " << sv.size() << endl
         << "capacity(): " << sv.capacity() << endl;
    
    sv.reserve(15);
    cout << "size(): " << sv.size() << endl
         << "capacity(): " << sv.capacity() << endl;

    sv.reserve(5);
    cout << "size(): " << sv.size() << endl
         << "capacity(): " << sv.capacity() << endl;

    sv.resize(10, "NanJiang");
    cout << "size(): " << sv.size() << endl
         << "capacity(): " << sv.capacity() << endl;
    print(cout, sv) << endl;

    sv.resize(5);
    cout << "size(): " << sv.size() << endl
         << "capacity(): " << sv.capacity() << endl;
    print(cout, sv) << endl;  
}

// exercise_13_41
// _alloc.construct(newFirFree++, std::move(*iter++));只有通过后置++运算符，才能保证正确的逻辑
// 即构造的对象从第一个空闲空间开始，赋值源对象从就内存空间的第一个有效对象开始，构造成功后新旧指针都向前前进一步
// 如果使用前置++运算符，导致程序从新申请的第二个空闲空间开始构造，这是未定义的行为，必须从第一个空闲空间开始构造才是正确的

void exercise_13_42(int argc, char *argv[])
{
    checkargc(argc, 2);
    ifstream infile;
    openinfile(infile, argv[1]);
    shared_ptr<ifstream> pf(&infile, [] (ifstream *pf) {    pf->close();    });

    TextQuery tq(infile);
    do {
        cout << "Please input a word to query or 'q' to exit: ";
        string word;
        if(!(cin >> word) || word == "q")
            break;
        
        cout << tq.query(word) << endl;
    } while(true);

    // 在这次修改中，体会到了面向对象的好处，改起来真的挺方便的
}

// exercise_13_43
// 我更倾向于使用while循环的destroy版本，顺序构造，应该逆序销毁，这样的逻辑更清晰，顺序销毁，有些反常

void exercise_13_44()
{
    String s1;
    cin >> s1;
    cout << s1 << endl;

    String s2("C++5");
    s2.pop_back();
    cout << s2 << endl;

    String s3(s1);
    cout << s3 << endl;
    s3 = s2;
    cout << s3 << endl;

    String s4;
    getline(cin, s4);
    cout << s4 << endl;
    
    // String.hpp and String.cpp is trialed in the selfQuery
}

// exercise_13_45
// lvalue reference and rvalue reference是互补的关系，左值引用绑定到左值，左值持久，是一个已经定义的对象
// 而右值引用绑定到右值，右值短暂，可以是一个表达式的返回值，可以是一个创建的临时对象，可以是一个字面值常量
// 除此之外，两者都是引用，都是绑定到某个对象上面。
// exercise_13_46 write in the book Notification:右值引用是左值，只要是显式定义的对象就是左值
// exercise_13_47 is String.hpp and String.cpp

void exercise_13_48()
{
    vector<String> svec;
    String word;
    while (cin >> word)
    {
        svec.push_back(word);
    }
    for (auto &w : svec)
    {
        cout << w << " ";
    }
    cout << endl;
}

// exercise_49_50 is String.hpp strVec.hpp Message.hpp and exercise_13_48
// exercise_13_51
// clone中的unique_ptr以值的形式返回，因为函数的返回值是右值，是即将被销毁的临时对象，因此用clone函数的
// 返回值初始化或者赋值一个unique_ptr对象，调用的是移动构造函数和移动赋值运算符函数，因此正确工作

// exercise_13_52
// 利用拷贝并交换的技术实现赋值运算符，可以用一套代码实现拷贝赋值和移动赋值，秘密就在形参上
// hp = hp2 hp2是左值，用hp2初始化赋值运算符函数的形参rhs，调用的是拷贝构造函数，拷贝一份string资源
// 然后交换左值与rhs的资源，完成赋值；
// hp = std::move(hp2); 传递给赋值运算符函数的是一个右值，调用移动构造函数初始化形参rhs，然后交换左值与rhs
// 的资源，完成拷贝

// exercise_13_53
// 从底层效率的角度来说，的确直接定义移动赋值运算符函数要比利用移动并交换的技术效率更高（拷贝过程也出不多这样）
// 直接定义移动赋值：释放旧内存+赋值新的指针和索引数据+移动源对象空指针处理
// 移动并交换：移动构造函数创建新的对象+赋值指针+移动源对象空指针处理+交换资源+形参析构(释放旧内存)
// 可以看到拷贝并交换技术需要创建一个形参，多出了一步交换操作，因此效率更低，因此最好定义自己的拷贝和移动赋值运算符函数

// exercise_13_54 is exercise_13_30
// 结果是函数匹配出现了二义性，（常量）左值引用与左值是同一优先级；右值引用与右值是同一优先级

// exercise_13_55 is strBlob.hpp
// exercise_13_56
// 会发生无限调用自身，陷入死循环,infinite resursion,无限递归

// exercise_13_57
// return Foo(*this).sorted();  // const &&的函数体会调用sorted() &&版本，成功返回


int main(int argc, char *argv[])
{
    // exercise_13_13();
    // exercise_13_17();
    // exercise_13_28();
    // exercise_13_30();
    // exercise_13_31();
    // exercise_13_39_40();
    // exercise_13_42(argc, argv);
    // exercise_13_44();
    // exercise_13_48();

    return 0;
}