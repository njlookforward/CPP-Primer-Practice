#include "exercise.hpp"
#include <array>
#include <initializer_list>
#include "Sales_data.hpp"

using namespace std;

void prog1_container()
{
    list<Sales_data> salesMge;
    deque<double> ddeq;
    vector<vector<string>> lines;

    list<string>::iterator iter;
    vector<int>::difference_type count;
    list<string> authors{"Milton", "Shakespeare", "Austen"};
    auto it1 = authors.begin();
    auto it2 = authors.rbegin();
    auto it3 = authors.cbegin();
    auto it4 = authors.crbegin();

    cout << *it1 << " " << *it2 << " " << *it3 << " " << *it4 << endl;

    // container definition and initialization
    vector<const char*> articles{"a", "an", "the"};
    list<string> lst2(authors); // copy constructor request container type and element type must conformity/correspondence
    // deque<string> sdeq(authors);    // error container
    // vector<string> svec(articles);  // error element
    forward_list<string> words(articles.begin(), articles.end());

    // only sequential container accept size initialization, associated container don't support
    vector<int> ivec(10, -1);
    list<string> slist(10, "hi");
    forward_list<int> iforLst(10);
    deque<string> sdeq(10); // 都进行值初始化

    // C++11加入的array顺序容器
    array<int, 10> ia1; // 默认初始化
    array<int, 10> ia2{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};   // 列表初始化
    array<int, 10> ia3{42}; // array[0] = 42, 另外9个都是0
    // 尽管内置数组不可以进行拷贝或对象赋值操作，但是array可以，但元素类型与大小必须匹配
    array<int, 10> digits(ia3);
    digits = ia2;
    // 以后用array来代替内置数组，其实用vector会更好
}

void prog2_assign_swap_relation()
{
   array<int, 10> arr1 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
   array<int, 10> arr2 = {0};
   arr1 = arr2;
   arr2 = {0, 1, 2, 3, 4, 5, 6, 7, 8};

   // use assign only for sequential container
   list<string> authors{"Milton", "Shakespeare", "Austen"};
   vector<const char*> articles{"a", "an", "the"};
   authors.assign(articles.cbegin(), articles.cend());
   cout << "authors after assign: ";
   for (auto &&i : authors)
   {
        cout << i << " ";
   }
   cout << endl;
    initializer_list<string> strLst{"Milton", "Shakespeare", "Austen"};
    authors.assign(strLst);
    cout << endl << "authors after assign: ";
   for (auto &&i : authors)
   {
        cout << i << " ";
   }
   cout << endl;

   list<string> slst(1);
   slst.assign(10, "hiya");
    cout << endl << "slst after assign: ";
   for (auto &&i : slst)
   {
        cout << i << " ";
   }
   cout << endl;

    // 尽可能使用非成员函数版本的swap是一个好习惯
   swap(authors, slst); // 两个容器类型要相同
    cout << endl << "authors after swap: ";
   for (auto &&i : authors)
   {
        cout << i << " ";
   }
   cout << endl;
    cout << "slst after swap: ";
   for (auto &&i : slst)
   {
        cout << i << " ";
   }
   cout << endl;

   vector<int> v1 = {1, 3, 5, 7, 9, 12};
   vector<int> v2 = {1, 3, 5, 9};
   vector<int> v3 = {1, 3, 5, 7};
   vector<int> v4 = {1, 3, 5, 7, 9, 12};
   cout << endl
        << (v1 < v2) << endl        // true
        << (v1 < v3) << endl        // false
        << (v1 == v4) << endl       // true
        << (v1 == v2) << endl;      // false
}

