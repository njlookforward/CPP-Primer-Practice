#ifndef QUERYRESULT_HPP
#define QUERYRESULT_HPP

#include <iostream>
#include <string>
#include <memory>
#include <set>
#include <vector>

class QueryResult {
    friend std::ostream &operator<<(std::ostream &os, const QueryResult &qr);

public:
    using line_no = std::vector<std::string>::size_type;

    QueryResult(const std::string &, std::shared_ptr<std::set<line_no>>, 
                std::shared_ptr<std::vector<std::string>>);
    QueryResult(const QueryResult &) = default;
    QueryResult &operator=(const QueryResult &) = default;
    ~QueryResult() = default;

    // 接下来的这些函数是操作某些数据成员
    std::set<line_no>::const_iterator begin() const;
    std::set<line_no>::const_iterator end() const;
    
    std::shared_ptr<std::vector<std::string>> get_file() const {  return _ptext;  }

private:
    std::string _word;
    std::shared_ptr<std::set<line_no>> _pset;
    std::shared_ptr<std::vector<std::string>> _ptext;
};

std::ostream &operator<<(std::ostream &os, const QueryResult &qr);

inline std::string make_plural(size_t cnt, std::string word)
{
    if(cnt > 1)
        return word + "s";
    else
        return word;
}

#endif