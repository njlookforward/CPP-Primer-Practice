#ifndef EXERCISE_HPP
#define EXERCISE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <stdexcept>
#include <string>
#include <vector>
#include <tuple>
#include <memory>
#include <algorithm>
#include <numeric>
#include <bitset>
#include <regex>
#include "Sales_data.hpp"

inline void checkArgs(int argc, int req)
{
    if(argc != req)
        throw std::runtime_error("checkArgs(int,int): input arguments' number is not enough");
}

inline int openInputFile(std::ifstream &infile, const std::string &dir)
{
    infile.open(dir);
    if(!infile)
    {
        std::cerr << "Sorry, cannot open " << dir << std::endl;
        return EXIT_FAILURE;    // 这是预处理量，不需要使用std
    }
    else
        return EXIT_SUCCESS;
}

/***********很重要的一个练习的函数集，在函数中使用tuple一次性返回多个值**************/
using matches = std::tuple<std::vector<std::vector<Sales_data>>::size_type,
                           std::vector<Sales_data>::iterator,
                           std::vector<Sales_data>::iterator>;  // 需要进行排序，不能是const_iterator
using matchSet_ptr = std::shared_ptr<std::vector<matches>>;

// 创建书店集合
void initBookStoreSet(std::vector<std::vector<Sales_data>> &bookstores,
                      std::ifstream &infile);   // 可能会有多个文件进行导入，因此一次只处理一个
// 在书店集合中寻找指定书籍的出现
// 这道题的目的就是练习tuple的一个重要作用就是一次性从函数中返回多个值
matchSet_ptr findBook(std::vector<std::vector<Sales_data>> &bookstoreSet,
                      const std::string &book); // 需要进行排序，不能const
// 打印匹配的数据
void reportResults(std::istream &is, std::ostream &os,
                   std::vector<std::vector<Sales_data>> &files);

// exercise_17_5
typedef std::vector<std::vector<Sales_data>>::size_type storeNo;
typedef std::vector<Sales_data>::iterator bookPos;
std::pair<storeNo, bookPos> findBook_v2(std::vector<std::vector<Sales_data>> &bookStores, 
                                                            const std::string &book);

// exercise_17_6
// 定义一个简单类来保存bookstores中的所有匹配数据
struct matchStore {
    matchStore(storeNo i, bookPos bg, bookPos ed): _index(i), _begin(bg), _end(ed) {}
    matchStore() = default;
    storeNo _index;
    bookPos _begin;
    bookPos _end;
};

typedef std::shared_ptr<std::vector<matchStore>> pmatchset;
pmatchset findBook_v3(std::vector<std::vector<Sales_data>> &bookstores, const std::string &book);

// exercise_17_11_12
// 包含10个真假问题的答案
struct TenBitsAnswer {
    TenBitsAnswer() = default;
    TenBitsAnswer(int a): _answer(a) {}
    bool getAnswer(int index) const;
    void setAnswer(int index, bool status);

    int _answer = 0;
};

inline bool TenBitsAnswer::getAnswer(int index) const
{
    return _answer & (1UL << index);
}

inline void TenBitsAnswer::setAnswer(int index, bool status)
{
        if(status)
            _answer |= (1UL << index);  // 不要傻了，还得改变状态呢
    else
        _answer &= ~(1UL << index);
}

struct HundredBitsAnswer
{
    HundredBitsAnswer() = default;
    HundredBitsAnswer(unsigned long long answer): _answer(answer) {}
    bool getAnswer(int index) const;
    void setAnswer(int index, bool status);
    
    std::bitset<101> _answer;
};

inline bool HundredBitsAnswer::getAnswer(int index) const
{
    return _answer[index];
}

inline void HundredBitsAnswer::setAnswer(int index, bool status)
{
    status ? (_answer[index] = 1) : (_answer[index] = 0);
}

bool phoneValid(const std::smatch &phone);

// exercise_17_21
struct peopleinfo {
    std::string _name;
    std::vector<std::string> _phones;
};

void AddressBook(std::vector<peopleinfo> &phones, std::ifstream &infile);
void printPhones(std::ostream &os, const std::vector<peopleinfo> &phones);

#endif