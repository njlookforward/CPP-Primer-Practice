#include "Quote.hpp"
using namespace std;

double Quote::net_price(size_t sz) const
{
    return _price * sz;
}

void Quote::debug() const
{
    cout << "ISBN: " << _isbn
         << " # original price: " << _price;
}

double Bulk_Quote::net_price(std::size_t sz) const
{
    if(_discount <= 0 || _discount >= 1)
        throw out_of_range("discount is invalid");
    
    // Bug2: 竟然忘记了折扣策略，不应该啊
    if(sz >= _quantity)
        return _price * (1 - _discount) * sz;
    else
        return _price * sz;
}

void Bulk_Quote::debug() const
{
    Quote::debug();
    cout << " min_quantity: " << _quantity
         << " discount: " << _discount << endl;
}

double print_total(std::ostream &os, const Quote &item, std::size_t sz)
{
    double total = item.net_price(sz);
    os << "ISBN: " << item.isbn()
       << " # sold: " << sz << " due price: " << total << endl;

    return total;
}

double Preference_Quote::net_price(std::size_t sz) const
{
    if(_discount <= 0 || _discount >= 1)
        throw out_of_range("discount is invalid");
    
    if(sz <= _quantity)
        return _price * (1 - _discount) * sz;
    else
        return _price * (1 - _discount) * _quantity + _price * (sz - _quantity);
}

void Preference_Quote::debug() const
{
    Quote::debug();

    cout << " max_quantity: " << _quantity
         << " discount: " << _discount << endl;
}
