#include <string>
#include <vector>
#include <functional>
#include <fstream>
#include "strBlob.hpp"
#include "exercise.hpp"

using namespace std;

void prog1_overload()
{
    // usually operator+ is defined non-member function, 对称性运算可以交换左操作数和右操作数的位置
    string s = "world";
    string t = s + "!";
    string u = "hi" + t;
}

void prog2_dereference_arrow()
{
    // 重载箭头运算符，可以改变的是从哪个对象中获取数据成员，而箭头运算符获取成员这一事实永远不会改变
    strBlob sb{"hi", "bye", "now"}; // 直接初始化
    strBlobPtr psb(sb);
    *psb = "okay";
    cout << psb->size() << endl
         << (*psb).size() << endl;
}

void prog3_function_object()
{
    int i = -42;
    absInt absobj;
    cout << absobj(i) << endl;

    vector<string> svec = {"hello", "C++", "world"};
    PrintString printer;
    printer(svec[0]);

    PrintString errors(cerr, '\n');
    errors(svec[1]);

    for_each(svec.begin(), svec.end(), PrintString(cout, '\n'));
}

void prog4_functional()
{
    plus<int> intAdd;
    negate<int> intNegate;
    cout << intAdd(10, 20) << endl
         << intNegate(intAdd(10, 20)) << endl;

    // vector<string> svec;
    // sort(svec.begin(), svec.end(), greater<string>());
    // vector<string *> nameTable;
    // sort(nameTable.begin(), nameTable.end(), less<string *>());
    // // 可以使用标准库的比较函数比较指针值
}

A Foo(const A&ca) { return ca;  }
void f1(long double) {}
void manip(const C&) {}
void manip(const D&) {}
void manip(const E&) {}

void prog5_type_cast()
{
    smallInt si = 3.14;
    cout << static_cast<int>(si) + 3.14 << endl;

    B b;
    /*****两个类定义了相同的类型转换函数的二义性******/
    // A a = Foo(b);
    // A a = Foo(A(b));
    A a = Foo(b.operator A());

    /*******定义了多个转换源是算数类型且类型转换运算符目标是算符类型的二义性*******/
    A a1;
    // f1(a1);
    // long ld = 12;
    // A a2(ld);
    short s = 42;
    A a3(s);

    /*****重载函数和隐式转换构造函数的二义性*******/
    int i = 10;
    // manip(i);
    // manip(C(10));

    /******重载函数和定义多个转换源或转换目标是算数类型的二义性*******/
    smallInt si1 = 1, si2 = 2;
    smallInt si3 = si1 + si2;

    // int sumI = si3 + 0;
}

void prog6_bind_function(int argc, char **argv)
{
    function<decltype(sizeCompare)> fp1 = sizeCompare;
    using namespace placeholders;
    function<bool (const std::string &)> fp2 = bind(sizeCompare, _1, 6);

    // function<decltype(sizeCompare)>::result_type ret;    // 很有意思的玩法

    ifstream ifs;
    openfile(ifs, argv[1]);

    vector<string> svec;
    string word;
    while (ifs >> word)
    {
        svec.push_back(cleanup_str(word));
    }
    cout << count_if(svec.cbegin(), svec.cend(), fp2) << endl
         << count_if(svec.cbegin(), svec.cend(), bind(sizeCompare, _1, 6)) << endl;

    ifs.close();
}

int main(int argc, char **argv)
{
    // prog2_dereference_arrow();
    // prog3_function_object();
    // prog4_functional();
    // prog5_type_cast();
    prog6_bind_function(argc, argv);

    return 0;
}