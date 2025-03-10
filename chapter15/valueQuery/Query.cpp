#include "Query.hpp"
#include "exercise.hpp"
#include <algorithm>
#include <iterator>
using namespace std;

Query::Query(const std::string &word): _query(new WordQuery(word)) {}
// Bug10: 这是一个好Bug，WordQuery的构造函数是private, Query设置为WordQuery的友元类，因此Query可以定义WordQuery对象
// 包括new一个WordQuery对象，但是不能std::make_shared<WordQuery>(word)，因为make_shared不是WOrdQuery的友元函数

Query::Query(const Query &q): _query(q._query->clone()) {}
Query::Query(Query &&q): _query(q._query) {
    q._query = nullptr;
}

Query &Query::operator=(const Query &q)
{
    Query_base *tmp = q._query->clone();
    if(_query)
        delete _query;
    _query = tmp;

    return *this;
}

Query &Query::operator=(Query &&q)
{
    // 因为移动操作是移动资源，资源只有一份，没有复制出的两份，因此需要换一种判断方法
    if(this != &q)
    {
        if(_query)
            delete _query;
        _query = q._query;
        q._query = nullptr;
    }

    return *this;
}

QueryResult WordQuery::eval(const TextQuery &text, std::size_t lb, std::size_t rb) const 
{
    auto res = text.query(_word);

    auto ret_lines = make_shared<set<line_no>>();
    remove_copy_if(res.begin(), res.end(), inserter(*ret_lines, ret_lines->begin()),
                    Threshold(lb, rb));
    
    return QueryResult(_word, ret_lines, res.get_file());
}

Query operator~(const Query &qr)
{
    return new NotQuery(qr);
}

Query operator~(Query &&qr)
{
    return new NotQuery(std::move(qr));
}

QueryResult NotQuery::eval(const TextQuery &text, std::size_t lb, std::size_t rb) const
{
    // 取反查询操作
    auto result = _query.eval(text, 0, text.get_file()->size());
    auto ret_lines = make_shared<set<line_no>>();

    auto bgit = result.begin(),
         edit = result.end();
    // auto sz = result.get_file()->size();

    for(line_no n = lb; n <= rb; ++n)
    {
        if(bgit == edit || *bgit != n)
            ret_lines->insert(n);
        else if(bgit != edit)
            ++bgit;
    }

    return QueryResult(rep(), ret_lines, result.get_file());
}

Query operator|(const Query &lhs, const Query &rhs)
{
    return new OrQuery(lhs, rhs);
}

Query operator|(Query &&lhs, Query &&rhs)
{
    return new OrQuery(std::move(lhs), std::move(rhs));
}

QueryResult OrQuery::eval(const TextQuery &text, std::size_t lb, std::size_t rb) const
{
    auto lhsRes = _left.eval(text, lb, rb),
         rhsRes = _right.eval(text, lb, rb);
    
    auto ret_lines = make_shared<set<line_no>>(lhsRes.begin(), lhsRes.end());
    ret_lines->insert(rhsRes.begin(), rhsRes.end());

    // auto elimit = remove_if(ret_lines->begin(), ret_lines->end(),
    //                         Threshold(lb, rb));
    // ret_lines->erase(elimit, ret_lines->end());

    return QueryResult(rep(), ret_lines, lhsRes.get_file());
}

Query operator&(const Query &lhs, const Query &rhs)
{
    return new AndQuery(lhs, rhs);
}

Query operator&(Query &&lhs, Query &&rhs)
{
    return new AndQuery(std::move(lhs), std::move(rhs));
}

QueryResult AndQuery::eval(const TextQuery &text, std::size_t lb, std::size_t rb) const
{
    auto lhsRes = _left.eval(text, lb, rb), 
         rhsRes = _right.eval(text, lb, rb);
    
    auto ret_lines = make_shared<set<line_no>>();
    set_intersection(lhsRes.begin(), lhsRes.end(), rhsRes.begin(), rhsRes.end(),
                     inserter(*ret_lines, ret_lines->begin()));    
    // Bug9: 这是自己对set不熟悉，set没有push_back操作，只有insert操作

    // auto elimit = remove_if(ret_lines->begin(), ret_lines->end(),
    //                             Threshold(lb, rb));
    // ret_lines->erase(elimit, ret_lines->end());
    
    return QueryResult(rep(), ret_lines, lhsRes.get_file());
}

