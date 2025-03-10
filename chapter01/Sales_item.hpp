/* Starting exercise Cpp Primer, jiayou, persist to learn and modify comprehension
 * Author: NanJiang
 */
#ifndef SALES_ITEM_HPP
#define SALES_ITEM_HPP

#include <iostream>
#include <string>
// 这回就不用using namespace std了，慢慢适应带std命名空间的对象

class Sales_item
{
    // because need to access or modify Sales_item private data member
    friend std::istream& operator>>(std::istream &in, Sales_item &rhs);

private:
    std::string _isbn;          // 书号，唯一键值，implicit initialization to empty string
    unsigned _uints_sold = 0;   // 卖出总数；explicit initialization
    double _revenue = 0.0;      // 总收入；explicit initialization
public:
    Sales_item() = default; // 这种形式没有用过
    Sales_item(std::string isbn): _isbn(isbn) {}
    Sales_item(const Sales_item &rhs);  // copy constructor
    Sales_item(std::istream &in);   // 不知道出了什么事情
    ~Sales_item() {}

    // access private data member
    const std::string& isbn() const {    return _isbn;   }
    unsigned soldCount() const {    return _uints_sold; }
    double totalRevenue() const {   return _revenue;    }
    double averageSold() const;

    // modify private data member
    void isbn(std::string newISBN)       {    _isbn = newISBN;      }
    void soldCount(unsigned newCnt)      {   _uints_sold = newCnt;  }
    void totalRevenue(double newRevenue) {  _revenue = newRevenue;  }
    Sales_item &operator+=(const Sales_item &rhs);

    // for singal object operator
    bool operator==(const Sales_item &rhs) const;
    bool operator!=(const Sales_item &rhs) const;

};

std::istream& operator>>(std::istream &in, Sales_item &rhs);
std::ostream& operator<<(std::ostream &os, const Sales_item &rhs);
Sales_item operator+(const Sales_item &lhs, const Sales_item &rhs);
bool checkCompare(const Sales_item &lhs, const Sales_item &rhs);

#endif