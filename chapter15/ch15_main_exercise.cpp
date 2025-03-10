#include "Quote.hpp"
#include "Base.hpp"
using namespace std;

// exercise_15_1
// 虚函数机制目的是动态绑定。在基类中定义为虚函数，在派生类中可以重新定义进行覆盖，当使用基类指针或引用调用这个虚函数时，
// 调用哪个版本取决于指针或引用所绑定的是基类对象还是派生类对象
// answer: 在类中被定义为virtual的成员，基类希望虚成员在派生类中能够被重定义；除了构造函数之外，任意非static成员
// 都能够被定义为虚成员

// exercise_15_2
// protected访问权限的成员能够被派生类的成员访问，但是不能被类的用户访问
// private访问权限的成员更加严格，只能被本类的成员访问，不能被类的用户或者派生类的成员访问。
// answer: protected是受保护的访问符号，protected成员能够被基类的成员，友元和派生类的成员访问，但是不能被基类的
// 普通用户访问，private成员只能被基类的成员和友元访问，不能被派生类的成员访问。

// exercise_15_3
// class Quote and print_total in the Quote.hpp

// exercise_15_4
// (a) wrong: 一个类不能派生它本身
// (c) wrong: 类的声明只包括class + qualifier, 不能有类派生列表。一个类的声明不可以包含派生列表

// exercise_15_5 in the Quote.hpp
// exercise_15_6 is prog1_quote()
// exercise_15_7 in the Quote.hpp

// exercise_15_8
// 静态类型是定义一个对象时所显示声明的类型，一般来说，非引用和非指针对象的静态类型与动态类型一致
// 只有类类型的指针或引用静态类型可能与动态类型不一致，其动态类型是指针所指向或引用所绑定的对象的实际类型
// 静态类型是编译时所确定的，动态类型是运行时所确定的。
// 书上的原文：静态类型是在编译期已知的，是变量声明时的类型或表达式生成的类型
// 动态类型是变量或表达式在内存中保存的对象的类型，到运行时才可知。基类的指针或引用的动态类型可能与静态类型不一致

// exercise_15_9
// 当基类指针或基类引用绑定派生类对象时，会发生静态类型与动态类型不一致
// Quote basic; Bulk_Quote bulk; Preference_Quote prefer;
// Quote *pb = &bulk;
// pb = &prefer;
// Quote &rb = bulk;
// Quote &rb2 = prefer;

// exercise_15_10
// 因为ifstream是istream的派生类，因此将ifstream对象传递给istream &,会发生派生类向基类的类型转换
// 在print函数中，引用对象的动态类型是ifstream，因此运行时是从输入文件流对象中向Sales_data对象输入数据
// 如果其中调用到虚函数，会使用ifstream版本的虚函数
// 在要求使用基类型对象的指针或引用的地方，可以使用派生类对象进行代替，这是一个静态类型与动态类型不一致的典型案例。

void exercise_15_11()
{
    Quote basic("0-201-70353-X", 10);
    Bulk_Quote bulk("0-201-88954-4", 20, 12, 0.2);
    Preference_Quote prefe("0-201-78345-X", 10, 13, 0.1);

    Quote *pb = &basic;
    pb->debug();
    cout << endl;
    pb = &bulk;
    pb->debug();
    pb = &prefe;
    pb->debug();
}

// exercise_15_12
// 需要强迫自己养成习惯，对于派生类中的虚函数应该在声明的末尾添加override，在定义中不需要添加
// 是有必要将一个成员函数同时声明为override和final的
// override: 在C++11新标准中，在派生类中重定义虚函数，通过在形参列表之后（包括const等限定符）添加override限定符
// 可以清晰明确地告诉编译器，在派生类中要覆盖基类中的同名虚函数；如果不添加override，在派生类中，为同名虚函数定义不同
// 的形参列表是合法的；但是添加override，编译器对这样的写法会报错
// final: 该限定词用来通知编译器这个虚函数不允许其派生类重定义覆盖它，否则会报错
// 通过同时定义override和final，可以更加清晰明确的向编译器表达我们的意图。


void exercise_15_13()
{
    base1 b("tianjin", 100);
    derived1 d("nanjiang", 25, 3);
    b.print(cout);
    d.print(cout);
    // 该代码存在问题，不过已经更改
}

// exercise_15_14
// base: (a) (c) (e) (d)
// 自己做错了，不过错的很好，pb2->name()，应该调用的是基类的name函数，因为name不是虚函数，是一个普通成员函数
// derived: (b)  (f)

