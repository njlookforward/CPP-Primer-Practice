#ifndef BASE_HPP
#define BASE_HPP

#include <iostream>

// 验证动态绑定与访问权限检查无关
class FriendClass;
class Base {
    friend class FriendClass;

public:
    static void statmem() { std::cout << "Base::statmem()" << std::endl;    }

private:
    virtual void vfcn() const {
        std::cout << "Base::vfcn()" << std::endl;
    }
};

class Derived: public Base {
public:
    void invokeStatMem(const Derived &derObj) const;

private:
    void vfcn() const {
        std::cout << "Derived::vfcn()" << std::endl;
    }
};

class FriendClass {
public:
    FriendClass(Base *pb): _pb(pb) {}
    void foo() const {
        _pb->vfcn();
    }

    void changePoint(Base *nbp)
    {
        _pb = nbp;
    }

private:
    Base *_pb;
};

inline void Derived::invokeStatMem(const Derived &derObj) const
{
    Base::statmem();        // Base定义了局部静态成员函数
    Derived::statmem();     // Derived继承了statmem
    derObj.statmem();       // 利用派生类对象调用静态成员函数
    statmem();              // 使用this指针调用静态成员函数
}

// C++11中定义不能继承的类
class NoDerived final {};   // NoDerived不能作为基类
class Last final: public Base {
    void vfcn() const {}
};
// class BadClass: public NoDerived {};
// class BadTwoClass: public Last {};

// 说明override的重要性
struct B {
    virtual void f1(int) const {}
    virtual void f2() {}
    void f3() {}
};

struct D1: public B
{
    void f1(int) const override {}
    void f2() override {}    // error: 形参不一致
    void f3() {}       // error: f3 is not an virtual fcn
    void f4() {}       // error: B don't have vfcn f4
};

struct D2: B {
    void f1(int) const final {}
};

struct D3 : D2
{
    void f2() override {}   // right
    // void f1(int) const {}   // error, 不能再覆盖了
};

class Pal;
class base1 {
    friend class Pal;

public:
    base1(const std::string &str, int i): _basename(str), _prot_mem(i) {}
    virtual ~base1() = default;
    virtual void print(std::ostream &os) {  os << _basename;    }

private:
    std::string _basename;

protected:
    int _prot_mem = 0;
};

class derived1: public base1 {
public:
    derived1(const std::string &str, int i1, int i2): base1(str, i1), _i(i2) {}
    void print(std::ostream &os) override {  base1::print(os);   os << " " << _i; }
    // 代码已经修改完毕，必须指定调用基类的print，否则会爆栈。

private:
    int _i;
};

// 通过测试，说明派生类的成员或者友元只能通过派生类对象来访问基类中的受保护成员
class Sneaky: public base1 {
    friend void clobber(Sneaky &);
    friend void clobber(base1 &);

public:
    Sneaky(const std::string &str, int i1, int i2): base1(str, i1), _priv_mem(i2) {}

private:
    int _priv_mem = 0;
};

class Pal {
public:
    int f(base1 b) {    return b._prot_mem; }
    // int f2(Sneaky s) {  return s._priv_mem; }   // error, 不是派生类的友元
    int f3(Sneaky s) {  return s._prot_mem; }   // 仍然是Sneaky基类子对象的友元
    // 基类的访问权限由基类决定，即使是派生类的基类部分
};

// 说明友元不能继承
class D4: public Pal {
public:
    // int f(base1 b) {    return b._prot_mem; }
};

inline void clobber(Sneaky &s)
{
    std::cout << "Sneaky::prot_mem: " << s._prot_mem << std::endl;
}

inline void clobber(base1 &b)
{
    // std::cout << "base1::prot_mem: " << b._prot_mem << std::endl;
}

class base2 {
public:
    base2() = default;
    base2(int i, char ch): prot_mem(i), priv_mem(ch) {}
    virtual ~base2() = default;
    void pub_mem() const {  std::cout << "base1::pub_mem()" << std::endl;   }
    void test(base2 &b) {    b = *this;  } 

protected:
    int prot_mem = 25;

private:
    char priv_mem = 'x';
};

class Pub_Derv: public base2 {
public:
    Pub_Derv(int i, char ch): base2(i, ch) {}
    int f() {   pub_mem();  return prot_mem;    }
    // char g() {  return priv_mem;    }
    void test(base2 &b) {    b = *this;  } 
};

struct Pri_Derv: private base2 {
    Pri_Derv(int i, char ch): base2(i, ch) {}
    int f1() {  pub_mem();  return prot_mem;    }
    void test(base2 &b) {    b = *this;  } 

public:
    using base2::pub_mem;
protected:
    using base2::prot_mem;
};

struct Prot_Derv: protected base2 {
    Prot_Derv(int i, char ch): base2(i, ch) {}
    void test(base2 &b) {    b = *this;  } 
};

struct Derived_from_Public: public Pub_Derv {
    Derived_from_Public(int i, char ch): Pub_Derv(i, ch) {}
    int use_base() {    return prot_mem;    }
    void test(base2 &b) {    b = *this;  } 
};

struct Derived_from_Protected: public Prot_Derv
{
    Derived_from_Protected(int i, char ch): Prot_Derv(i, ch) {}
    void test(base2 &b) {    b = *this;  } 
};


struct Derived_from_Private: public Pri_Derv
{
    Derived_from_Private(int i, char ch): Pri_Derv(i, ch) {}
    int use_base() {    return prot_mem;    }   // error, because private inherit base2
    // void test(base2 &b) {    b = *this;  } 
};

struct base3 {
    base3(): _mem(0) {}
    int memfcn() const {    return 0;   }

protected:
    int _mem = 0;
};

struct Derived3: base3
{
    Derived3(int i): _mem(i) {}

    int get_mem() const {   return _mem;    }
    int get_base_mem() const {  return base3::_mem; }   // 使用作用于限定符来使用隐藏的成员
    int memfcn(int i) const {   return i;   }

protected:
    int _mem = 0;
};

struct base4 {
    virtual int fcn() const {   return 0;   }
};

struct Derived4: base4 {
    using base4::fcn;   // 使用using声明将基类的同名函数作为派生类的重载函数
    int fcn(int i) const {  return i;   }
    virtual int fcn2() const {  return 25;  }
};

struct Derived5: Derived4 {
    int fcn(int i) const {  return i;   }
    int fcn() const override {  return 1;  }
    int fcn2() const override { return 50;  }
};

#endif