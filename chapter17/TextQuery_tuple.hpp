#ifndef TEXTQUERY_TUPLE_HPP
#define TEXTQUERY_TUPLE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <tuple>
#include <cctype>

class TextQuery {
public:
    using line_no = std::vector<std::string>::size_type;
    using ResultTuple = 
    std::tuple<std::string, std::shared_ptr<std::set<line_no>>, std::shared_ptr<std::vector<std::string>>>;
    explicit TextQuery(std::ifstream &inputfile);   // 必须进行显示构造，不能出现隐式类型转换
    TextQuery(const TextQuery &) = default;
    TextQuery &operator=(const TextQuery &) = default;
    ~TextQuery() = default;

    ResultTuple query(const std::string &word) const;
    void display_map() const;

private:
    std::shared_ptr<std::vector<std::string>> _ptext;   // save text according on line
    // exercise_12_32
    // strBlob _ptext; // save text's content
    std::map<std::string, std::shared_ptr<std::set<line_no>>> _wordMap;   // save the word and occurrence's relationship

    static std::string cleanup_str(const std::string &word);    // 工具函数，作为成员函数的功能实现接口    
};

std::ostream &operator<<(std::ostream &os, const TextQuery::ResultTuple &rhs);

inline std::string make_plural(size_t cnt, std::string word)
{
    if(cnt > 1)
        return word + "s";
    else
        return word;
}

#endif