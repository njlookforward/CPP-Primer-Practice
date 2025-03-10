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
    virtual QueryResult eval(const TextQuery &) const = 0;  // pure virtual funtion
    virtual std::string rep() const = 0;
};

// Query是程序接口类，负责隐藏整个继承体系，通过智能指针来实现虚调用，即多态性
// 只要能理解 Query result = Query("fiery") & Query("hair") | Query("wind")就可以知道Query需要有哪些操作
// 继承体系中最基础的查询工作是WordQuery, 因此上面的例子就是查询语句，无论多么复杂的查询语句，最终可以分解成
// 各种Query("word")的位运算组合，因此需要string的构造函数
// 除此Query的构造和位运算操作外，Query还有接口的操作, 抽象基类Query_base所拥有的操作，Query必须都有
class Query {
    friend Query operator~(const Query &qr);
    friend Query operator&(const Query &lhs, const Query &rhs);
    friend Query operator|(const Query &lhs, const Query &rhs);
    friend Query operator~(Query &&qr);
    friend Query operator&(Query &&lhs, Query &&rhs);
    friend Query operator|(Query &&lhs, Query &&rhs);

public:
    // 如果是类指针拷贝语义的话，只需要考虑Query的拷贝、移动控制，不涉及Query_base
    // 我靠，说明我自己设计的类值拷贝语义弄复杂了，他妹的
    Query(const std::string &word);
    Query(const Query&q): _query(q._query), _cnt(q._cnt) {
        ++*_cnt;
    }
    Query(Query &&q): _query(q._query), _cnt(q._cnt) {
        q._query = nullptr;
        q._cnt = nullptr;
    }

    Query &operator=(const Query &rhs) {
        ++*rhs._cnt;
        --*_cnt;
        if(*_cnt == 0 && _query)
        {
            delete _query;
            delete _cnt;
        }
        _query = rhs._query;
        _cnt = rhs._cnt;

        return *this;
    }

    Query &operator=(Query &&rhs) {
        if(this != &rhs) {
            --*_cnt;
            if(*_cnt == 0 && _query)
            {
                delete _query;
                delete _cnt;
            }
            _query = rhs._query;
            _cnt = rhs._cnt;
            rhs._query = nullptr;
            rhs._cnt = nullptr;
        }
        return *this;
    }

    ~Query() {
        if(_cnt) {
            --*_cnt;
            if(*_cnt == 0 && _query)
            {
                delete _query;
                delete _cnt;
            }
        }
    }
    
    QueryResult eval(const TextQuery &text) const { return _query->eval(text);  }   // Bug4: 对eval函数不熟悉，又忘记了传递实参
    std::string rep() const {   return _query->rep();   }

private:
    // 把生成特殊Query_base的任务只交给位运算，不需要交给用户，因此设置能private
    Query(Query_base * qr): _query(qr), _cnt(new int(1)) {}

    Query_base *_query = nullptr;
    int *_cnt = nullptr;
};

// WordQuery只用来查询单词，而不用管其他的派生类
class WordQuery: public Query_base {
    friend class Query;
private:
    WordQuery(const std::string &word): _word(word) {}

    QueryResult eval(const TextQuery &text) const { return text.query(_word); }
    std::string rep() const {   return _word;   }

    std::string _word;
};

// 对于程序实现类NotQuery的查询对象是所有派生类，包括WordQuery, OrQuery, AndQuery, even NotQuery对象
class NotQuery: public Query_base {
    friend Query operator~(const Query &qr);    // 需要调用NotQuery的构造函数
    friend Query operator~(Query &&qr);

private:
    NotQuery(const Query &qr): _query(qr) {}
    NotQuery(Query &&qr): _query(std::move(qr)) {}

    QueryResult eval(const TextQuery &text) const;
    std::string rep() const {
        return "~(" + _query.rep() + ")";   // Bug5: + 错写成了<<，这还是编程不熟练，对string不熟悉
    }

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
    QueryResult eval(const TextQuery &text) const;
};

class AndQuery: public BinaryQuery {
    friend Query operator&(const Query &lhs, const Query &rhs);
    friend Query operator&(Query &&lhs, Query &&rhs);

private:
    AndQuery(const Query&lhs, const Query &rhs): BinaryQuery(lhs, rhs, "&") {}
    AndQuery(Query &&lhs, Query &&rhs): BinaryQuery(std::move(lhs), std::move(rhs), "&") {}
    QueryResult eval(const TextQuery &text) const;
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