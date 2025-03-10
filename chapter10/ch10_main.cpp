#include "exercise.hpp"
#include "Sales_data.hpp"

void prog1_algorithm()
{
    vector<int> ivec;
    int elem;
    while (cin >> elem)
    {
        ivec.push_back(elem);
    }
    
    elem = 42;
    auto result = find(ivec.cbegin(), ivec.cend(), elem);
    cout << elem
         << (result != ivec.cend() ? " is " : " is not ")
         << "present in the sequence." << endl;

    // because this is generic algorithm, can being used in all kinds of container
    list<string> slst{"I", "am", "looking for", "a value"};
    auto res1 = find(slst.cbegin(), slst.cend(), "a value");
    cout << "a value "
         << (res1 != slst.cend() ? "is " : "is not ")
         << "present in the sequence." << endl;
    
    int ia[] = {27, 210, 12, 47, 109, 83};
    elem = 110;
    // auto res2 = find(begin(ia), end(ia), elem);
    auto res2 = find(ia+1, ia+4, elem);
    cout << elem
         << (res2 != ia+4 ? " is " : " is not ")
         << "present in the sequence." << endl;
}

void prog2_algorithm()
{
    vector<int> ivec;
    int elem;
    while (cin >> elem)
    {
        ivec.push_back(elem);
    }

    auto sum = accumulate(ivec.cbegin(), ivec.cend(), 0);
    cout << "the sum of sequence is " << sum << endl;

    list<string> slst;
    vector<string> svec;
    ifstream infile(".\\data\\accum");
    if(!infile)
    {
        cerr << "Sorry, cannot open this file." << endl;
        return;
    }
    string word;
    while (infile >> word)
    {
        slst.push_back(word);
        svec.insert(svec.cend(), word);
    }
    auto sumStr = accumulate(slst.cbegin(), slst.cend(), string(""));
    // the third argument must be string, only string has operator+
    cout << "Finally, the sum of string sequence is" << endl
         << sumStr << endl;
    
    auto res = equal(slst.cbegin(), slst.cend(), svec.cbegin());
    cout << "slst "
         << (res == true ? "== " : "!= ")
         << "svec" << endl;

    infile.close();
}

void prog3_write_algor()
{
    vector<int> ivec(10, 1);
    cout << "before fill the vector: ";
    for (auto &&i : ivec)
    {
        cout << i << " ";
    }
    cout << endl;

    fill(ivec.begin(), ivec.end(), 0);
    cout << "after fill the vector: ";
    for (auto &&i : ivec)
    {
        cout << i << " ";
    }
    cout << endl;
    
    fill(ivec.begin(), ivec.begin() + ivec.size() / 2, 10);
    cout << "after fill half the vector: ";
    for (auto &&i : ivec)
    {
        cout << i << " ";
    }
    cout << endl;

    // 注意：向目地迭代器写入元素，要保证目的容器有足够的空间容纳要写入的元素
    ivec.clear();   // clear vector
    srand(static_cast<unsigned>(time(NULL)));   // 生成随机数种子
    auto iter = back_inserter(ivec);
    iter = 42;  // 迭代器适配器可以直接赋值

    fill_n(iter, 8, rand()%20);
    cout << "after fill 8 random number: ";
    for (auto &&i : ivec)
    {
        cout << i << " ";
    }
    cout << endl;

    // welcome to copy algorithm
    int a1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int a2[sizeof(a1) / sizeof(*a1)];
    copy(begin(a1), end(a1), begin(a2));
    for (auto &&i : a2)
    {
        cout << i << " ";
    }
    cout << endl;

    ivec.clear();
    list<int> ilst;
    int elem;
    while (cin >> elem)
    {
        ilst.push_front(elem);
    }
    for (auto &&i : ilst)
    {
        cout << i << " ";
    }
    cout << endl;
    // replace(ilst.begin(), ilst.end(), 23, 0);
    replace_copy(ilst.cbegin(), ilst.cend(), back_inserter(ivec), 23, 0);
    cout << "after replace and copy into ivec:" << endl;
    for (auto &&i : ivec)
    {
        cout << i << " ";
    }
    cout << endl;
}

void prog4_predicate()
{
    vector<string> svec;
    string str;
    while (cin >> str)
    {
        svec.push_back(str);
    }
    // cout << "before sort: " << endl;
    // print(svec);
    // sort(svec.begin(), svec.end(), isShorter);
    // cout << "after rely on size sort: " << endl;
    // print(svec);

    elimDups(svec);
    // stable_sort(svec.begin(), svec.end(), isShorter);
    stable_sort(svec.begin(), svec.end(), [](const string &a, const string &b)
                                          {   return a.size() < b.size(); });
    cout << "after rely on lambda calculate size stable_sort: " << endl;
    print(svec); 
}

