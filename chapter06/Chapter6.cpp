#include "Chapter6.hpp"

int factorial(int val)
{
    if(val != 0)
        return factorial(val - 1) * val;
    else
        return 1;
}

void count_calls(int val)
{
    static int num_static = 0;
    int num_local = 24;
    cout << endl
         << "parameter = "     << val          << endl
         << "local object = "  << ++num_local  << endl
         << "static object = " << num_static++ << endl;
}

void reset(int *pi)
{
    *pi = 0;
    pi = 0;
}

void reset(int &ri)
{
    ri = 0;
}

void Swap(int *lhs, int *rhs)
{
    // 任何时候只要使用指针都要验证指针的有效性
    if(!lhs || !rhs || lhs == rhs || *lhs == *rhs)
        return;
    int tmp = *lhs;
    *lhs = *rhs;
    *rhs = tmp;
}

void Swap(int &lhs, int &rhs)
{
    int tmp = lhs;
    lhs = rhs;
    rhs = tmp;
}

string::size_type find_char(const string &str, char ch, int &occurs)
{
    // 很巧妙的构思
    auto ret = str.size();
    occurs = 0;
    for(decltype(ret) index = 0; index != str.size(); ++index)
    {
        if(str[index] == ch)
        {
            if (ret == str.size())
            {
                ret = index;    // 第一次出现的位置
            }
            ++occurs;   // 出现的总次数
        }
    }
    return ret;
}

bool is_sentence(const string &str)
{
    int cnt = 0;
    return find_char(str, '.', cnt) == str.size() - 1 && cnt == 1;
}

bool checkUpper(const string &str)
{
    for (auto &&ch : str)
    {
        if(isupper(ch))
            return true;
    }
    
    return false;
}

void convertLower(string &str)
{
    for (auto &ch : str)
    {
        if(isupper(ch))
            ch = tolower(ch);   // don't forget
    }
}

void print(const char *str)
{
    // 有守卫标记
    if(str) // don't forget judge null pointer
        while (*str)
        {
            cout << *str++;
        }
    cout << endl;
}

void print(const int *beg, const int *end)
{
    while(beg != end)
        cout << *beg++ << " ";
    cout << endl;
}

void print(const int *arr, int size)
{
#ifndef NDEBUG  // 用于软件产品未发布时进行调试，正式发布产品时可以定义NDEBUG使调试部分失效
    cerr << __func__ << ": array's size is " << size << endl;
#endif

    for(int index = 0; index < size; ++index)
        cout << arr[index] << " ";
    cout << endl;
}

void print(int (&arr)[8])
{
    for (auto elem : arr)
    {
        cout << elem << " ";
    }
    cout << endl;
}

void print(int (*matrix)[4], int rowSize)
{
    for(int index = 0; index < rowSize; ++index)
    {
        for (auto &&elem : *(matrix + index))
        {
            cout << elem << " ";
        }
        cout << endl;
    }
}

int Bigger(int lhs, const int *rhs)
{
    return lhs > *rhs ? lhs : *rhs;
}

void SwapPointer(int *&lhs, int *&rhs)
{
    if(lhs && rhs)
    {
        int *tmp = lhs;
        lhs = rhs;
        rhs = tmp;
    }
    else
        cerr << "passed parameter has null pointer" << endl;
}

void error_msg(initializer_list<string> ls)
{
    for(auto beg = ls.begin(); beg != ls.end(); ++beg)
        cout << *beg << " ";
    cout << endl << endl;
    for (const auto &i : ls)
    {
        cout << i << " ";
    }
    cout << endl;
}

int sumOfList(initializer_list<int> li)
{
    int sum = 0;
    // for(size_t index = 0; index < li.size(); ++index)   // initializer_list has't operator[], so must use iterator
    for(auto beg = li.begin(); beg != li.end(); ++beg)
        sum += *beg;
    
    return sum;
}

bool str_subrange(const string &str1, const string &str2)
{
    if(str1.size() == str2.size())
        return str1 == str2;
    auto size = str1.size() < str2.size() ? str1.size()
                                          : str2.size();
    for(decltype(size) i = 0; i < size; ++i)
        if(str1[i] != str2[i])
            return false;
    
    return true;
}

const string &shorterString(const string &s1, const string &s2)
{
    return s1.size() < s2.size() ? s1 : s2;
}

string &shorterString(string &s1, string &s2)
{
    auto &r = shorterString(const_cast<const string &>(s1),
                            const_cast<const string &>(s2));
    return const_cast<string &>(r);
}

char &get_val(string &s1, string::size_type index)
{
    if(index < s1.size() && index >= 0)
        return s1[index];
    else
        exit(0);
}

vector<string> process()
{
    string expected,
           actual   = "nanjiang";
    if(expected.empty())
        return {};  // 空列表
    else if (expected == actual)
    {
        return {"functionalX", "Okay"};
    }
    else
        return {"functionalX", expected, actual};
}

void recursivePrint_shun(vector<int>::const_iterator beg, vector<int>::const_iterator end)
{
    if(beg != end)
    {
        cout << *beg << " ";
        recursivePrint_shun(beg+1, end);
    }
    else
        cout << endl;
}

void recursivePrint_ni(vector<int>::const_iterator beg, vector<int>::const_iterator end)
{
    if(beg != end)
    {
        recursivePrint_ni(beg+1, end);
        cout << *beg << " ";
    }
}

void recur_ndebug_print(vector<int>::const_iterator beg, vector<int>::const_iterator end)
{
    if(beg != end)
    {
        cout << *beg << " ";
    #ifndef NDEBUG
        cout << "vector<int> has " << end - beg << " elements." << endl;
    #endif  //NDEBUG
        recur_ndebug_print(beg+1, end);
    }
}

// const string &manip()
// {
//     // 不要返回函数内局部对象的引用或者指针，因为函数返回后函数栈被释放了，同时释放内部的所有数据，因此找不到了
//     string ret = "error";
//     if(!ret.empty())
//         return ret;
//     else
//         return "Empty"; // 同样不能返回局部临时变量，即使返回值是const string &
//     // 虽然是warning，但是在运行时出现segment fault.段错误
// }

sz ht = 24, wd = 80;
char def = '&';

string make_plural(size_t ctr, const string &word, const string &ending)
{
    return ctr > 1 ? word + ending
                   : word;
}

void f()
{
    cout << "f()" << endl;
}

void f(int)
{
    cout << "f(int)" << endl;
}

void f(int, int)
{
    cout << "f(int, int)" << endl;
}

void f(double, double)
{
    cout << "f(double, double = 3.14)" << endl;
}

int exer54(int, int)
{
    return 54;
}

int Add(int v1, int v2)
{
    return v1 + v2;
}

int Minus(int v1, int v2)
{
    return v1 - v2;
}

int Mutiply(int v1, int v2)
{
    return v1 * v2;
}

int Divide(int v1, int v2)
{
    return v1 / v2;
}
