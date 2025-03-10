#ifndef QUERY_HPP
#define QUERY_HPP

#include "TextQuery.hpp"

// 我认为该程序设计分为程序接口类和程序实现类，因此暴露给用户的接口都设计在程序接口类Query中
// 而程序实现类只暴露给程序接口类（设置为友元类），其余设计为protected和private
// 程序接口类与程序实现类与类中的接口函数public和实现函数private是一个道理
class Query;
class Query_base {
    friend class Query;
protected:
    using line_no = TextQuery::line_no;
    virtual ~Query_base() = default;    // 作为基类必须定义虚析构函数

private:
    // 所有的查找类都有两个操作，一个查找，一个打印操作对象
    virtual QueryResult eval(const TextQuery &, std::size_t, std::size_t) const = 0;  // pure virtual funtion
    virtual std::string rep() const = 0;
    virtual Query_base *clone() const & = 0;    // 其实只需要常量左值引用
    virtual Query_base *clone() && = 0;         // 右值引用不会被用到
};

// Query是程序接口类，负责隐藏整个继承体系，通过智能指针来实现虚调用，即多态性
// 只要能理解 Query result = Query("fiery") & Query("hair") | Query("wind")就可以知道Query需要有哪些操作
// 继承体系中最基础的查询工作是WordQuery, 因此上面的例子就是查询语句，无论多么复杂的查询语句，最终可以分解成
// 各种Query("word")的位运算组合，因此需要string的构造函数
// 除此Query的构造和位运算操作外，Query还有接口的操作, 抽象基类Query_base所拥有的操作，Query必须都有
class Query {
    friend Query operator~(const Query &qr);
    friend Query operator~(Query &&qr);
    friend Query operator&(const Query &lhs, const Query &rhs);
    friend Query operator&(Query &&lhs, Query &&rhs);
    friend Query operator|(const Query &lhs, const Query &rhs);
    friend Query operator|(Query &&lhs, Query &&rhs);

public:
    // Bug3: 派生类WordQuery定义在此构造函数的下面，编译器是无法识别的
    // Query(const std::string &word): _query(new WordQuery(word)) {}
    Query(const std::string &word);

    // 根据三/五法则，有析构函数必须定义自己的拷贝控制成员
    Query(const Query&);
    Query(Query &&);

    Query &operator=(const Query &);
    Query &operator=(Query &&);

    ~Query() {
        if(_query)
            delete _query;  // 必须是有效指针时才可以释放空间
    }
    
    QueryResult eval(const TextQuery &text, std::size_t lb, std::size_t rb) const { return _query->eval(text, lb, rb);  }   // Bug4: 对eval函数不熟悉，又忘记了传递实参
    std::string rep() const {   return _query->rep();   }

private:
    // 把生成特殊Query_base的任务只交给位运算，不需要交给用户，因此设置能private
    Query(Query_base *qr): _query(qr) {}

    Query_base *_query = nullptr; // 需要定义拷贝控制成员，我决定利用虚拷贝，包括移动操作
    // 不要想太多，对于普通指针，考虑空指针问题，避免完美主义，从熟悉的入手，一点点修改，工程师的扳手原理
};

// WordQuery只用来查询单词，而不用管其他的派生类
class WordQuery: public Query_base {
    friend class Query;
private:
    WordQuery(const std::string &word): _word(word) {}
    WordQuery(const WordQuery &) = default;
    WordQuery(WordQuery &&) = default;

    QueryResult eval(const TextQuery &text, std::size_t lb, std::size_t rb) const;
    std::string rep() const {   return _word;   }

    WordQuery *clone() const & {    return new WordQuery(*this);        }
    WordQuery *clone() &&   {   return new WordQuery(std::move(*this)); }

    std::string _word;
};

// 对于程序实现类NotQuery的查询对象是所有派生类，包括WordQuery, OrQuery, AndQuery, even NotQuery对象
class NotQuery: public Query_base {
    friend Query operator~(const Query &qr);    // 需要调用NotQuery的构造函数
    friend Query operator~(Query &&);
private:
    NotQuery(const Query &qr): _query(qr) {}
    NotQuery(Query &&qr): _query(std::move(qr)) {}
    NotQuery(const NotQuery &) = default;
    NotQuery(NotQuery &&) = default;