// exercise_15_15_16 is Quote.hpp
// exercise_15_17
// 编译器给出的错误信息是由于类定义中有纯虚函数的声明，因此没法定义对应的对象
void exercise_15_17()
{
    // Disc_quote discer("0-201-82470-1", 50, 5, .19); // 抽象基类，没有办法定义对象
}

// exercise_15_18 考察可访问的派生类向基类类型的转换
// d1 is valid
// d2 is invalid because d2 is private inheritance
// d3 is invalid because d3 is protected inheritance
// dd1 is valid
// dd2 is invalid because indirect inheritance is private
// dd3 is invalid because indirect inheritance is protected

// exercise_15_19
// 对于 void memfcn(Base &b) {   b = *this; }   // 每个成员函数都有，因此是否合法
// Base: vaild
// Pub_Derv: valid
// Pri_Derv: valid
// Prot_Derv: valid
// Derived_from_Public: valid
// Derived_from_Protected: valid
// Derived_from_Private: invalid becasue Pri_Derv is private inheritance
// 首先，不管派生类以什么方式继承基类，派生类的成员和友元都可以使用派生类向基类的类型转换
// 其次，如果派生类是以公有或者受保护的形式继承基类，则派生类的派生类的成员和友元可以使用
// 该派生类向直接基类的类型转换，如果是私有继承，那么就无法使用

// exercise_15_20 is Base.hpp
void exercise_15_20()
{
    base2 b(25, 'n');
    Pub_Derv pub(25, 'n');
    Pri_Derv pri(25, 'n');
    Prot_Derv prot(25, 'n');
    Derived_from_Public dd1(25, 'n');
    Derived_from_Private dd2(25, 'n');
    Derived_from_Protected dd3(25, 'n');

    base2 *pb = &pub;
    // pb = &pri;  //
    // pb = &prot; //
    pb = &dd1;
    // pb = &dd2;  //
    // pb = &dd3;  //
}

// exercise_15_21_22 is Graphics.hpp

// exercise_15_23
// 这里需要明确这个“覆盖”的含义，覆盖的意思是在派生类中重定义基类中的虚函数，就是这个意思
// 因此需要将D1中的fcn函数改为 int fcn();
// p2->fcn(42)会报错，因为函数形参列表不匹配；

void exercise_15_23()
{
    base4 bobj;
    Derived4 d1obj;
    Derived5 d2obj;

    base4 *bp1 = &bobj, *bp2 = &d1obj, *bp3 = &d2obj;
    cout << bp1->fcn() << endl; // dynamic-binding  0
    cout << bp2->fcn() << endl; // dynamic-binding  0
    cout << bp3->fcn() << endl; // 1

    Derived4 *d1p = &d1obj;
    Derived5 *d2p = &d2obj;
    cout << d1p->fcn2() << endl;    // 25
    cout << d2p->fcn2() << endl;    // 50

    base4 *p1 = &d2obj;
    Derived4 *p2 = &d2obj;
    Derived5 *p3 = &d2obj;

    cout << p1->fcn()<< endl;       // 1
    cout << p2->fcn(42) << endl;    // 42
    cout << p3->fcn(84) << endl;    // 84
}

// exercise_15_24
// 继承体系中的基类需要定义虚析构函数，虚析构函数需要释放该类作用域内所申请的资源，如果没有，则使用默认操作
// 作为基类使用的类应该定义虚析构函数，目的是若一个基类指针指向动态分配的对象，删除指针时能够调用该对象的实际类型的
// 析构函数；虚析构函数的工作是当对象的生命周期结束时，能够正确删除数据成员，若该类中定义了指针类数据成员，能够
// 释放所申请的空间，保证内存安全。当然虚析构函数可以为空，使用合成的版本即可。

// exercise_15_25
// 如果我们没有定义Disc_Quote的默认构造函数，那么我们在定义Disc_quote的派生类的构造函数时必须显式地定义基类部分
// 而且必须调用Disc_Quote中定义的构造函数，不能跳过这一步。
// 而且由于Disc_quote没有默认构造函数，因此派生类也无法合成默认构造函数，必须显示定义。

// exercise_15_26_27 in the Quote.hpp
void exercise_15_26()
{
    Bulk_Quote bulk1, bulk2("0-201-82470-1", 50, 5, .19);
    Bulk_Quote bulk3(bulk2);
    bulk1 = bulk2;
    bulk2 = Bulk_Quote("0-201-82470-1", 50, 5, .19);
}

