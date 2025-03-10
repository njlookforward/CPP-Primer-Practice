#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Sales_data.hpp"
#include "HasPtr.hpp"
#include "exercise.hpp"
#include "strVec.hpp"

using namespace std;

void prog1_copy_control()
{
    string dots(10, '.');   // direct initialization
    string s(dots);         // direct initialization
    // 拷贝初始化使用拷贝构造函数或者移动构造函数
    string s2 = dots;       // copy initialization, formation is "="
    string s3 = "9-999-99999";  // copy initialization
    string s4 = string(10, '9');    // copy initialization

    // destructor
    Sales_data *p = new Sales_data;
    auto sp = make_shared<Sales_data>();
    Sales_data item(*p);
    vector<Sales_data> sdvec;
    sdvec.push_back(*sp);

    delete p;
}

void prog2_three_five_principle()
{
    HasPtr hp1("C++");
    HasPtr hp2 = fcn_rval(hp1); // 猜测可能是hp2直接就是ret的值，所以没有调用构造函数，只是换个变量名称而已
}

void prog3_delete()
{
    NoCopy nc1;
    // NoCopy nc2 = nc1;
    NoCopy nc3;
    // nc3 = nc1;
    // NoDtor nd1;
    // NoDtor *pnd = new NoDtor;
    // delete pnd;

    PrivateCopy pc1, pc3;
    // PrivateCopy pc2 = pc1;
    // pc1 = pc3;
}

void prog4_strVec()
{
    strVec svec1;
    string str;
    while (cin >> str)
    {
        svec1.push_back(str);
    }
    svec1.pop_back();
    svec1.pop_back();
    cout << "svec1:" << endl;
    print(cout, svec1) << endl;

    strVec svec2(8);
    cout << "svec2:" << endl;
    print(cout, svec2) << endl;
    cin.clear();
    auto iter = svec2.begin();
    while(cin >> str && iter != svec2.end())
    {
        *iter++ = str;
    }
    cout << "svec2:" << endl;
    print(cout, svec2) << endl; 

    strVec svec3 = {"Piglet", "Eeyore", "Roo", "Chris", "Kanga", "Pooh", "Tigger"};
    cout << "svec3:" << endl;
    print(cout, svec3) << endl;

    svec2 = svec3;
    cout << "svec2:" << endl;
    print(cout, svec2) << endl;

    strVec svec4(svec1);
    cout << "svec4:" << endl;
    print(cout, svec4) << endl;
}

void prog5_move()
{
    int i = 42;
    int &lr = i; // lvalue reference
    // int &&rr = i;   // error
    // int &lr2 = i * 42;  // error
    const int &cr = i * 42;
    int &&rr2 = i * 42; // rvalue reference
    // int &&rr3 = rr2;    // error, rvalue reference is lvalue,此时编译器中rr2是int类型
    int &&rr3 = std::move(rr2); // std::move定义在utility头文件中

    Y y1, y2 = std::move(y1);
    hasY hy1, hy2 = std::move(hy1); // 都使用合成移动构造函数
}

void prog6_mf_move()
{
    strVec svec;
    string s = "some string or another";
    svec.push_back(s);
    svec.push_back("done");

    Foo i,j;
    i = j;  // this is lvalue, right
    retFoo(j) = i;  // this is lvalue, right
    // retVal() = j;   // error, this is rvalue
    i = retVal();
    retVal().sorted();
    retFoo(i).sorted();
}

int main()
{
    // prog1_copy_control();
    // prog2_three_five_principle();
    // prog3_delete();
    // prog4_strVec();
    // prog5_move();
    prog6_mf_move();

    return 0;
}