void prog3_sequential_operand()
{
    vector<string> svec;
    string word;
    // while (cin >> word)
    // {
    //     svec.push_back(word);
    // }
    svec.insert(svec.begin(), "hello");
    svec.insert(svec.end(), 10, "Anna");
    for (auto &&i : svec)
    {
        cout << i << " ";
    }
    cout << endl;

    list<int> ilst;
    for (int i = 0; i < 4; ++i)
    {
        ilst.push_front(i);
    }
    for (auto &&i : ilst)
    {
        cout << i << " ";
    }
    cout << endl;

    vector<string> v = {"quasi", "simba", "frollo", "scar"};
    list<string> slist;
    auto reiter1 = slist.insert(slist.begin(), v.end() - 2, v.end());
    cout << "reiter1 = " << *reiter1 << endl;
    auto reiter2 = slist.insert(slist.end(), {"these", "words", "will",
                               "go", "at", "the", "end"});
    cout << "reiter2 = " << *reiter2 << endl;
    
    // 学习使用insert的返回值
    auto iter = slist.begin();
    // don't forget cin's state dont't recovery
    cin.clear();
    // while (cin >> word)
    // {
    //     iter = slist.insert(iter, word);    // 相当于push_front
    // }
    for (auto &&i : slist)
    {
        cout << i << " ";
    }
    cout << endl;

    // use emplace construct element
    deque<Sales_data> salesMsg;
    salesMsg.emplace_back("978-0590353403", 25, 15.99);
    salesMsg.push_back(Sales_data("0-201-78345-X", 5, 15.99));
    auto saleit = salesMsg.begin() + 1;
    salesMsg.emplace(saleit, "0-201-70353-X", 4, 24.99);
    salesMsg.emplace_front("0-399-82477-1", 2, 45.39);
    for (auto &&i : salesMsg)
    {
        print(cout, i) << endl;
    }

    // access element in the container
    if(!slist.empty())  // before accessing element must assure container isn't empty
    {
        auto val1 = *slist.begin(), val2 = slist.front();   // 赋值给auto后会隐去引用
        auto last = slist.end();
        auto val3 = *(--last), val4 = slist.back();
        // forward_list 没有--和back
        cout << "first element is " << val1 << " and " << val2 << endl
             << "last element is " << val3 << " and " << val4 << endl;
    }
    // 访问成员函数返回的都是引用
    if(!slist.empty())
    {
        slist.front() = "NanJiang";
        auto &lastElem = slist.back();
        lastElem = "TianJin";
        auto elem = slist.back();
        elem = "C++";
    }
    for (auto &&i : slist)
    {
        cout << i << " ";
    }
    cout << endl;

    // vector<int> ivec;
    // cout << ivec[0];    // 发生运行时错误
    // cout << ivec.at(0); // 会抛出out_of_range exception
}

