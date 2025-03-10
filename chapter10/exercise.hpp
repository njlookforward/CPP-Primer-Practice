#ifndef EXERCISE_HPP
#define EXERCISE_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <cstring>
#include "Sales_data.hpp"

using namespace std;

// 打印序列中的每个元素
template<typename Container>
void print(const Container &c)
{
    for (auto &&i : c)
    {
        cout << i << " ";
    }
    cout << endl;
}

// 重载打印序列函数
template <typename Iterator>
void print(Iterator first, Iterator last)
{
    while (first != last)
    {
        cout << *first++ << " ";
    }
    cout << endl;
}

// 消除重复单词
void elimDups(vector<string> &words);
// 按照单词长度进行排序
inline bool isShorter(const string &s1, const string &s2)
{
    return s1.size() < s2.size();
}

// exercise_10_12
inline bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs)
{
    return lhs.isbn() < rhs.isbn();
}

inline bool isMoreThresholdLeng(const string &str, unsigned len)
{
    return str.size() >= len;
}

inline bool isLessThresholdLeng(const string &str, unsigned len)
{
    return str.size() < len;
}

inline string make_plural(int count, const string &word, const string &suffix)
{
    if(count > 1)
        return word + suffix;
    else
        return word;
}

// exercise_10_16
void biggies(vector<string> &words, string::size_type sz,
             ostream &os = cout, char delim = ' ');

// exercise_14_40
class SizeComp {
public:
    SizeComp(std::size_t sz): _threshold(sz) {}
    bool operator() (const std::string &word) const
    {
        return word.size() >= _threshold;
    }

private:
    std::size_t _threshold;
};



inline void display(ostream &os, const string &str, char c)
{
    os << str << c;
}

template <typename Container>
void Input(istream &is, Container &con) // 一定要用心啊，别总是马虎
{
    typename Container::value_type elem;
    while (is >> elem)
    {
        con.insert(con.end(), elem);
    }
}

template <typename Container>
void randInitCon(Container &con, unsigned cnt)
{
    // 默认元素是int
    srand(static_cast<unsigned>(time(NULL)));
    while (cnt)
    {
        con.insert(con.end(), rand() % 50);
        --cnt;
    }
}

void elimDups(list<string> &slst);

#endif