// exercise_15_28_29
// 如果要在容器中存放具有继承关系的元素，应该存放基类的智能指针而不是存放基类对象，因为如果存放基类对象
// 存入派生类对象时会被切片，元素类型必须定义为指针才能保存派生类对象。

// exercise_15_30 in the Basket.hpp

// exercise_15_31 is in the paper

// exercise_15_32
// Query的数据成员是shared_ptr<query_base>，因此Query的拷贝是智能指针的拷贝，类指针语义拷贝，引用计数加一
// Query的移动是智能指针的移动；Query的赋值是智能指针的赋值，旧的智能指针引用计数减一，若为0则释放所指向的query_base对象
// 等号右侧的智能指针的引用计数加一；Query的析构函数让智能指针的引用计数减一，若为0则释放所指向的query_base对象
// 会调用query_base的虚析构函数，根据query_base的动态类型调用实际的析构函数

// exercise_15_33
// 由于没有显式定义query_base的拷贝控制成员，因此使用都是合成拷贝控制成员；因为定义了虚析构函数，因此query_base
// 不会合成移动操作，因此query_base的拷贝、赋值、析构、默认构造函数都是编译器合成的，逐成员进行，没有特殊性，
// 由于是虚基类，不允许直接声明其对象，当其派生类对象进行这些操作时，会使用基类的默认合成版本，由于没有数据成员
// 其实什么也不做

// exercise_15_34
// (a) list all build_tree's all constructor: Query(const string &) -> WordQuery(const string &) ->
// Query(const string &) -> WordQuery(const string &) -> AndQuery(const Query &, const Query &) ->
// Query(shared_ptr<query_base>) -> Query(const string &) -> WOrdQuery(const string &) ->
// OrQuery(const QUery &, const Query &) -> Query(shared_ptr<query_base>)
// (b) cout << q所调用的rep: OrQuery::rep() -> AndQuery::rep() -> WordQuery::rep() -> WOrdQuery::rep()
// -> WOrdQuery::rep()
// (c) q.eval(): OrQuery::eval() -> AndQuery()::eval() -> WOrdQUery::eval() -> WordQuery::eval()
// -> WOrdQuery::eval()

// exercise_15_35_36 in the Query.hpp
// Debug的一个非常重要的方法就是打印语句print，进行定位

// exercise_15_37
// 如果派生类中的数据成员由Query替换成shared_ptr<Query_base>，那么就没有程序接口类了，只能使用程序实现类，那么
// 实现类需要承担接口类的义务，因此Query_base的eval函数和rep函数需要定义为Public,然后在
// NotQuery BinaryQuery OrQuery AndQuery中使用->eval来调用对应的接口函数
// 只要作为接口的类的函数定义为public即可，此时的接口类是query_base，派生类继续定义为private也没事，因为动态绑定
// 发生在运行期，不会进行类型检查。此时的接口类是Query_base，实现类是Query_base的派生类
// 在面向对象的世界中，一定要设计好谁是接口类，哪些是实现类，这样就方便设计了

// exercise_15_38
// BinaryQuery a = ... invalid because BinaeryQuery has pure virtual function, 不能被定义
// 做错了。这是不合法的，不存在Query向AndQuery的转换
// 做错了，这是不合法的，不存在Query向OrQuery的转换

// exercise_15_39 in the Query.hpp

// exercise_15_40
// 无论哪种情况，都不会发生错误。rhs为空集，则insert插入为空；lhs为空集，则make_shared创建的set为空
// 若两者都为空集，则set为空，返回的QueryResult中shared_ptr<set<line_no>>中的set为空

// exercise_15_41 .\pointquery\Query.hpp
// 这道题提醒我，要使用智能指针而不是普通指针，因为使用智能指针可以使用默认合成的拷贝控制成员
// 一旦使用普通指针，需要定义自己的拷贝控制成员，保证内存安全。要使用普通指针有两种方案，一种使用引用计数
// 实现类指针拷贝语义，一种是利用虚拷贝实现类值拷贝语义，以后尽量使用智能指针，真的会减少代码量与思考量

// exercise_15_42 .\pointquery\Query.hpp
// 最简单的改进当然是(c), 在eval中添加一个表示范围的数就行

int main(int argc, char **argv)
{
    // exercise_15_11();
    // exercise_15_13();
    // exercise_15_17();
    // exercise_15_20();
    // exercise_15_23();
    exercise_15_26();

    return 0;
}

// 不要管时间、行数。我只管一道题一道题地验证下去，不墨迹，不着急，不逃避，我要勇敢的面对，我是勇敢的人