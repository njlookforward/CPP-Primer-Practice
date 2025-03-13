#include <tuple>
#include <cstddef>
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include "exercise.hpp"

using namespace std;

void prog1_tuple()
{
    // tuple的构造函数应该是explicit,但是g++中能够编译通过，好吧
    tuple<size_t, size_t, size_t> threeD = {1, 2, 3};   // 默认构造函数进行值初始化，都为0
    tuple<string, vector<double>, int, list<int>>
        someVal("consntants", {3.14, 2.718}, 42, {0,1,2,3,4,5});
    
    auto item = make_tuple("0-999-78345-X", 3, 60.00);
    auto book = get<0>(item);
    auto cnt = get<1>(item);    // 在auto中，等号右值的const or &属性会被舍去
    auto price = get<2>(item) / cnt;
    get<2>(item) *= 0.8;    // 总价格打8折
    typedef decltype(item) trans;
    auto item_size = tuple_size<trans>::value;
    tuple_element<1, trans>::type units_sold;
    cout << book << " "
         << cnt << " "
         << price << " "
         << item_size << endl;
    
    tuple<string, string> duo{"1", "2"};
    tuple<size_t, size_t> twoD{1, 2};
    tuple<int, int> origin{1, 2};
    bool b = (twoD == origin);
    b = twoD < origin;
    cout << boolalpha << b << noboolalpha;
}

void prog2_tuple_bookstores(int argc, char **argv)
{
    checkArgs(argc, 5);
    ifstream ifs1, ifs2, ifs3, ifs4;
    openInputFile(ifs1, argv[1]);
    openInputFile(ifs2, argv[2]);
    openInputFile(ifs3, argv[3]);
    openInputFile(ifs4, argv[4]);
    shared_ptr<ifstream> pfile1(&ifs1, [](ifstream *pf) { pf->close();  });
    shared_ptr<ifstream> pfile2(&ifs2, [](ifstream *pf) { pf->close();  });
    shared_ptr<ifstream> pfile3(&ifs3, [](ifstream *pf) { pf->close();  });
    shared_ptr<ifstream> pfile4(&ifs4, [](ifstream *pf) { pf->close();  });

    vector<vector<Sales_data>> bookstores;
    initBookStoreSet(bookstores, ifs1);
    initBookStoreSet(bookstores, ifs2);
    initBookStoreSet(bookstores, ifs3);
    initBookStoreSet(bookstores, ifs4);

    reportResults(cin, cout, bookstores);
}

int main(int argc, char **argv)
{
    // prog1_tuple();
    prog2_tuple_bookstores(argc, argv);

    return 0;
}