#ifndef QUOTE_HPP
#define QUOTE_HPP

#include <iostream>
#include <string>
#include <cstddef>
#include <stdexcept>
#include <utility>

// Base class, need to consider access
class Quote {
public:
    // 通过显示的定义拷贝控制成员，使得Quote类能够执行这些操作，而且其派生类会自动合成相应的操作
    Quote() {
        // std::cout << "Quote()" << std::endl;
    }

    Quote(const std::string &isbn, double price): _isbn(isbn), _price(price) {
        // std::cout << "Quote(const string &, double)" << std::endl;
    }

    Quote(const Quote &q): _isbn(q._isbn), _price(q._price) {
        // std::cout << "Quote(const Quote &)" << std::endl;
    }

    Quote(Quote &&q): _isbn(std::move(q._isbn)), _price(std::move(q._price)) {
        // std::cout << "Quote(Quote &&)" << std::endl;
    }

    Quote &operator=(const Quote &q) {
        // std::cout << "Quote &operator=(const Quote &)" << std::endl;
        if(this != &q)
        {
            // 说明不是自赋值
            _isbn = q._isbn;
            _price = q._price;
        }
        return *this;
    }

    Quote &operator=(Quote &&q)
    {
        // std::cout << "Quote &operator=(Quote &&)" << std::endl;
        if(this != &q)
        {
            _isbn = std::move(q._isbn);
            _price = q._price;
        }
        return *this;
    }

    virtual ~Quote()  // virtual destructor in order to carry out dynamic_binding
    {
        // std::cout << "~Quote()" << std::endl;
    }

    std::string isbn() const {  return _isbn;   }
    virtual double net_price(std::size_t sz) const;
    virtual void debug() const;

    // 模拟虚拷贝
    virtual Quote *clone() const & {    return new Quote(*this);    }
    virtual Quote *clone() && { return new Quote(std::move(*this));  }

private:
    std::string _isbn;  // book name

protected:
    double _price = 0;  // original price
};

// 继承体系需要进行重构
class Disc_quote: public Quote {
public:
    Disc_quote() {
        // std::cout << "Disc_quote()" << std::endl;
    }

    Disc_quote(const std::string &isbn, double p, std::size_t qty, double dis)
             : Quote(isbn, p), _quantity(qty), _discount(dis) {
        // std::cout << "Disc_quote(const string &, double, size_t, double)" << std::endl;
    }

    Disc_quote(const Disc_quote &dq): Quote(dq), _quantity(dq._quantity), _discount(dq._discount) {}
    Disc_quote(Disc_quote &&dq): Quote(std::move(dq)), _quantity(dq._quantity), _discount(dq._discount) {}

    Disc_quote &operator=(const Disc_quote &dq)
    {
        if(this != &dq)
        {
            Quote::operator=(dq);
            _quantity = dq._quantity;
            _discount = dq._discount;
        }
        return *this;
    }

    Disc_quote &operator=(Disc_quote &&dq)
    {
        if(this != &dq)
        {
            Quote::operator=(std::move(dq));
            _quantity = dq._quantity;
            _discount = dq._discount;
        }
        return *this;
    }

    ~Disc_quote() = default;

    double net_price(std::size_t sz) const override = 0;
    std::pair<std::size_t, double> discount_policy() const
    {   return {_quantity, _discount};  }

protected:
    std::size_t _quantity = 0;  // 折扣适合的购买量
    double _discount = 0.0;     // 折扣值
};

class Bulk_Quote: public Disc_quote {
public:
    Bulk_Quote() = default;
    // Bulk_Quote(const std::string &isbn, double price, std::size_t qty, double dis):
    //         Disc_quote(isbn, price, qty, dis) {}
    // 继承基类的构造函数
    using Disc_quote::Disc_quote;
    ~Bulk_Quote() = default;

    // 默认、拷贝、移动构造函数不会被继承，而是按照正常规则被合成
    Bulk_Quote(const Bulk_Quote &bq):Disc_quote(bq) {}
    Bulk_Quote(Bulk_Quote &&bq): Disc_quote(std::move(bq)) {}

    Bulk_Quote &operator=(const Bulk_Quote &bq)
    {
        if(this != &bq)
        {
            Disc_quote::operator=(bq);
        }
        return *this;
    }

    Bulk_Quote &operator=(Bulk_Quote &&bq)
    {
        if(this != &bq)
        {
            Disc_quote::operator=(std::move(bq));
        }
        return *this;
    }

    // use qualifier "override" to explictly specify derived class override virtual function
    double net_price(std::size_t sz) const override;    
    void debug() const override;

    // 对于虚函数，返回值可以是派生类的指针或引用
    Bulk_Quote *clone() const & {   return new Bulk_Quote(*this);   }
    Bulk_Quote *clone() && {    return new Bulk_Quote(std::move(*this));    }
    
// private:
//     std::size_t _min_quantity = 0;  // 满足折扣策略的最小数量
//     double _discount = 0.0;           // discount (0,1)
};

class Preference_Quote: public Disc_quote{
public:
    Preference_Quote() = default;
    Preference_Quote(const std::string &isbn, double price, std::size_t qty, double dis):
            Disc_quote(isbn, price, qty, dis) {}
    ~Preference_Quote() = default;

    double net_price(std::size_t sz) const override;
    void debug() const override;

    Preference_Quote *clone() const & { return new Preference_Quote(*this); }
    Preference_Quote *clone() && {  return new Preference_Quote(std::move(*this));  }

// private:
//     std::size_t _max_qty = 0;   // 可以享受优惠的最大数量
//     double _discount = 0;       // 折扣率
};

double print_total(std::ostream &os, const Quote &item, std::size_t sz);
// bool operator==(const Bulk_Quote &lhs, const Bulk_Quote &rhs);

#endif

// Bug1: 构造函数的成员初始化列表中要符合类中数据成员的声明顺序，否则会先被默认初始化再赋值