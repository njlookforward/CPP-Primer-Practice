#include "Sales_data.hpp"
#include "Screen.hpp"
#include "Example.hpp"
#include <vector>
using namespace std;

void exercise_7_1_record()
{
    cout << "This program is to count soldRecord" << endl;
    Sales_data total;
    if(read(cin, total))
    {
        unsigned cnt = 1;
        Sales_data trans;
        while (read(cin, trans))
        {
            if(total.isbn() == trans.isbn())
                ++cnt;
            else
            {
                print(cout, total) << endl << "SoldRecord:\t" << cnt << endl << endl;
                total = trans;
                cnt = 1;
            }
        }
        print(cout, total) << endl << "SoldRecord:\t" << cnt << endl;
    }
    else
        cerr << "No data?" << endl;
}

// exercise_7_2 exercise_7_3 exercise_7_6 exercise_7_7 have being exercised in the prog1
// exercise_7_8
// read函数中，需要从输入流中读取数据并写入到Sales_data中，因此使用普通引用
// print函数中，只需要读取Sales_data中的数据到输出流中，不需要写入数据，因此使用常量引用

// exercise_7_10
// if(read(read(cin, data1), data2)), 先后从输入流中读取数据写入到data1和data2中，如果成功写入则条件为真
// 写入失败则条件为假

void exercise_7_11()
{
    Sales_data data1_default,
               data2_string("0-201-70353-X"),
               data3_three("0-201-82470-1", 4, 45.39),
               data4_cin(cin);
    
    print(cout, data1_default) << endl << endl;
    print(cout, data2_string) << endl << endl;
    print(cout, data3_three) << endl << endl;
    print(cout, data4_cin) << endl << endl;
}

// exercise_7_16
// 在类的定义中访问说明符出现的次数和位置没有规定，访问说明符可以设置多次，它的有效性是从定义开始直到下一个访问说明符之前
// 作为类的接口的成员应该在public之后，可以被类的用户所访问
// 作为类的内部实现的成员应该在private之后，可以被友元和内部成员访问，作为类的封装

// exercise_7_17
// struct and class unique distinction is default access权限，struct is public, class is private

// exercise_7_18
// encapsulation 是将类的内部实现放在private访问说明符之后，只能被类的友元或成员访问，外界类的使用者是无法访问的
// 封装将类的实现与类的接口分离，外部代码使用类的接口不会破坏类，而且一旦改变类的内部实现，因为类的接口没有改变
// 所以不需要修改任何用户代码，维护更加便捷

// exercise_7_19
// 我将constructor, member function-name()-address()放在public中，作为类的接口，方便外界调用
// 将所有的数据成员放在private中封装起来，不受外界破坏

// exercise_7_20
// 一旦某些函数或者类需要访问类的私有成员，就将其设为友元函数或者友元类
// 我的理解是尽量不要用友元，因为友元破坏了类的封装性，尽量设置合适的接口以避免友元

// exercise_7_25
// Screen能够安全的依赖默认的拷贝和赋值操作，因为数据成员中没有指针等需要额外申请空间资源的对象
// 因此可以执行默认的拷贝和赋值操作

void exercise_7_27()
{
    Screen myScreen(5, 5, 'X');
    myScreen.move(4,0).set('#').display(cout);
    cout << endl;
    myScreen.display(cout);
    cout << endl;
}

// exercise_7_28
// 第一个display是修改后的结果，但第二个display是修改前的结果

// exercise_7_30
// 显式地使用指针访问成员更加清晰，但是更繁琐，个人认为不如使用隐式this指针访问成员

// exercise_7_32
// 只能让整个window_mgr作为Screen的友元类，因为window_mgr中使用了Screen类型，前置声明作为不完全类型是无效的
// 因此没法单单让clear作为Screen的友元成员函数

// exercise_7_34
// 若将typedef std::string::size_type pos放在类定义的最后一行，则会发生编译错误
// 因为其他成员的类型是pos的话，进行名字查找找不到类型别名的定义，发生编译错误

void exercise_7_38()
{
    Sales_data trans;
    print(cout, trans) << endl;
}

// exercise_7_39
// 我认为都接受默认实参，会产生匹配冲突，由于优先级相同编译器不知道选择哪一个，导致编译错误ambiguous

// exercise_7_40 进行对象的抽象，那些可以作为数据成员，并配套构造函数
class Date {
public:
    Date(int year = 2024, int month = 11, int day = 21):
        _year(year), _month(month), _day(day) {}

private:
    int _year;
    int _month;
    int _day;
};

// exercise_7_42 no need to exercise

// exercise_7_43
class NoDefault {
public:
    NoDefault(int val): _val(val) {}

private:
    int _val;
};

class C {
public:
    C() = default;

private:
    NoDefault _my_mem = 0;  // 运用类的隐式类型转换，使用了NoDefault的int构造函数
};

void exercise_7_43()
{
    C cobj;
    // exercise_7_44
    // vector<NoDefault> vec(10);
    // 我认为这个声明不合法，因为NoDefault没有默认构造函数进行初始化
    // exercise_7_45
    vector<C> vec(10);  // 声明是合法的，因为class C has default constructor
}

// exercise_7_47
// 我认为接受一个string参数的Sales_data构造函数不应该是explicit,这样做的优点是可以隐式的进行类类型转换，少写一些代码
// 缺点就是不直观，不利于阅读

// exercise_7_51
// 根据构造函数的目的决定是否将单参数构造函数设为explicit，是否要重点强调，重点区分，才决定要不要加上explicit

// exercise_7_52
struct Sales_Item
{
    string _isbn;
    unsigned _units_sold = 0;
    double _revenue = 0;
};

void exercise_7_52()
{
    Sales_Item trans{"978-0590353403", 25, 15.99};
    cout << trans._isbn << endl
         << trans._units_sold << endl
         << trans._revenue << endl;
    // 尽管g++ compiler没有报错，但是aggregate class 不应该有类内初始值
}

// exercise_7_55
// Data是聚合类，所以也是一个字面值常量类

// exercise_7_56
// 类的静态成员是指在类中声明为static的成员，它只与类相关联，不与具体的对象相关联，被所有的对象所共有
// 具体的对象中只包含普通的数据成员，不包含静态成员，而且静态成员需要单独定义，他的生命周期是与整个程序同步的
// 而且静态成员可以作为默认实参，静态成员类型可以是不完全类型，这些普通成员都无法做到
// 静态成员函数中不包含this指针，因此只能访问静态数据成员，无法访问普通的数据成员

void exercise_7_58()
{
    cout << Example::rate << " " << Example::vecSize
         << " " << "vec's size is " << Example::vec.size() << endl;
}

int main()
{
    // exercise_7_1_record();
    // exercise_7_11();
    // exercise_7_27();
    // exercise_7_38();
    // exercise_7_43();
    // exercise_7_52();
    exercise_7_58();

    return 0;
}