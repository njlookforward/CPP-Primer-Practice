#include <tuple>
#include <cstddef>
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include <bitset>
#include "exercise.hpp"

using namespace std;

void prog1_tuple()
{
    // tuple的构造函数应该是explicit,但是g++中能够编译通过，好吧
    // tuple<size_t, size_t, size_t> threeD = {1, 2, 3};   // 默认构造函数进行值初始化，都为0
    tuple<string, vector<double>, int, list<int>>
        someVal("consntants", {3.14, 2.718}, 42, {0,1,2,3,4,5});
    
    auto item = make_tuple("0-999-78345-X", 3, 60.00);
    auto book = get<0>(item);
    auto cnt = get<1>(item);    // 在auto中，等号右值的const or &属性会被舍去
    auto price = get<2>(item) / cnt;
    get<2>(item) *= 0.8;    // 总价格打8折
    typedef decltype(item) trans;
    auto item_size = tuple_size<trans>::value;
    // tuple_element<1, trans>::type units_sold;
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

void prog3_bitset()
{
    bitset<32> bitvec(1U);  // 这是一个constexpr变量
    bitset<13> bitvec1(0xbeef); //        1111011101111
    bitset<20> bitvec2(0xbeef); // 00001011111011101111
    bitset<128> bitvec3(~0ULL);
    bitset<32> bitvec4("1100");
    // 使用子串初始化
    string str("1111111000000011001101");
    bitset<32> bitvec5(str, 5, 4);
    bitset<32> bitvec6(str, str.size() - 4);
    cout << bitvec.to_string() << endl
         << bitvec1 << endl
         << bitvec2 << endl
         << bitvec3 << endl
         << bitvec4.to_string() << endl
         << bitvec5.to_string() << endl
         << bitvec6.to_string() << endl;
}

void prog4_bitset_operation()
{
    bitset<16> bitvec(1U);
    bool is_set = bitvec.any();         // true
    bool is_not_set = bitvec.none();    // false
    bool is_all_set = bitvec.all();     // false
    auto set_sz = bitvec.count();       // 1
    auto bitsz = bitvec.size();         // 16
    cout << set_sz << " " << bitsz << endl;
    cout << bitvec << endl;
    bitvec.flip();
    cout << bitvec << endl;
    bitvec.set();
    cout << bitvec << endl;
    bitvec.reset();
    cout << bitvec << endl;
    
    cout << bitvec.flip(0) << endl
         << bitvec.set(bitvec.size() - 1) << endl
         << bitvec.set(0, 0) << endl
         << bitvec.reset(2) << endl
         << bitvec.test(0) << endl;
    
    bitvec[0] = 1;
    bitvec[14] = bitvec[0];
    bitvec[0].flip();
    cout << ~bitvec[0] << endl;
    cout << bitvec[0] << endl
         << bitvec << endl;
    auto ulong = bitvec.to_ulong();
    cout << "ulong = " << ulong << endl;

    bitset<16> bits;
    cin >> bits;
    cout << "bits = " << bits << endl;
}

void prog5_bitset_quiz()
{
    // 大胆尝试，错就错了，他妹的，我要自己试试
    unsigned long quiz = 0;   
    // 针对班里的30名同学，通过了就置位，没通过就复位，以第29名同学为例
    quiz |= 1UL << 29;    // 第29名学生通过
    quiz &= ~(1UL << 29); // 第29名同学失败
    if(quiz & (1UL << 29))
        cout << "No.29 student pass" << endl;
    else
        cout << "No.29 student fail" << endl;

    /*******接下来使用bitset实现同样的功能********/
    bitset<32> grades;
    grades.set(29);
    grades.reset(29);
    grades[29] = true;
    if(grades.test(29))
        cout << "No.29 student pass" << endl;
    else
        cout << "No.29 student fail" << endl; 
}

void prog6_regex()
{
    
}

int main(int argc, char **argv)
{
    // prog1_tuple();
    // prog2_tuple_bookstores(argc, argv);
    // prog3_bitset();
    // prog4_bitset_operation();
    prog5_bitset_quiz();

    return 0;
}