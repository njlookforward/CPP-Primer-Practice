#include "Sales_data.hpp"
#include "Screen.hpp"
#include "Debug.hpp"
#include "Account.hpp"
#include <cctype>
using namespace std;

void prog1_Sales_data()
{
    // 一条一条地读取书籍售卖信息，将同一书号进行归位
    // Sales_data total;   // 汇总消息
    // if(read(cin, total))
    // {

    // exercise_7_13
    Sales_data total(cin);
    if(cin)
    {
       Sales_data trans(cin);
       do
       {
            if(trans.isbn() == total.isbn())
                total.combine(trans);
            else{
                print(cout, total) << endl << endl;
                total = trans;
            }
       } while (read(cin, trans));
        print(cout, total) << endl;
    }
    else
        cerr << "No data?" << endl;
}

void prog2_screen()
{
    Screen myScreen(6, 6, "NanJiang is practising C++");
    char aimCh = myScreen.get();
    if(islower(aimCh = myScreen.get(2,4)))
        myScreen.move(2,4).set(toupper(aimCh));
    aimCh = myScreen.get();

    myScreen.set(1,6, toupper(myScreen.get(1,6)));
    myScreen.display(cout);

    const Screen blank(5, 5, "####This ia NanJiang speakong####");
    blank.display(cout);
}

struct First
{
    int memi;
    int getMem();
};

struct Second
{
    int memi;
    int getMem();
};

void prog3_class()
{
    // 只要名字不同，两个类就是完全不一样的类型
    First obj1;
    // Second obj2 = obj1;

    Sales_data item1;
    struct Sales_data item2;
    class Sales_data item3;
}

class Link_screen {
private:
    Screen _window;
    Link_screen *prev;
    Link_screen *next;  // 不完全类型，只能用指针或引用
};

void prog4_friend()
{
    Window_mgr winctl;
    winctl.insert(Screen(24, 80, "This is NanJiang"));
    winctl.insert(Screen(3, 6, '$'));
    winctl.clear(2);
    winctl.clear(0);
}

typedef double Money;
string bal;
class myAccount {
public:
    Money balance() {   return bal; }   // 返回的是数据成员，不是外部的string对象
private:
    // typedef double Money;   // error，不能在类内部重复定义 

    Money bal;
};

void prog5_class_scope()
{
    Screen window(4, 4, "NanJiang is practising C++ programming!");
    char aimCh = window.get();
    aimCh = window.dummy_fcn(2).get();

    window.setHeight(8);
}

class ConstRef {
public:
    ConstRef(int i): ii(i), ci(i), ri(i) {}

private:
    int ii;
    const int ci;
    int &ri;
};

struct X {
    X(int i, int j): rem(i % j), base(i) {}
    int rem, base;
};

void prog6_constructor()
{
    X xobj = X(8, 3);   // 不经意的失误说明临时值不被分配内存
}

void prog7_converting_constructor()
{
    // 隐式的类类型转换，每次只能转换一种类型，而且转换构造函数是只有一个形参的
    Sales_data item("0-201-88954-4", 2, 15);
    string null_book("0-201-88954-4");
    item.combine(Sales_data("0-201-88954-4"));  // 显示转化
    // item.combine(string("0-201-88954-4"));  // 每次只能进行一步转换，const char* --> string --> Sales_data
    // item.combine(cin);
    item.combine(Sales_data(null_book));
    item.combine(static_cast<Sales_data>(cin)); // use static_cast to explicit convertion
    print(cout, item);
    // Sales_data item2 = null_book;
}

struct Data {
    int ival;
    string str;
};

void prog8_aggregate()
{
    Data dataobj = {0, "Anna"};
    cout << dataobj.ival << " " << dataobj.str << endl;
}

void prog9_constexpr_class()
{
    constexpr Debug io_sub(false, true, false);
    if(io_sub.any())
    {
        cerr << "print appropriate error messages" << endl;
    }
    // io_sub.set_hw(true);
    // 不要被constexpr吓到，他仍然是const对象，只不过是字面值常量，是一种直接用字面值替代的对象，不会提供内存

    Debug hw_sub(true, false, false);
    if(hw_sub.any())
    {
        cerr << "occur hardware error" << endl;
    }
    hw_sub.set_hw(false);

    constexpr Debug prod(false);
    if(prod.any())
    {
        cerr << "print an error message" << endl;
    }
}

void prog10_static_member()
{
    Account myAccount("nanjiang", 577.98);
    Account *pa = &myAccount;
    double rate = Account::rate();
    rate = myAccount.rate();
    pa->calculate();
    myAccount.calculate();
    Account::rate(0.013);
    myAccount.calculate();
}

// 静态成员能用于某些场景，而普通成员不能
class Bar {
private:
    static Bar _stamem; // 静态成员可以是不完全类型
    Bar *_pmem;         // 普通成员中指针和引用可以是不完全类型
    Bar &_rmem;           // 普通成员必须是完全类型
};

int main()
{
    prog1_Sales_data();
    // prog2_screen();
    // prog3_class();
    // prog4_friend();
    // prog5_class_scope();
    // prog6_constructor();
    // prog7_converting_constructor();
    // prog8_aggregate();
    // prog9_constexpr_class();
    // prog10_static_member();

    return 0;
}