#ifndef EXERCISE_HPP
#define EXERCISE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <deque>
#include <string>
#include <forward_list>
#include <map>
#include <iterator>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <queue>
#include <stdexcept>

using namespace std;

// exercise_9_4
bool find_v1(vector<int>::const_iterator first, vector<int>::const_iterator last, int aim);
// exercise_9_5
auto find_v2(vector<int>::const_iterator first, vector<int>::const_iterator last, int aim) -> vector<int>::const_iterator;

// exercise_9_15
inline
bool isEqual(const vector<int> &ivec1, const vector<int> &ivec2)
{
    return ivec1 == ivec2;
}

// exercise_9_16 --> generic algorithm request using iterator, but this question use specific container
bool isEqual(const list<int> &ilst, const vector<int> &ivec);

inline void pluralize(size_t cnt, string &word)
{
    if(cnt > 1)
        word.push_back('s');
}

// exercise_9_28
forward_list<string>::iterator Insert(forward_list<string> &sfLst, const string &posElem,
                                      const string &newElem);

// exercise_9_41
string Initstr(const vector<char> &cvec);

// exercise_9_43
void ModifyStr(string &str, const string &oldVal, const string &newVal);
void ModifyStrAns(string &str, const string &oldVal, const string &newVal);
// exercise_9_44
void ModifyStr_v2(string &str, const string &oldVal, const string &newVal);
// exercise_9_45
void ModifyStr_v3(string &name, const string &pre, const string &post);
// exercise_9_46
void ModifyStr_v4(string &name, const string &pre, const string &post);
// exercise_9_47
void find_num_alpha(const string &str);
void find_num_alpha_v2(const string &str);
// exercise_9_49
bool exclude_ascender_descender(const string &word);
// exercise_9_50
int calculateStr(const vector<string> &svec);
double calStr_v2(const vector<string> &svec);

// exercise_9_51
class Date {
    friend ostream &operator<<(ostream &os, const Date &date);

public:
    Date() = default;
    Date(const string &date);

private:
    unsigned _year = 2024;
    unsigned _month = 12;
    unsigned _day = 11;
};

extern map<string, unsigned> monthmap;

ostream &operator<<(ostream &os, const Date &date);

// exercise_9_52
// 需要定义一个类作为栈中的元素，保存表达式的一个操作对象
// 因为枚举是一种自定义类，因此可以直接在头文件中定义，而不会重定义
enum obj_type{LP, RP, ADD, SUB, VAL};
struct  obj
{
    obj(obj_type ot, double val = 0):_t(ot), _v(val) {}
    obj_type _t;
    double   _v;
};

void calNewVal(stack<obj> &so, double val);
double expresolution(const string &expr);
inline void skipws(const string &expr, string::size_type &pos)
{
    if(pos != expr.size())  // 必须确定好边界，有效
        pos = expr.find_first_not_of(" ", pos); // 跳过表达式中没有用处的空白字符
    // 这里出问题了，一旦到达表达式的末尾，没有找到就会返回npos
}

#endif  // EXERCISE_HPP