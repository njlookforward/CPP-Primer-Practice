#include "Quote.hpp"
#include "Base.hpp"
#include <vector>
#include <memory>
#include "Basket.hpp"
using namespace std;

void prog1_quote()
{
    Quote basic("0-201-70353-X", 10);
    Bulk_Quote bulk("0-201-88954-4", 20, 12, 0.2);
    Preference_Quote prefe("0-201-78345-X", 10, 13, 0.1);

    print_total(cout, basic, 20);
    print_total(cout, bulk, 10);
    print_total(cout, prefe, 20);
}

void prog2_check_dynamic_binding()
{
    Base b;
    Derived d1, d2;
    FriendClass fc(&b);
    fc.foo();
    fc.changePoint(&d1);
    fc.foo();

    d1.invokeStatMem(d2);
}

void prog3_virtual_fcn()
{
    Quote base("0-201-82470-1", 50);
    print_total(cout, base, 10);
    Bulk_Quote derived("0-201-82470-1", 50, 5, .19);
    print_total(cout, derived, 10);

    base = derived;
    cout << base.net_price(20) << endl;

    Quote *pb = &derived;
    cout << pb->net_price(42) << endl
         << pb->Quote::net_price(42) << endl;   // 通过使用作用域运算符来回避虚函数机制
}

void prog4_protected()
{
    Sneaky s("nanjiang", 25, 2);
    base1 b("tianjin", 17);

    clobber(s);
    clobber(b);

    Pub_Derv d1(54, 'n');
    Pri_Derv d2(53, 'j');
    d1.pub_mem();
    // d2.pub_mem();    // 私有继承
    Derived_from_Private dpri(25, 'n');
    Derived_from_Public dpub(32, 'n');
    cout << dpri.use_base() << endl;
    dpub.use_base();
    dpri.pub_mem();
}

void prog5_base_scope()
{
    // 在编译时期进行静态类型的名字检查
    Bulk_Quote bulk("0-201-82470-1", 50, 5, .19);
    Bulk_Quote *bulkP = &bulk;
    Quote *bp = &bulk;
    bulkP->discount_policy();

    Derived3 d(42);
    cout << d.get_mem() << endl
         << d.get_base_mem() << endl;

    base3 b;
    cout << b.memfcn() << endl
         << d.memfcn(25) << endl
        //  << d.memfcn() << endl
         << d.base3::memfcn() << endl;
}

void prog6_container_inheritance()
{
    // 当存放具有继承关系的对象时，容器中应该存放的是智能指针
    vector<shared_ptr<Quote>> basket;
    // 使用智能指针就像使用普通指针一样，也存在派生类向基类的类型转换
    basket.push_back(make_shared<Quote>("0-201-82470-1", 50));
    basket.push_back(
        make_shared<Bulk_Quote>("0-201-54848-8", 50, 10, .25)
    );
    basket.emplace_back(new Bulk_Quote("0-201-82470-1", 50, 5, .19));
    cout << basket.back()->net_price(15) << endl;
}

void prog7_basket()
{
    Basket bsk;
    Quote basic("0-201-70353-X", 10);
    Bulk_Quote bulk("0-201-88954-4", 20, 12, 0.2);
    Preference_Quote prefe("0-201-78345-X", 10, 13, 0.1);
    for(int i = 0; i < 20; ++i)
    {
        bsk.insert(make_shared<Quote>("0-201-70353-X", 10));
        bsk.insert(make_shared<Bulk_Quote>("0-201-88954-4", 20, 12, 0.2));
        bsk.insert(make_shared<Preference_Quote>("0-201-78345-X", 10, 13, 0.1));

        bsk.add_item(basic);
        bsk.add_item(bulk);
        bsk.add_item(prefe);
    }

    bsk.total_receipt(cout);
}

int main(int argc, char **argv)
{
    // prog1_quote();
    // prog2_check_dynamic_binding();
    // prog3_virtual_fcn();
    // prog4_protected();
    // prog5_base_scope();
    // prog6_container_inheritance();
    prog7_basket();

    return 0;
}

// 怕什么，有什么可怕的，大胆去尝试，失败了又怎么样，慢慢去修改不就好了