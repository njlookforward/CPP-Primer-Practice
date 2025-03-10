#ifndef EXERCISE_HPP
#define EXERCISE_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include <cstring>

template <typename Container>
std::ostream &print(std::ostream &os, Container c)
{
    for (const auto &i : c)
    {
        os << i << " ";
    }
    
    return os;
}

// exercise_12_6
inline std::vector<int> *allocVec()
{
    auto ret = new std::vector<int>();
    return ret;
}

// exercise_12_7
inline std::shared_ptr<std::vector<int>> allocSmart()
{
    return std::make_shared<std::vector<int>>();
}

inline std::istream &readToVec(std::istream &is, std::shared_ptr<std::vector<int>> pv)  // 直接拷贝就可以，没必要使用引用，这就是使用shared_ptr的好处
{
    int tmp;
    while (is >> tmp)
    {
        pv->push_back(tmp);
    }
    return is;
}

inline std::istream &readToVec(std::istream &is, std::vector<int> *pv)
{
    int tmp;
    while (is >> tmp)
    {
        pv->push_back(tmp);
    }
    return is;
}

inline std::ostream &display(std::ostream &os, std::shared_ptr<std::vector<int>> pv)
{
    for (const auto &i : *pv)
    {
        os << i << " ";
    }
    return os;
    // 可以直接返回，而不要担心管理动态内存
}

inline std::ostream &display(std::ostream &os, std::vector<int> *pv)
{
    for (const auto &i : *pv)
    {
        os << i << " ";
    }

    // 既然都已经打印完数据了，就应该释放内存了，在第一次编写的时候就忘记释放了，说明使用普通指针来管理动态内存是存在很大问题的
    return os;
}

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

char *increTwice(char *, int &);

#endif