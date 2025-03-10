#ifndef CHAPTER6_HPP
#define CHAPTER6_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <initializer_list>
#include <ctime>
#include <cstdlib>
#include <cctype>
#include <cassert>
#include <cstdio>
#include <cmath>

using namespace std;

int factorial(int val);             // calculate factorial
int exercise_6_5_absolute(int val); // calculate absolution
void count_calls(int val);          // check local static object

/*parameter pass: pass by value or pass by reference*/
void reset(int *pi);
void reset(int &ri);
void Swap(int *lhs, int *rhs);
void Swap(int &lhs, int &rhs);
inline bool isShorter(const string &str1, const string &str2)
{
    return str1.size() < str2.size();
}

// constexpr bool shorter(const string &s1, const string &s2)
// {
//     return s1.size() < s2.size();
// }
// 使用引用形参返回额外的信息，意思是可以利用引用形参返回多个值
string::size_type find_char(const string &str, char ch, int &occurs);

/*const parameter and const argument*/
bool is_sentence(const string &str);
bool checkUpper(const string &str);
void convertLower(string &str);

// exercise_6_18
class Matrix;
bool compare(const Matrix &lhs, const Matrix &rhs);
vector<int>::iterator change_val(int, vector<int>::iterator);

// array parameter must specify array's begin and end range
void print(const char *str);    // 使用标记指定数组长度
void print(const int *beg, const int *end); // 使用标准库函数确定数组起始元素和尾后元素的位置
void print(const int *arr, int size);   // 数组起始位置和数组大小
void print(int (&arr)[8]);  // 直接传递明确大小的数组
void print(int (*matrix)[4], int rowSize);  // Multiply array

int Bigger(int lhs, const int *rhs);
void SwapPointer(int *&lhs, int *&rhs); // change pointer parameter, need reference to pointer

// pass mutable number parameters
void error_msg(initializer_list<string> ls);
int sumOfList(initializer_list<int> li);

// return expression
bool str_subrange(const string &str1, const string &str2);
// const string &manip();

// const_cast and overload
const string &shorterString(const string &s1, const string &s2);
string &shorterString(string &s1, string &s2);

char &get_val(string &s1, string::size_type index); // 返回值可以是左值
vector<string> process();
void recursivePrint_shun(vector<int>::const_iterator beg, vector<int>::const_iterator end);
void recursivePrint_ni(vector<int>::const_iterator beg, vector<int>::const_iterator end);
void recur_ndebug_print(vector<int>::const_iterator beg, vector<int>::const_iterator end);

// return pointer to array
int (*func(int i)) [10]; // 返回类型是指向含有10个整数的数组指针
auto func1(int i) -> int (*) [10]; // 使用尾置返回类型
// int odd[]  = {1, 3, 5, 7, 9};
// int even[] = {0, 2, 4, 6, 8};
// // 使用decltype设置数组类型
// inline decltype(odd) *arrPtr(int i)
// {
//     return i % 2 ? &odd : &even;
// }

// inline decltype(odd) &arrPtr1(int i)
// {
//     return i % 2 ? odd : even;
// }

// exercise_6_36
string (&arrRef(int i)) [10];

typedef string sarrTen[10];
using sarrTen = string[10];
sarrTen &arrRef1(int i);

auto arrRef2(int i) -> string (&) [10];

// string sarr[10] = {};
// decltype(sarr) &arrRef3(int i);
// exercise_6_37: 我认为使用尾置返回类型的形式最好，因为更加清晰，不易出错

// now coming to 6.4 function overload and scope
// string read();
// void print(const string &);
// void print(double);
// inline void fooBar(int ival)
// {
//     bool read = false;  // 声明在局部作用域中的名字会隐藏外层作用域中的同名实体
//     string str = read();    // error
//     void print(int);
//     print("nanjiang");
//     print(ival);
//     print(3.14);
// }

// special language character default argument constexpr function preprocessor
typedef string::size_type sz;
extern sz ht, wd;
extern char def;
inline string screen(sz height = ht, sz widen = wd, char backgrnd = def)
{
    ostringstream oss;
    oss << "(" << height << ", " << widen << ", " << backgrnd << ")";
    string ret = oss.str();
    return ret;
}

string pingmu(sz, sz, char backgrnd = ' ');
// string pingmu(sz, sz, char backgrnd = '#');
string pingmu(sz = 24, sz = 80, char);  // 添加默认实参

string make_plural(size_t ctr, const string &word,
                               const string &ending = "s");

// inline function and constexpr function usually is being defined in the header file
constexpr int new_sz() {    return 42;  }
constexpr size_t scale(size_t cnt) {    return new_sz() * cnt;  }   // 当传入的是常量表达式时返回常量表达式，当传入非常量时返回的是非常量

// 对调试有帮助的预处理变量
// exercise_6_51
void f();
void f(int);
void f(int, int);
void f(double, double = 3.14);

// exercise_6_54
int exer54(int, int);
int Add(int v1, int v2);
int Minus(int v1, int v2);
int Mutiply(int v1, int v2);
int Divide(int v1, int v2);

#endif  // CHAPTER6_H