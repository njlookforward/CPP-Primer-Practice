#include "Query.hpp"
#include <algorithm>
#include <iterator>
using namespace std;

Query::Query(const std::string &word): _query(new WordQuery(word)) {}
// Bug10: 这是一个好Bug，WordQuery的构造函数是private, Query设置为WordQuery的友元类，因此Query可以定义WordQuery对象
// 包括new一个WordQuery对象，但是不能std::make_shared<WordQuery>(word)，因为make_shared不是WOrdQuery的友元函数

Query operator~(const Query &qr)
{
    return shared_ptr<Query_base>(new NotQuery(qr));
}

QueryResult NotQuery::eval(const TextQuery &text) const
{
    // 取反查询操作
    auto result = _query.eval(text);
    auto ret_lines = make_shared<set<line_no>>();

    auto bgit = result.begin(),
         edit = result.end();
    auto sz = result.get_file()->size();

    for(line_no n = 0; n < sz; ++n)
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
    return shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}

QueryResult OrQuery::eval(const TextQuery &text) const
{
    auto lhsRes = _left.eval(text),
         rhsRes = _right.eval(text);
    
    auto ret_lines = make_shared<set<line_no>>(lhsRes.begin(), lhsRes.end());
    ret_lines->insert(rhsRes.begin(), rhsRes.end());

    return QueryResult(rep(), ret_lines, lhsRes.get_file());
}

Query operator&(const Query &lhs, const Query &rhs)
{
    return shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}

QueryResult AndQuery::eval(const TextQuery &text) const
{
    auto lhsRes = _left.eval(text), 
         rhsRes = _right.eval(text);
    
    auto ret_lines = make_shared<set<line_no>>();
    set_intersection(lhsRes.begin(), lhsRes.end(), rhsRes.begin(), rhsRes.end(),
                     inserter(*ret_lines, ret_lines->begin()));    
    // Bug9: 这是自己对set不熟悉，set没有push_back操作，只有insert操作
    
    return QueryResult(rep(), ret_lines, lhsRes.get_file());
}
