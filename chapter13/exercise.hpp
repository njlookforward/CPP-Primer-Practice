#ifndef EXERCISE_HPP
#define EXERCISE_HPP

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>

struct X {
    X()                 {   std::cout << "X()" << std::endl;            }
    X(const X &)        {   std::cout << "X(const X &)" << std::endl;   }
    X(X &&) noexcept    {   std::cout << "X(X &&)" << std::endl;        }

    X &operator=(const X &)      {   std::cout << "X &operator(const X &)" << std::endl; return *this;  }
    X &operator=(X &&) noexcept  {   std::cout << "X &operator(X &&)" << std::endl; return *this;       }

    ~X()    {   std::cout << "~X()" << std::endl;   }
};

// 检查实参传递是否调用copy constructor or move constructor
// 这次不能使用inline的形式，会出现很多意料之外的事情
void fcn1_copy(X x1);

X fcn2_right_val();

X &fcn3_left_val(X &x1);

// exercise_13_17
struct numbered {
    numbered();
    numbered(const numbered &rhs);

    size_t mysn;
};

// inline void fcn_print_num(numbered s)
// {
//     std::cout << s.mysn << std::endl;
// }

inline void fcn_print_num(const numbered &s)
{
    std::cout << s.mysn << std::endl;
}

struct NoCopy
{
    NoCopy() = default;
    NoCopy(const NoCopy &) = delete;            // 阻止拷贝
    NoCopy &operator=(const NoCopy &) = delete; // 阻止赋值
    ~NoCopy() = default;
};

struct NoDtor
{
    NoDtor() = default;
    ~NoDtor() = delete;
    // 析构函数被删除的自定义类类型，不能新建对象，只能动态分配对象，但是不能释放
};

// 私有拷贝控制，将拷贝控制函数声明为私有，用户代码不能拷贝这个类型的对象，为了让成员函数和友元函数同样不同拷贝
// 只声明，不定义
class PrivateCopy {
    PrivateCopy(const PrivateCopy &);               // 阻止拷贝
    PrivateCopy &operator=(const PrivateCopy &);    // 阻止赋值

public:
    PrivateCopy() = default;
    ~PrivateCopy() {}
};

// exercise_13_18_19
class Employee {
public:
    Employee():_number(++_cnt) {}
    Employee(const std::string &name):_name(name), _number(++_cnt) {}
    // 我认为一个雇员只能有唯一的名字和对应的唯一的员工编号，没有分身，所以不能使用拷贝初始化
    Employee(const Employee &) = delete;
    // 一旦某些职位出现人员调整，直接使用合成拷贝赋值运算符函数即可
    Employee &operator=(const Employee &) = default;
    ~Employee() = default;

    std::string &name() {   return _name;   }
    size_t number()     {   return _number; }

private:
    std::string _name;
    size_t      _number;

    static size_t _cnt;
};

// exercise_13_28 define a binaryTree, treenode's content is string
// class BinStrTree;
// class TreeNode {
//     friend class BinStrTree;
// public:
//     TreeNode():_val(), _cnt(0), _lchild(nullptr), _rchild(nullptr) {}
//     TreeNode(const std::string &val):_val(val), _cnt(1), _lchild(nullptr), _rchild(nullptr) {}
//     // TreeNode的拷贝构造函数，没有设计过，也没有这个需求啊
//     // 因为二叉树是类指针拷贝，因此不需要定义拷贝构造函数和拷贝赋值运算符
//     ~TreeNode() {   destroy();  }

//     void addNode(const std::string &val);
//     void destroy(); // 释放子树结点所占资源
//     void inorder();

// private:
//     std::string _val;   // 节点内容
//     std::size_t _cnt;   // 添加次数
//     TreeNode *_lchild;  // 左孩子节点
//     TreeNode *_rchild;  // 右孩子节点
// };

// 我懂得这道题应该如何思考了，如果二叉树的拷贝是类指针语义，树节点是不需要进行拷贝的
// 如果二叉树是类值拷贝，那么需要树节点也要进行类值拷贝
// 先搞定脑子里面清晰的东西，对于二叉树，采用类指针拷贝语义，当引用计数为0时才会销毁各个节点
// 这就是工程师思维，先从自己清楚的地方入手，做着做着自己就更清晰了，甚至是推倒重来
// 类指针拷贝设计
// class BinStrTree {
// public:
//     BinStrTree():_root(nullptr), _use(new std::size_t(1)) {}
//     BinStrTree(const BinStrTree &rhs): _root(rhs._root), _use(rhs._use)
//     {   ascendCnt(rhs); }

//     BinStrTree &operator=(const BinStrTree &rhs);

//     ~BinStrTree() { descendCnt();   }

//     void insert(const std::string &val);
//     void clear(); // 从根节点开始将整棵树所有节点释放
//     void inorderTraversal();

// private:
//     void ascendCnt(const BinStrTree &bt) {  ++*bt._use; }
//     void descendCnt();

//     TreeNode *_root;    // 二叉树的根节点
//     std::size_t *_use;  // reference count
// };

inline void checkargc(int argc, int threshold)
{
    if(argc < threshold)
        throw std::runtime_error("input parameters isn't enough.");
}

inline void openinfile(std::ifstream &ifs, const std::string &dir)
{
    ifs.open(dir);
    if(!ifs)
    {
        std::cerr << "Sorry, can't open " << dir << std::endl;
        return;
    }
}

struct Y
{
    // 一个类没有定义任何版本的拷贝控制函数，而且所有的non-static数据成员都可以移动，编译器会合成移动操作
    int i;
    std::string s;
};

struct hasY
{
    Y mem;
};

class Foo {
public:
    // 右值或左值引用成员函数，与const一样& and && is the qualifier of this
    Foo &operator=(const Foo &) &;
    Foo someMem() const &;

    // 同样类似于const，可以利用& and &&进行函数重载
    Foo sorted() &&;        // 对可改变的右值排序
    Foo sorted() const &;   // 对任何类型的左值排序，不过排序的是副本,这里的任意类型包括左值，也包括右值

private:
    std::vector<int> _data;
};

inline Foo &Foo::operator=(const Foo &) &
{
    return *this;
}

inline Foo Foo::someMem() const &
{
    return Foo();
}

inline Foo Foo::sorted() &&
{
    std::cout << "sorted() &&" << std::endl;
    sort(_data.begin(), _data.end());
    return *this;
}

inline Foo Foo::sorted() const &
{
    std::cout << "sorted() const &" << std::endl;
    // 最初版本：
    Foo ret(*this);
    sort(ret._data.begin(), ret._data.end());
    return ret;

    // exercise_13_57 version
    // return Foo(*this).sorted();

    // exercise_13_56 version
    // Foo ret(*this);
    // return ret.sorted();
}

inline Foo &retFoo(Foo &rf) {   return rf;  }
inline Foo retVal()     {   return Foo();   }

#endif