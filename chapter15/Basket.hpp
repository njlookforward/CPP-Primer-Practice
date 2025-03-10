#ifndef BASKET_HPP
#define BASKET_HPP

#include "Quote.hpp"
#include <set>
#include <memory>

class Basket {
public:
    Basket() = default;
    void insert(const std::shared_ptr<Quote> &item)
    {   _items.insert(item);    }

    // 最终目的是要在basket中添加quote或者bulk_quote等派生类对象
    void add_item(const Quote &);
    void add_item(Quote &&);

    double total_receipt(std::ostream &os) const;

private:
    static bool compare(const std::shared_ptr<Quote> &lhs, 
                        const std::shared_ptr<Quote> &rhs)
    {   return lhs->isbn() < rhs->isbn();   }

    std::multiset<std::shared_ptr<Quote>, decltype(compare) *> _items{compare}; // 类内赋予初始值除了等号之外的方法
    // 只要知道一个less<key>，multiset就知道等于，大于的比较方式了
};

inline double Basket::total_receipt(std::ostream &os) const
{
    double sum = 0.0;
    for(auto iter = _items.cbegin(); iter != _items.cend();
             iter = _items.upper_bound(*iter))
    {
        sum += print_total(os, **iter, _items.count(*iter));
    }

    os << "Total sale: " << sum;

    return sum;
}

inline void Basket::add_item(const Quote &q)
{
    _items.insert(std::shared_ptr<Quote>(q.clone()));
}

inline void Basket::add_item(Quote &&q)
{
    _items.insert(std::shared_ptr<Quote>(std::move(q).clone()));
}

#endif