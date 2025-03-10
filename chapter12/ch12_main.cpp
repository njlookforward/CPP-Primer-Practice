#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <vector>
#include <list>
#include <new>
#include "strBlob.hpp"
#include "exercise.hpp"
#include "TextQuery.hpp"
#include "QueryResult.hpp"

using namespace std;

void prog1_shared_ptr()
{
    shared_ptr<string> p1(make_shared<string>());   // make_shared<>() is template function
    shared_ptr<list<int>> p2;
    if(p1 && p1->empty())
        *p1 = "hi";

    shared_ptr<int> p3 = make_shared<int>(42);
    shared_ptr<string> p4 = make_shared<string>(10, '9');
    shared_ptr<int> p5 = make_shared<int>();    // 进行值初始化

    cout << "*p1 = " << *p1 << endl
         << "*p3 = " << *p3 << endl
         << "*p4 = " << *p4 << endl
         << "*p5 = " << *p5 << endl;

    auto p6 = make_shared<vector<string>>();    // 可以配合auto
    auto p = make_shared<int>(42);
    auto q(p);  // copy constructor

    auto r = make_shared<int>(42);
    r = p;
}

void prog2_strBlob()
{
    strBlob sb1{"nanjiang", "is", "practising", "C++", "smart", "pointers"};
    string fir = sb1.front(),
           end = sb1.back(),
           fourth = sb1[3];
    cout << fir << endl
         << end << endl
         << fourth << endl;
    
    cout << sb1 << endl;
    strBlob sb2(sb1);
    sb2.pop_back();
    sb2.push_back("POINTERS");
    sb2[3] = "cplusplus";
    cout << sb2 << endl;
}

void prog3_new_delete()
{
    int *pi = new int();
    cout << "*pi = " << *pi << endl;    // 默认构造函数
    int *pi1 = new int(1024);
    string *ps = new string(10, '9');
    vector<int> *pv = new vector<int>{0, 1, 2, 3, 4, 5};

    cout << "pi1 = " << *pi1 << endl
         << "ps = " << *ps << endl;
    print(cout, *pv) << endl;

    // 可以使用auto用编译器自动推断
    auto pa = new auto(3.14);
    cout << "*pa = " << *pa << endl;
    // dynamic allocation also can allocate const objection
    const int *pb = new const int(24);
    cout << "*const int pb = " << *pb << endl;

    int *p1 = new (nothrow) int();  // this is placement new, 定位new, bad_alloc and nothrow is defined in header file <new>
    int *p2 = nullptr;

    // if new must delete
    delete p2;  // delete a nullptr pointer is right
    delete p1;
    delete pb;
    delete pa;
    delete pi;
    delete pi1;
    delete ps;
    delete pv;
}

void prog4_shared_ptr_new()
{
    shared_ptr<double> sp1(new double(3.14));
    shared_ptr<int> sp2(new int(1024));

    // notice: shared_ptr's single pointer constructor is expicit, so cann't convert a normal pointer to smart pointer implicitly
    // shared_ptr<int> sp3 = new int(10);   // error, convert will fail

    // shared_ptr's other operation, use reset to assign new normal pointer to be bound with smart pointer
    shared_ptr<int> sp4(sp2);
    // one usage: if shared_ptr isn't a unique pointer to resource, then duplicate a same resource
    cout << "*sp4 = " << *sp4 << endl;
    if(!sp4.unique())
        sp4.reset(new int(*sp4));   // 一般情况下，是复制自身，在这个复制值上面进行操作
    *sp4 -= 100;
    cout << "*sp4 = " << *sp4 << endl;
}

struct destination {};
struct connection {};
connection connect(destination *des);
void disconnect(connection);
void end_connection(connection *c)
{
    // disconnect(*c);
}
void prog5_shared_ptr_delete()
{
    // 智能指针和哑类
    // destination des;
    // connection con = connect(&des);
    // shared_ptr<connection> pcon(&con, [] (connection *pc) { disconnect(*pc);    });
    // shared_ptr<connection> pc(&con, end_connection);
}

void prog6_unique_ptr()
{
    // unique_ptr bind unique objection, so can't copy or assignment
    unique_ptr<int> up1(new int(42));

    unique_ptr<string> up2(new string("NanJiang"));
    // unique_ptr<string> up3(up2);    // unique_ptr 不支持拷贝操作
    // up4 = up2;  // unique_ptr 不支持赋值操作

    unique_ptr<string> up4(up2.release());  // 可以结合使用release and reset 将动态内存指针的控制权转移
    unique_ptr<string> up3(new string("TianJin"));
    up4.reset(up3.release());

    // 向unique_ptr传递删除器
    // destination des;
    // connection con = connect(&des);
    // unique_ptr<connection, decltype(end_connection)*> pc(&con, end_connection);
}