    QueryResult eval(const TextQuery &text, std::size_t, std::size_t) const;
    std::string rep() const {
        return "~(" + _query.rep() + ")";   // Bug5: + 错写成了<<，这还是编程不熟练，对string不熟悉
    }

    NotQuery *clone() const &   {   return new NotQuery(*this); }
    NotQuery *clone() &&    {   return new NotQuery(std::move(*this));  }   
    // 同样对于派生类也是，右值引用不会被用到

    Query _query;
};

// BinaryQuery的操作对象跟NotQuery一样，面对所有的派生类，仍然是一个抽象基类
class BinaryQuery: public Query_base {
protected:
    BinaryQuery(const Query &lhs, const Query &rhs, const std::string &symbol):
                _left(lhs), _right(rhs), _opSym(symbol) {}
    BinaryQuery(Query &&lhs, Query &&rhs, const std::string &symbol):
        _left(std::move(lhs)), _right(std::move(rhs)), _opSym(symbol) {}
    
    std::string rep() const {
        return "(" + _left.rep() + " " + _opSym + " "
               + _right.rep() + ")";
    }

    Query _left, _right;
    std::string _opSym;
};

class OrQuery: public BinaryQuery {
    friend Query operator|(const Query &lhs, const Query &rhs);
    friend Query operator|(Query &&lhs, Query &&rhs);
private:
    OrQuery(const Query &lhs, const Query &rhs): BinaryQuery(lhs, rhs, "|") {}
    OrQuery(Query &&lhs, Query &&rhs): BinaryQuery(std::move(lhs), std::move(rhs), "|") {}
    OrQuery(const OrQuery &) = default;
    OrQuery(OrQuery &&) = default;

    QueryResult eval(const TextQuery &text, std::size_t, std::size_t) const;

    OrQuery *clone() const &    {   return new OrQuery(*this);  }
    OrQuery *clone() && {   return new OrQuery(std::move(*this));   }
};

class AndQuery: public BinaryQuery {
    friend Query operator&(const Query &lhs, const Query &rhs);
    friend Query operator&(Query &&lhs, Query &&rhs);

private:
    AndQuery(const Query&lhs, const Query &rhs): BinaryQuery(lhs, rhs, "&") {}
    AndQuery(Query &&lhs, Query &&rhs): BinaryQuery(std::move(lhs), std::move(rhs), "&") {}
    AndQuery(const AndQuery &) = default;
    AndQuery(AndQuery &&) = default;

    QueryResult eval(const TextQuery &text, std::size_t, std::size_t) const;

    AndQuery *clone() const &   {   return new AndQuery(*this); }
    AndQuery *clone() &&    {   return new AndQuery(std::move(*this));  }
};


Query operator~(const Query &qr);   // 怪不得IDE会显示有错误，位取反运算的操作数只有一个
Query operator&(const Query &lhs, const Query &rhs);
Query operator|(const Query &lhs, const Query &rhs);
Query operator~(Query &&qr);
Query operator&(Query &&lhs, Query &&rhs);
Query operator|(Query &&lhs, Query &&rhs);

inline
std::ostream &operator<<(std::ostream &os, const Query &qr)
{   return os << qr.rep();   }  // Bug2: 不清楚自己定义的函数

#endif

// Bug1: Query的定义应该在NotQuery, BinaryQuery的前面，因为这两个派生类含有Query的数据成员
// Bug2: 不清楚自己定义的函数
// Bug3: 派生类WordQuery定义在此构造函数的下面，编译器是无法识别的
// Query(const std::string &word): _query(new WordQuery(word)) {}

// Bug4: 对eval函数不熟悉，又忘记了传递实参
// Bug5: + 错写成了<<，这还是编程不熟练，对string不熟悉
// Bug6, 还是马虎，对函数eval不熟悉
// Bug7: 这绝对是马虎，argv也写成了argc
// Bug8: 这是自己对set不熟悉，set没有push_back操作，只有insert操作
// Bug9: 这是一个好Bug，WordQuery的构造函数是private, Query设置为WordQuery的友元类，因此Query可以定义WordQuery对象
// 包括new一个WordQuery对象，但是不能std::make_shared<WordQuery>(word)，因为make_shared不是WOrdQuery的友元函数
// Bug10: throw是C++的关键字，没有定义在std命名空间中。