void prog5_lambda()
{
    // lambda expression: [capture list](parameter list) -> return type { function body }
    auto f = [] {   return 42;  };   // lambda expression must has [] and {} at least
    cout << f() << endl;    // use operator() invoke lambda

    // vector<string> svec;
    // string str;
    // while (cin >> str)
    // {
    //     svec.push_back(str);
    // }
    // biggies(svec, 5);

    // 值捕获
    size_t v1 = 24; // local variable
    auto f1 = [v1] { return v1; };  // captured varable is copied in the lambda's initialization, not invoke
    v1 = 0;
    cout << f1() << endl;

    // 引用捕获
    size_t v2 = 2024;
    auto f2 = [&v2] {   return v2;  };
    v2 = 12;
    cout << "f2() = " << f2() << endl;

    // 可变lambda, 在lambda中可以改变捕获变量的值
    size_t v3 = 2024;
    auto f3 = [v3] () mutable { return ++v3;    };
    v3 = 0;
    cout << "f3() = " << f3() << endl
         << "f3() = " << f3() << endl
         << "f3() = " << f3() << endl;
    
    size_t v4 = 12;
    auto f4 = [&v4] () {    return ++v4;    };
    v4 = 0;
    cout << "f4() = " << f4() << endl
         << "f4() = " << f4() << endl
         << "f4() = " << f4() << endl;
    
    vector<int> ivec;
    int elem;
    while (cin >> elem)
    {
        ivec.push_back(elem);
    }
    vector<int> ivecopy(ivec.size());
    // transform(ivec.cbegin(), ivec.cend(), ivecopy.begin(),
    //           [] (int i)
    //           { return i < 0 ? -i : i;  });

    // 只要lambda中不仅仅是单一的return statement, 还有其他语句就必须指出return type
    transform(ivec.cbegin(), ivec.cend(), ivecopy.begin(),
              [] (int i) -> int
              { if(i < 0) return -i; else return i; });
    cout << "before transform: " << endl;
    print(ivec);
    cout << endl << "after transform: " << endl;
    print(ivecopy);
}

void prog6_bind()
{
    vector<string> svec;
    string str;
    while (cin >> str)
    {
        svec.push_back(str);
    }
    // biggies(svec, 6);

    // use bind can swap parameter's order
    // 单词按从短到长排序
    sort(svec.begin(), svec.end(), isShorter);
    // print(svec);
    for_each(svec.cbegin(), svec.cend(), bind(display, ref(cout), placeholders::_1, ' '));
    cout << endl;
    // 由长到短排序
    sort(svec.begin(), svec.end(), bind(isShorter, placeholders::_2, placeholders::_1));
    for_each(svec.cbegin(), svec.cend(), bind(display, ref(cout), placeholders::_1, ' '));
}

void prog7_inserter()
{
    list<int> lst{1, 2, 3, 4};
    list<int> lst2, lst3;
    copy(lst.cbegin(), lst.cend(), front_inserter(lst2));
    print(lst2);
    copy(lst.cbegin(), lst.cend(), inserter(lst3, lst3.begin()));
    print(lst3);
}

void prog8_iostream_iterator()
{
    istream_iterator<int> int_iter(cin), eof;
    vector<int> ivec1(int_iter, eof);
    // vector<int> ivec;
    // while (int_iter != eof)
    // {
    //     ivec.push_back(*int_iter++);
    // }
    print(ivec1);

    ifstream ifs(".\\data\\count-size");
    if(!ifs)
    {
        cerr << "Sorry, cannot open this file." << endl;
        return;
    }

    istream_iterator<string> isiter(ifs), ifsEof;
    list<string> slst(isiter, ifsEof);
    print(slst);

    // 尝试是否可以在恢复cin状态后，可以继续使用istream_iterator
    // cin.clear();
    // cout << accumulate(int_iter, eof, 0) << endl;
    
    ifstream numfile(".\\data\\outFile2");
    if(!numfile)
    {
        cerr << "Sorry, cannot open this file." << endl;
        return;
    }
    istream_iterator<int> numiter(numfile), numeof;
    cout << accumulate(numiter, numeof, 0) << endl;

    vector<int> ivec{23, 109, 45, 89, 6, 34, 12, 90, 34, 23, 56, 23, 8, 89, 23};
    sort(ivec.begin(), ivec.end());
    ofstream ofile(".\\data\\outFile2", ios::app | ios::out);
    if(!ofile)
    {
        cerr << "Sorry, cannot open this ofile." << endl;
        return;
    }
    ostream_iterator<int> ositer(ofile, " ");
    for (auto &&i : ivec)
    {
        ositer = i;
    }
    
    ofile.close();
    numfile.close();
    ifs.close();

    ostream_iterator<int> out_iter(cout, " ");
    copy(ivec.cbegin(), ivec.cend(), out_iter);
    cout << endl;
}

