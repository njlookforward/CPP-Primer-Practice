#include "exercise.hpp"
using namespace std;

void initBookStoreSet(std::vector<std::vector<Sales_data>> &bookstores, std::ifstream &infile)
{
    vector<Sales_data> bookstore;
    Sales_data trans;
    while (infile >> trans)
    {
        bookstore.push_back(trans);
    }
    bookstores.push_back(bookstore);
}

matchSet_ptr findBook(std::vector<std::vector<Sales_data>> &bookstoreSet, const std::string &book)
{
    matchSet_ptr pset = make_shared<vector<matches>>();

    for(auto bgit_store = bookstoreSet.begin(); bgit_store != bookstoreSet.end(); ++bgit_store)
    {
        // 重载函数，只有到编译时才能知道，所以不要害怕报错
        stable_sort(bgit_store->begin(), bgit_store->end(), 
            static_cast<bool(*)(const Sales_data&, const Sales_data&)>(compareIsbn));
        // Bug: 在C++中，传入函数名作为函数指针的实参时，如果传入的是重载函数的函数名，且函数形参是一个模板类型
        // 并没有指出函数指针的类型，那么编译器是无法根据传入的函数名选择某个具体的函数版本，会发生歧义，因此需要使用
        // static_cast将函数实参显示转换成我们需要的函数指针类型，才能让编译器找到目标重载函数
        pair<vector<Sales_data>::iterator, vector<Sales_data>::iterator> scope = 
            equal_range(bgit_store->begin(), bgit_store->end(), Sales_data(book),
            static_cast<bool(*)(const Sales_data&, const  Sales_data&)>(compareIsbn));
        // Bug: 在标准库泛型算法equal_range中，搜索值类型必须与容器元素值类型保持一致，而且传入的比较算法应该比较的是
        // 两个相同类型的即容器元素类型的比较算法；因为他会交换容器元素类型的值与搜索值的顺序来实现>的算法，通过交换值的
        // 顺序使用一个<运算符同时实现</>/==的算法
        if(scope.first != scope.second)
            pset->push_back(make_tuple(bgit_store - bookstoreSet.begin(), 
                            scope.first, scope.second));
        else
            continue;
    }

    return pset;
}

void reportResults(std::istream &is, std::ostream &os, std::vector<std::vector<Sales_data>> &files)
{
    string book;
    while(true)
    {
        os << "Please input which book you want to realize sale data or q to quit: ";
        is >> book;
        if(!is || book == "q") break;
        auto pset = findBook(files, book);
        if(pset->empty()) {
            os << "Sorry, there isn't any data in the saleLibrary about " << book << endl;
            continue;
        } else {    
            for (const auto &item : *pset)
            {
                os << "store " << get<0>(item) << " sales: "
                     << accumulate(get<1>(item), get<2>(item), Sales_data(book)) << endl;
                     // Bug: 肯定有原因，accumulate是在<numeric>头文件中
            }
        }
    }
}

std::pair<storeNo, bookPos> findBook_v2(std::vector<std::vector<Sales_data>> &bookStores, const std::string &book)
{
    // 如果没有找到，就返回bookstores.size()和bgit_store.end()
    for(auto bgit_store = bookStores.begin(); bgit_store != bookStores.end(); ++bgit_store)
    {
        auto bookit = find_if(bgit_store->begin(), bgit_store->end(),
                [book](const Sales_data &item){ return item.isbn() == book; }); // Bug: find_if需要一元谓词
        if(bookit != bgit_store->cend())
            return make_pair(bgit_store - bookStores.cbegin(), bookit);
    }
    return make_pair(bookStores.size(), bookStores.begin()->end());
}

pmatchset findBook_v3(std::vector<std::vector<Sales_data>> &bookstores, const std::string &book)
{
    pmatchset matchset = make_shared<vector<matchStore>>();

    for(auto bgit_store = bookstores.begin(); bgit_store != bookstores.end(); ++bgit_store)
    {
        stable_sort(bgit_store->begin(), bgit_store->end(),
            static_cast<bool(*)(const Sales_data&, const Sales_data&)>(compareIsbn));
        
        Sales_data tmp(book);
        auto found = equal_range(bgit_store->begin(), bgit_store->end(), tmp,
            static_cast<bool(*)(const Sales_data&, const Sales_data&)>(compareIsbn));
        if(found.first != found.second)
            matchset->push_back(matchStore(bgit_store - bookstores.begin(),
                                             found.first, found.second));
    }

    return matchset;
}