void prog4_erase()
{
    // 在容器内部删除一个元素，不要忘记要更新迭代器，引用或者指针
    vector<int> ivec{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    // delete odd element
    // auto iter = ivec.begin();
    // while (iter != ivec.end())
    // {
    //     if(*iter % 2)
    //         iter = ivec.erase(iter);
    //     else
    //         ++iter;    
    // }

    // erase 3-6
    auto bg = find(ivec.begin(), ivec.end(), 3),
         ed = find(ivec.begin(), ivec.end(), 6) + 1;
    bg = ivec.erase(bg, ed);
    cout << *bg << " with " << *ed << endl; // 7
    
    for (auto &&i : ivec)
    {
        cout << i << " ";
    }
    cout << endl;
}

void prog5_forward_list()
{
    // erase the odd element in the forward_list
    forward_list<int> ifLst{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto previt = ifLst.before_begin(),
         curit = ifLst.begin();
    while (curit != ifLst.end())
    {
        if(*curit % 2)
            curit = ifLst.erase_after(previt);
        else
        {
            ++previt;
            ++curit;
        }        
    }
    for (auto &&i : ifLst)
    {
        cout << i << " ";
    }
    cout << endl;
    auto last = find(ifLst.begin(), ifLst.end(), 8);
    auto newit = ifLst.insert_after(last, {13, 21, 34, 55});
    cout << *newit << endl;
    auto bgit = find(ifLst.begin(), ifLst.end(), 6),
         edit = find(ifLst.begin(), ifLst.end(), 13);
    newit = ifLst.erase_after(bgit, edit);
    cout << *newit << endl;
    for (auto &&i : ifLst)
    {
        cout << i << " ";
    }
}

void prog6_resize()
{
    list<int> ilst(10, 42);
    ilst.resize(15);
    cout << "after resize: ";
    for (auto &&i : ilst)
    {
        cout << i << " ";
    }
    cout << endl;
    ilst.resize(25, -1);
    cout << "after resize: ";
    for (auto &&i : ilst)
    {
        cout << i << " ";
    }
    cout << endl;
    ilst.resize(5);
    cout << "after resize: ";
    for (auto &&i : ilst)
    {
        cout << i << " ";
    }
    cout << endl;
}

void prog7_iterator()
{
    // 容器操作可能使迭代器失效，因此操作完成后需要重新定位迭代器
    vector<int> ivec{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    // delete even element and duplicate odd element
    auto iter = ivec.cbegin();
    while (iter != ivec.cend())
    {
        if(*iter % 2)
        {
            iter = ivec.insert(iter, *iter);
            iter += 2;
        }
        else
            iter = ivec.erase(iter);
    }
    for (auto &&i : ivec)
    {
        cout << i << " ";
    }
    cout << endl;
}

void prog8_vector_space()
{
    vector<int> ivec;
    cout << "ivec: size " << ivec.size()
         << " capacity "  << ivec.capacity() << endl;
    
    for (vector<int>::size_type i = 0; i != 24; ++i)
    {
        ivec.push_back(i);
    }
    cout << "ivec: size " << ivec.size()
         << " capacity "  << ivec.capacity() << endl;
    
    ivec.reserve(50);
    cout << "ivec: size " << ivec.size()
         << " capacity "  << ivec.capacity() << endl;

    // 用光这些容量
    while (ivec.size() != ivec.capacity())
    {
        ivec.push_back(0);
    }
    cout << "ivec: size " << ivec.size()
         << " capacity "  << ivec.capacity() << endl;   
    ivec.push_back(1);
    cout << "ivec: size " << ivec.size()
         << " capacity "  << ivec.capacity() << endl;
    ivec.shrink_to_fit();
    cout << "ivec: size " << ivec.size()
         << " capacity "  << ivec.capacity() << endl;
}

void prog9_string()
{
    // 构造string的另外三种方法
    const char *cp = "Hello World!!!";  // end with '\0'
    char noNull[] = {'h', 'i'}; // pure char array
    string s1(cp);  // constructor one
    string s2(noNull, 2);   // constructor two
    string s3(s1, 6);   // constructor three -> World!!!
    string s4(s1, 6, 5);    // constructor four -> World
    string s5(cp+6, 5); // World
    string s6(s1, 6, 20);   // just copy to string end
    // string s7(s1, 16);  // cast a out_of_range exception
    // string s8(noNull);  // 未定义
    cout << "s1 " << s1 << endl
         << "s2 " << s2 << endl
         << "s3 " << s3 << endl
         << "s4 " << s4 << endl
         << "s5 " << s5 << endl
         << "s6 " << s6 << endl;
        //  << "s8 " << s8 << endl;
    
    // 子字符串操作
    string s9("hello world");
    string sub1 = s9.substr(0, 5);  // hello
    string sub2 = s9.substr(6);     // world
    string sub3 = s9.substr(6, 20); // world
    string sub4 = s9.substr(11);    // ""
    // string sub5 = s9.substr(12);    // out_of_range
    cout << "sub1 " << sub1 << endl
         << "sub2 " << sub2 << endl
         << "sub3 " << sub3 << endl
         << "sub4 " << sub4 << endl;
}

void prog10_string_operand()
{
    string str("Hello World");
    auto &rstr = str.insert(str.size(), 3, '!');
    cout << "rstr: " << rstr << endl;
    auto &rs2 = str.erase(str.size() - 8, 8);
    cout << "rs2: " << rs2 << endl;

    const char *cp = "Stately, plump Buck";
    auto &rs3 = str.assign(cp, 7);
    cout << "rs3: " << rs3 << endl;
    // auto &rs4 = str.append(cp+7);
    auto &rs5 = str.insert(str.size(), cp+7);
    cout << "rs5: " << rs5 << endl;

    string s = "some string", s2 = "some other string";
    s.insert(0, s2);
    cout << "s: " << s << endl;
    s.insert(4, s2, 5, 5);
    cout << "s: " << s << endl;

    string s3 = "CPP Primer";
    s3.append(" 4th Ed.");
    cout << s3 << endl;
    s3.replace(11, 3, "5th");
    cout << s3 << endl;
}

void prog11_string_find()
{
    string name("AnnaBelle");
    auto pos = name.find("Anna");
    cout << "name[pos] = " << name[pos] << endl;
    pos = name.find("anna");
    if(pos == string::npos)
        cout << "anna don't being found." << endl;

    string numbers("0123456789"), str("r2d2");
    auto pos2 = str.find_first_of(numbers);
    cout << pos2 << " -> " << str[pos2] << endl;
    pos2 = numbers.find(str);
    if(pos2 == string::npos)
        cout << "str is not a substr of numbers." << endl;

    string dept("03714p3");
    pos2 = dept.find_first_not_of(numbers);
    cout << pos2 << " -> " << dept[pos2] << endl;

    pos2 = 0;
    while ((pos2 = dept.find_first_of(numbers, pos2)) != string::npos)
    {
        cout << "found number at index: " << pos2
             << " element is " << dept[pos2] << endl;
        ++pos2;
    }
    
    // reverse search
    string river("Mississippi");
    auto pos3 = river.find("is");
    cout << "find index is " << pos3 << endl;
    pos3 = river.rfind("is");
    cout << "rfind index is " << pos3 << endl;
}

void prog12_string_compare()
{
    string s1("hello"), s2("world");
    const char *cp = "hello world";

    auto res = s1.compare(s2);
    cout << res << endl;    // -1
    res = s1.compare(3, 2, s2, 3, 2);   // 1
    cout << res << endl;
    res = s1.compare(cp);
    cout << res << endl;    // -1
    res = s1.compare(0, 5, cp, 5);
    cout << res << endl;    // 0
}

void prog13_string_number()
{
    int i = 42;
    string s = to_string(i);
    double d = stod(s);
    cout << "s = " << s << endl
         << "d = " << d * 2 << endl;

    string s2 = "pi = -3.1415926.";
    double d2 = stod(s2.substr(s2.find_first_of("+-.0123456789")));
    cout << "d2 = " << d2 << endl;
    size_t pos;
    double d3 = stod(s2.substr(s2.find_first_of("+-.0123456789")), &pos);
    cout << "d3 = " << d3 << endl
         << "pos = " << pos << endl
         << "begin = " << &s2[s2.find_first_of("+-.0123456789")] << endl;
    
    string trys("    3.12");
    double tryd = stod(trys, &pos);
    cout << "tryd = " << tryd << endl
         << "pos = " << pos << endl;
}

void prog14_stack()
{
    deque<int> ideq = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    stack<int> stk(ideq);
    vector<string> svec = {"Milton", "Shakespeare", "Austen"};
    stack<string, vector<string>> str_stk(svec);
    str_stk.push("NanJiang");

    stack<int> intStk;
    for(int ix = 0; ix < 10; ++ix)
    {
        intStk.push(ix);
    }
    while (!intStk.empty()) // stack不能使用范围for statement
    {
        int elem = intStk.top();
        cout << elem << " ";
        intStk.pop();
    }
    cout << endl;
}

void prog15_queue()
{
    queue<int> ique;
    for(int ix = 0; ix < 10; ++ix)
        ique.push(ix);
    while (!ique.empty())
    {
        int elem = ique.front();
        cout << elem << " ";
        ique.pop();
    }
    cout << endl;

    priority_queue<string> spriQue;
    string word;
    while (cin >> word)
    {
        spriQue.push(word);
    }
    while (!spriQue.empty())
    {
        word = spriQue.top();
        cout << word << " ";
        spriQue.pop();
    }
    cout << endl;
}

int main()
{
    // prog1_container();
    // prog2_assign_swap_relation();
    // prog3_sequential_operand();
    // prog4_erase();
    prog5_forward_list();
    // prog6_resize();
    // prog7_iterator();
    // prog8_vector_space();
    // prog9_string();
    // prog10_string_operand();
    // prog11_string_find();
    // prog12_string_compare();
    // prog13_string_number();
    // prog14_stack();
    // prog15_queue();

    return 0;
}