void prog7_weak_ptr()
{
    auto sp = make_shared<int>(42);
    weak_ptr<int> wp(sp);

    // weak_ptr是shared_ptr的伴随指针类，用shared_ptr而不是weak_ptr
    sp.reset();
    if(shared_ptr<int> p = wp.lock())
        cout << *p << endl;
    else
        cout << "p is nullptr" << endl;
}

void prog8_dynamic_array()
{
    int *pia = new int[8]();    // 值初始化
    for(int i = 0; i < 8; ++i)
    {
        cout << *pia++ << " ";
    }
    cout << endl;

    typedef int arrI[8];
    int *pia2 = new arrI{0, 1, 2, 3, 4, 5, 6, 7};   // 列表初始化
    for(int i = 0; i < 8; ++i)
    {
        cout << *pia2++ << " ";
    }
    cout << endl;

    string *ps = new string[8]{"a", "an", "the", string(6, 'x')};
    for(int i = 0; i < 8; ++i)
    {
        cout << *ps++ << " ";
    }
    cout << endl;

    delete [] ps;
    delete [] pia2;
    delete [] pia;
}

void prog9_unique_ptr_array()
{
    unique_ptr<int []> up(new int[8]{0, 1, 2, 3, 4, 5, 6, 7});
    // auto pia = up.release();

    // for (size_t i = 0; i < 8; i++)
    // {
    //     cout << pia[i] << " ";
    // }
    // cout << endl;

    // delete [] pia;

    for (size_t i = 0; i < 8; i++)
    {
        up[i] *= 2;
        cout << up[i] << " ";
    }
    cout << endl;

    up = nullptr;

    cout << "use shared_ptr to save dynamic array's pointer." << endl;
    shared_ptr<int> sp(new int[8](), [] (int *pi) { delete [] pi;   });
    for(size_t i = 0; i < 8; ++i)
    {
        *(sp.get() + i) = i * 2;
        cout << *(sp.get() + i) << " ";
    }
    cout << endl;
}

void prog10_textquery(int argc, char *argv[])
{
    checkargc(argc, 2);
    ifstream inputfile;
    openinfile(inputfile, argv[1]);
    shared_ptr<ifstream> pf(&inputfile, [](ifstream *pf) {  pf->close();    });

    TextQuery tq(inputfile);
    while (true)
    {
        cout << "Please input a word which you want to query in the text or 'q' to exit this name: ";
        string word;
        if(!(cin >> word) || word == "q")
            break;
        QueryResult qr = tq.query(word);
        cout << qr << endl;
    }
}

void prog11_allocator()
{
    // string *const p = new string[8]();  // 作为首地址固定存储
    // string stmp;
    // string *q = p;
    // while (cin >> stmp && q != p + 8)
    // {
    //     *q++ = stmp;
    // }

    // for(auto ps = p; p != q; ++ps)
    //     cout << *ps << " ";
    // cout << endl;

    // delete [] p;

    allocator<string> allocStr;
    auto const ps = allocStr.allocate(8);   // 通过auto得到const的写法
    // 开始一步步构造对象
    auto qs = ps;
    allocStr.construct(qs++);   // empty string
    allocStr.construct(qs++, 10, 'c');
    allocStr.construct(qs++, "hi");

    qs = uninitialized_fill_n(qs, 5, "Nan");

    for(auto bg = ps; bg != qs; ++bg)
        cout << *bg << " ";
    cout << endl;

    while (qs != ps)
    {
        allocStr.destroy(--qs);
    }
    allocStr.deallocate(ps, 8);

    vector<int> ivec{1, 1, 2, 3, 5, 8, 13, 21};
    allocator<int> allocInt;
    auto const pi = allocInt.allocate(ivec.size() * 2);
    auto qi = uninitialized_copy(ivec.begin(), ivec.end(), pi);
    qi = uninitialized_fill_n(qi, ivec.size(), 24);

    for(auto it = pi; it != qi; ++it)
        cout << *it << " ";
    cout << endl;

    while (qi != pi)
    {
        allocInt.destroy(--qi);
    }
    allocInt.deallocate(pi, ivec.size() * 2);
}

int main(int argc, char *argv[])
{
    // prog1_shared_ptr();
    // prog2_strBlob();
    // prog3_new_delete();
    // prog4_shared_ptr_new();
    // prog5_shared_ptr_delete();
    // prog6_unique_ptr();
    // prog7_weak_ptr();
    // prog8_dynamic_array();
    // prog9_unique_ptr_array();
    prog10_textquery(argc, argv);
    // prog11_allocator();

    return 0;
}