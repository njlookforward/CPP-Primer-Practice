#ifndef TEXTQUERY_HPP
#define TEXTQUERY_HPP

/* 文本查询程序：读入文本，保存在TextQuery类中，TextQuery提供构造函数和查询函数
 * 查询函数返回的是QueryResult类，保存查到的结果，由于需要共享文本和所在行数的集合，因此采用shared_ptr
 */
// 来吧，来一次全面的大换血，不要害怕，不要怕麻烦，面向对象的好处就是看着代码很多，但是设计模式是
// 接口与实现相分离，因此是很好改的，只需要保持脑袋清醒，根据主要逻辑，需要什么就添加一个接口和对应实现就可以了

#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
// #include <vector>
// #include <string>
#include <map>
#include <set>
#include "strBlob.hpp"
#include "QueryResult.hpp"

class TextQuery {
public:
    using line_no = size_t;
    explicit TextQuery(std::ifstream &inputfile);   // 必须进行显示构造，不能出现隐式类型转换
    TextQuery(const TextQuery &) = default;
    TextQuery &operator=(const TextQuery &) = default;
    ~TextQuery() = default;

    QueryResult query(const String &word) const;
    void display_map() const;

private:
    // std::shared_ptr<std::vector<String>> _ptext;   // save text according on line
    // exercise_12_32
    strBlob _ptext; // save text's content
    std::map<String, std::shared_ptr<std::set<line_no>>> _wordMap;   // save the word and occurrence's relationship

    static String cleanup_str(const String &word);    // 工具函数，作为成员函数的功能实现接口    
};


#endif

// 哪怕只有一秒钟，一分钟，一小时也是一种重大胜利，不要在乎时长，不要磨洋工，认认真真过好当下的每一秒钟
// 一道题一道题的练，一个字一个字地看，一行行地看，一步一步地走，走得坚实而有力量，拿出你的激情
// 很多东西没见过，多见多练就好了，不要怕，拿出就做出一堆狗屎的心态行动就好了
// 读出声来，大声地说出自己的思路，爷就是自信，有耐心，不着急，不要掉进时间的陷阱里
// 不想干的时候，划线粗读就行了，或者一道一道地练代码，丢掉所有包袱，享受当下