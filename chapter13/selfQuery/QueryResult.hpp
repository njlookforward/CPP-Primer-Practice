#ifndef QUERYRESULT_HPP
#define QUERYRESULT_HPP

#include <iostream>
#include <string>
#include <memory>
#include <set>
#include "strBlob.hpp"

class QueryResult {
    friend std::ostream &operator<<(std::ostream &os, const QueryResult &qr);

public:
    using line_no = size_t;

    QueryResult(const String &, std::shared_ptr<std::set<line_no>>, strBlob);
    QueryResult(const QueryResult &) = default;
    QueryResult &operator=(const QueryResult &) = default;
    ~QueryResult() = default;

    // 接下来的这些函数是操作某些数据成员
    std::set<line_no>::const_iterator begin() const;
    std::set<line_no>::const_iterator end() const;
    
    strBlob get_file() const {  return _ptext;  }

private:
    String _word;
    std::shared_ptr<std::set<line_no>> _pset;
    strBlob _ptext;
};

std::ostream &operator<<(std::ostream &os, const QueryResult &qr);

inline String make_plural(size_t cnt, String word)
{
    if(cnt > 1)
        return word + "s";
    else
        return word;
}

#endif