void prog9_iostream_iterator()
{
    ifstream infile(".\\data\\book_sales");
    if(!infile)
    {
        cerr << "Sorry, cannot open infile." << endl;
        return;
    }

    // 用留迭代器处理自定义类类型，前提是自定义类类型必须定义了operator<< operator>>
    istream_iterator<Sales_data> sold_iter(infile), eof;
    ostream_iterator<Sales_data> out_iter(cout, "\n");
    // vector<Sales_data> soldmsg(sold_iter, eof);
    // print(soldmsg);
    if(sold_iter != eof)
    {
        // Sales_data total(*sold_iter++);
        // while (sold_iter != eof)
        // {
        //     Sales_data trans(*sold_iter++);
        //     if(total.isbn() == trans.isbn())
        //         total.combine(trans);
        //     else
        //     {
        //         cout << total << endl;
        //         total = trans;
        //     }    
        // }
        // cout << total << endl;

        Sales_data total(*sold_iter++);
        while (sold_iter != eof)
        {
            if(sold_iter->isbn() == total.isbn())
                total.combine(*sold_iter++);
            else
            {
                out_iter = total;
                total = *sold_iter++;
            }    
        }
        out_iter = total;
    }
    else
        cerr << "This file is empty." << endl;   

    infile.close();
}

void prog10_reverse_iterator()
{
    vector<int> ivec{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for(auto r_iter = ivec.crbegin(); r_iter != ivec.crend(); ++r_iter)
        cout << *r_iter << " ";
    cout << endl;

    vector<int> vec1;
    Input(cin, vec1);   // 马虎的最高境界竟然是能够圆回来得到正确结果
    vector<int> vec2(vec1);

    sort(vec1.begin(), vec1.end()); // ascend sort
    cout << "Ascend Sort: " << endl;
    print(vec1);
    sort(vec2.rbegin(), vec2.rend());   // Descend sort
    cout << "Descend Sort: " << endl;
    print(vec2);

    // the relationship of reverse_iterator and normal_iterator
    // istream_iterator<string> str_iter(cin);
    // string line = *str_iter++;
    // auto fcommait = find(line.cbegin(), line.cend(), ',');
    // cout << string(line.cbegin(), fcommait) << endl; // 打印第一个逗号之前的内容
    // auto lcommait = find(line.crbegin(), line.crend(), ',');
    // cout << string(lcommait.base(), line.cend()) << endl;   // 打印最后一个逗号之后的内容
}

void prog11_algorithm()
{
    vector<int> ivec;
    randInitCon(ivec, 10);
    cout << "before remove: "<< endl;
    print(ivec);
    // auto deit = remove_if(ivec.begin(), ivec.end(), [] (int elem) { return elem & 1; });
    list<int> ilst;
    remove_copy_if(ivec.begin(), ivec.end(), back_inserter(ilst),
                   [] (int elem) {  return elem & 1; });
    cout << "after remove, ivec is: " << endl;
    print(ivec);
    // ivec.erase(deit, ivec.end());
    // cout << "after erase: " << endl;
    // print(ivec);
    cout << "after remove and copy, ilst is " << endl;
    print(ilst);
}

void prog12_list_algorithm()
{
    // 对于list和forward_list，使用容器的成员函数算法代替通用的泛型算法
}

int main()
{
    // prog1_algorithm();
    prog2_algorithm();
    // prog3_write_algor();
    // prog4_predicate();
    // prog5_lambda();
    // prog6_bind();
    // prog7_inserter();
    // prog8_iostream_iterator();
    // prog9_iostream_iterator();
    // prog10_reverse_iterator();
    // prog11_algorithm();

    return 0;
}

// 哪怕只有一秒钟，一分钟，一小时也是一种重大胜利，不要在乎时长，不要磨洋工，认认真真过好当下的每一秒钟
// 一道题一道题的练，一个字一个字地看，一行行地看，一步一步地走，走得坚实而有力量，拿出你的激情
// 很多东西没见过，多见多练就好了，不要怕，拿出就做出一堆狗屎的心态行动就好了
// 读出声来，大声地说出自己的思路，爷就是自信，有耐心，不着急