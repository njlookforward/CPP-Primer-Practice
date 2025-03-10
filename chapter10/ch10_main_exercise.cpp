#include "exercise.hpp"

void exercise_10_1(int argc, char **argv)
{
    vector<int> ivec;
    Input(cin, ivec);
    string str(argv[1]);
    int elem = stoi(str);
    auto res = count(ivec.cbegin(), ivec.cend(), elem);
    cout << "In the sequence, " << elem
         << " occurs " << res << " times." << endl;
}

void exercise_10_2()
{
    list<string> slst;
    ifstream infile(".\\data\\accum");
    if(!infile)
    {
        cerr << "Sorry, cannot open the file." << endl;
        return;
    }
    Input(infile, slst);
    
    cout << "Please input what word you want to count: ";
    string aimStr;
    // cin.clear();
    cin >> aimStr;
    auto res = count(slst.cbegin(), slst.cend(), aimStr);
    cout << "#" << aimStr << "#"
         << " occurs " << res << " times." << endl;

    infile.close();
}

// exercise_10_3 is prog2
void exercise_10_4()
{
    vector<double> dvec;
    double d;
    while (cin >> d)
    {
        dvec.push_back(d);
    }
    auto sum = accumulate(dvec.cbegin(), dvec.cend(), 0.0);
    cout << "the sum of double sequence is " << sum << endl;
    // 通过编码说明，accumulate's third argument is 0, then return type is int and use int's operator+
    // will ignore 小数点尾数，只计算整数部分，结果肯定是错的
}

// exercise_10_5
// two roster's element are all char*, only compare two pointer, not the content of pointer
void exercise_10_5()
{
    const char *p[] = {"Hello", "World", "!"};
    char *q[] = {strdup(p[0]), strdup(p[1]), strdup(p[2])};
    const char *r[] = {p[0], p[1], p[2]};
    cout << "char *p[] "
         << (equal(begin(p), end(p), q) ? "== " : "!= ")
         << "char *q[]" << endl << endl
         << "char *p[] "
         << (equal(begin(p), end(p), r) ? "== " : "!= ")
         << "char *r[]" << endl;
    // 说明只是比较指针保存的地址，不是比较指针所指向的内容

    // never forget strdup's implement is TR动态内存，需要释放，否则会内存泄漏
    free(q[0]);
    free(q[1]);
    free(q[2]);
}

void exercise_10_6()
{
    // generic algorithm use iterator or pointer!!
    int a1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    fill_n(begin(a1), sizeof(a1)/sizeof(*a1), 0);
    for (auto &&i : a1)
    {
        cout << i << " ";
    }
    cout << endl;
}

// exercise_10_7
// (a): vec is empty, cannot being copyed, should use back_inserter(vec);
// (b): error because vec.reserve()是用来提前分配内存，只是影响capacity，但是此时vec中没有任何元素
// vec is empty, 因此向空容器中写入数值是错误的，应该改为vec.resize()
// 泛型算法对容器的要求并不是拥有多大的空间，而是拥有多少数量的元素，有了具体的元素才有对应的迭代器，才能进行赋值等迭代器操作
void exercise_10_7()
{
    vector<int> ivec;
    // ivec.reserve(10);
    ivec.resize(10);
    fill_n(ivec.begin(), 10, 4);
    // 我猜想ivec.begin() + 10 <= ivec.end(),这样来确保程序的安全性
    for (auto &&i : ivec)
    {
        cout << i << " ";
    }
    cout << endl;
}

// exercise_10_8
// 标准库算法使用的是迭代器操作，只有容器操作才能改变容器的大小，一般的迭代器操作与容器操作无关
// 而迭代器适配器的部分操作调用了容器操作，才导致容器大小发生改变。

void exercise_10_9()
{
    vector<string> svec;
    string str;
    while (cin >> str)
    {
        svec.push_back(str);
    }
    elimDups(svec);
}

// exercise_10_10
// 泛型算法是利用迭代器作为一层封装屏蔽了不同底层实现的容器的差异，使得他们可以共用一套代码
// 因此算法只能使用迭代器操作，而不能越过迭代器使用对应的容器操作，因此算法无法改变容器大小
// 泛型算法是通过迭代器实现了算法与数据结构相分离，generic algorithm operate iterator, iterator operate container

// exercise_10_11 is prog4_predicate

void exercise_10_12()
{
    vector<Sales_data> soldmsg;
    Input(cin, soldmsg);

    cout << "before sort: " << endl;
    for (auto &&entry : soldmsg)
    {
        print(cout, entry) << endl;
    }
    cout << endl;

    // sort(soldmsg.begin(), soldmsg.end(), compareIsbn);
    sort(soldmsg.begin(), soldmsg.end(), [](const Sales_data &lhs, const Sales_data &rhs)
                                                  {   return lhs.isbn() < rhs.isbn(); });
    cout << "after sort: " << endl;
    for (auto &&entry : soldmsg)
    {
        print(cout, entry) << endl;
    }
    cout << endl;
}

void exercise_10_13()
{
    vector<string> svec;
    string str;
    while (cin >> str)
    {
        svec.push_back(str);
    }
    
    auto resiter = partition(svec.begin(), svec.end(), bind(isMoreThresholdLeng, placeholders::_1, 5));
    // unsigned len = 5;
    // auto resiter = partition(svec.begin(), svec.end(), [len](const string &word) {    return word.size() >= 5; });
    print(svec.begin(), resiter);
    print(svec);
}

void exercise_10_14()
{
    auto f = [](int a, int b) { return a + b;   };
    cout << f(134, 34) << endl;
}

void exercise_10_15(int argc, char **argv)
{
    if(argc != 3)
    {
        cerr << "Please input two operands to add." << endl;
        return;
    }

    string s1(argv[1]), s2(argv[2]);
    int lhs = stoi(s1), rhs = stoi(s2);
    auto add = [lhs](int elem) {    return lhs + elem;  };
    cout << add(rhs) << endl;
}

// exercise_10_17 is exercise_10_12

void exercise_10_20()
{
    vector<string> svec;
    string word;
    while (cin >> word)
    {
        svec.push_back(word);
    }
    
    auto sixSum = count_if(svec.cbegin(), svec.cend(),
                [] (const string &str)  {   return str.size() >= 6; });
    cout << "In the sequence, " << sixSum
         << " words's length are more than six length." << endl;
}

void exercise_10_21()
{
    size_t sz = 8;
    // auto fcn = [sz] () mutable {    return sz > 0 ? sz-- : sz;  };
    auto fcn = [sz] () mutable -> bool {    if(sz>0) return sz--;   else return sz; };
    srand(static_cast<unsigned>(time(NULL)));
    vector<int> ivec;
    while (fcn())
    {
        ivec.push_back(rand() % 100);
    }
    print(ivec);
    cout << ivec.size() << endl;
}

void exercise_10_22()
{
    vector<string> svec;
    Input(cin, svec);
    auto sixSum = count_if(svec.cbegin(), svec.cend(), bind(isLessThresholdLeng, placeholders::_1, 6));
    cout << "In the sequence has " << sixSum
         << " words's length are less than 6." << endl;
    print(svec);
}

// exercise_10_23
// bind()接受的参数数量为1个可调用函数+这个可调用函数的参数数量

void exercise_10_24()
{
    string str("NanJiang");
    vector<int> ivec;
    Input(cin, ivec);
    auto iter = find_if(ivec.cbegin(), ivec.cend(), bind(isLessThresholdLeng, str, placeholders::_1));
    print(iter, ivec.cend());
    print(ivec);
}

// exercise_10_25 is ok

// exercise_10_26
// back_inserter(container)创建一个使用push_back的迭代器
// front_inserter创建一个使用push_front的迭代器
// inserter(container, iterator)创建一个使用insert的迭代器

void exercise_10_27()
{
    vector<string> svec;
    Input(cin, svec);
    sort(svec.begin(), svec.end());
    list<string> slst;
    unique_copy(svec.cbegin(), svec.cend(), back_inserter(slst));
    print(slst);
}

void exercise_10_28()
{
    vector<int> ivec{1,2,3,4,5,6,7,8,9};
    vector<int> ivec1;
    copy(ivec.cbegin(), ivec.cend(), back_inserter(ivec1));
    cout << "ivec1: ";
    print(ivec1);

    list<int> ilst;
    copy(ivec.cbegin(), ivec.cend(), front_inserter(ilst));
    cout << "ilst: ";
    print(ilst);
    vector<int> ivec3(ivec1);
    copy(ivec.cbegin(), ivec.cend(), inserter(ivec3, ivec3.begin() + 3));
    cout << "ivec3: ";
    print(ivec3);
}

void exercise_10_29()
{
    ifstream ifs(".\\data\\count-size");
    if(!ifs)
    {
        cerr << "Sorry, cannot open ifs." << endl;
        return;
    }

    istream_iterator<string> ifsIter(ifs), eof;
    vector<string> svec(ifsIter, eof);
    print(svec);

    ifs.close();
}

void exercise_10_30()
{
    istream_iterator<int> int_iter(cin), eof;
    ostream_iterator<int> out_iter(cout, " ");

    vector<int> ivec(int_iter, eof);
    sort(ivec.begin(), ivec.end());
    copy(ivec.cbegin(), ivec.cend(), out_iter);
    cout << endl;
    // exercise_10_31
    unique_copy(ivec.cbegin(), ivec.cend(), out_iter);
}

void exercise_10_32()
{
    ifstream ifs(".\\data\\book_sales");
    if(!ifs)
    {
        cerr << "Sorry, cannot open ifs." << endl;
        return;
    }

    istream_iterator<Sales_data> sold_iter(ifs), eof;
    ostream_iterator<Sales_data> out_iter(cout, "\n");

    vector<Sales_data> soldMsg(sold_iter, eof);
    sort(soldMsg.begin(), soldMsg.end(), [] (const Sales_data &lhs, const Sales_data &rhs)
                                         {   return lhs.isbn() < rhs.isbn(); });
    // 要进行最关键的一步，不断计算相同isbn的数据并打印
    // for(auto bgit = soldMsg.cbegin(); bgit != soldMsg.cend(); ++bgit)
    // {
    //     Sales_data total(*bgit);
    //     decltype(bgit) endit = bgit + 1;
    //     while ((endit = find(endit, soldMsg.cend(), *bgit)) != soldMsg.cend())
    //     {
    //         total = accumulate(endit, endit + 1, total);
    //         bgit = endit;
    //         ++endit;
    //     }
    //     out_iter = total;
    // }

    // the second resolution: use find_if_not and accumulate -- succeed
    for(auto bgit = soldMsg.cbegin(); bgit != soldMsg.cend(); )
    {
        Sales_data total(bgit->isbn());
        decltype(bgit) endit = find_if_not(bgit + 1, soldMsg.cend(), 
                [bgit] (const Sales_data &rhs) {    return rhs.isbn() == bgit->isbn();  });
        
        if(endit == bgit + 1)
            total = *bgit;
        else
            total = accumulate(bgit, endit, total);
        
        out_iter = total;
        bgit = endit;
    }

    ifs.close();
}

void exercise_10_33(int argc, char **argv)
{
    if(argc != 4)
    {
        cerr << "Must input three file directory." << endl;
        return;
    }

    ifstream ifs(argv[1]);
    ofstream oddfile(argv[2], ios::app), evenfile(argv[3], ios::app);
    if(!ifs || !oddfile || !evenfile)
    {
        cerr << "Sorry, cannot open file." << endl;
        return;
    }

    istream_iterator<int> int_iter(ifs), eof;
    ostream_iterator<int> odditer(oddfile, " "), eveniter(evenfile, "\n");
    while (int_iter != eof)
    {
        int elem = *int_iter++;
        if(elem & 1)
            odditer = elem;
        else
            eveniter = elem;    
    }
    
    evenfile.close();
    oddfile.close();
    ifs.close();
}

void exercise_10_34_35()
{
    srand(static_cast<unsigned>(time(NULL)));
    vector<int> ivec;
    for (size_t i = 0; i < 8; i++)
    {
        ivec.push_back(rand() % 50);
    }
    print(ivec);
    for(auto riter = ivec.crbegin(); riter != ivec.crend(); ++riter)
        cout << *riter << " ";
    cout << endl;

    // exercise_10_35
    for(auto bgit = ivec.cend() - 1; bgit >= ivec.cbegin(); --bgit)
        cout << *bgit << " ";
    cout << endl;
}

void exercise_10_36()
{
    list<int> ilst;
    Input(cin, ilst);
    auto lastZeroIter = find(ilst.crbegin(), ilst.crend(), 0);
    print(lastZeroIter.base(), ilst.cend());
    lastZeroIter++;
    auto aimit = lastZeroIter.base();
    int pos = 1;
    for(auto it = ilst.cbegin(); it != aimit; ++it, ++pos);
    if(pos >= ilst.size())
        cout << "In the sequence ilst don't have any zero." << endl;
    else
        cout << "The last zero is in the " << pos << " position." << endl;

    // use normal iterator
    auto curit = ilst.cbegin(), previt = ilst.cend();
    while ((curit = find(curit, ilst.cend(), 0)) != ilst.cend())
    {
        previt = curit;
        ++curit;
    }
    if(previt != ilst.cend())   // 必须要考虑清楚极限情况到底怎么判断
    {
        int pos = 1;
        for(auto it = ilst.cbegin(); it != previt; ++it, ++pos);
        cout << "The last zero is in the "
             << pos << " position." << endl;
    }
    else
        cout << "In the sequence don't find any zero." << endl;
}

void exercise_10_37()
{
    vector<int> ivec;
    randInitCon(ivec, 10);
    list<int> ilst;
    // copy(ivec.cbegin() + 2, ivec.cbegin() + 7, ilst.rbegin());

    // normal_iterator and reverse_iterator can convert to each other
    // 正向思考，将普通迭代器的范围转化为反向迭代器的范围
    // vector<int>::reverse_iterator re(ivec.begin() + 2); // the second position
    // vector<int>::reverse_iterator rb(ivec.begin() + 7); // the seventh position
    // copy(rb, re, back_inserter(ilst));

    // 逆向思考，直接计算反向迭代器的起始与终止位置
    auto rbgit = ivec.crbegin() + ivec.size() - 7,
         redit = ivec.crbegin() + ivec.size() - 3 + 1;
    copy(rbgit, redit, back_inserter(ilst));
    cout << "ivec's sequence: " << endl;
    print(ivec);
    cout << "ilst's sequence: " << endl;
    print(ilst);
}

// exercise_10_38
// 1. Input Iterator: * put in the right of assignment expression; ++; ==/!=; 只读不写，单向扫描
// 2. Output Iterator:* put in the left of assignment expression; ++; ==/!=; 只写不读，单向扫描
// 3. Forward Iterator: *; ++; ==/!=; 可读可写，单向移动，多遍扫描
// 4. Bidirectional Iterator: *; ++; --; ==/!=; 可读可写；双向移动，多遍扫描
// 5. RandomAccess Iterator: *; ++; --; ==/!=; </<=/>/>=; 算术运算 iter + n; iter - n; +=; -=; iter1 - iter2; []
// 可读可写；双向移动；多遍扫描，可以随机访问
// 少考虑一种迭代器运算，operator->, 迭代器类似于指针，可以使用->访问成员

// exercise_10_39
// list的迭代器属于Bidirectional Iterator, vector's iterator belong RandomAccess Iterator

// exercise_10_40, algorithm use what kind of iterator rely on specific implement
// copy's前两个迭代器参数只需要时input iterator即可，第三个参数至少需要时output iterator
// reverse需要使用Bidirectional iterator
// unique至少需要使用forward iterator

// exercise_10_41
// replace(beg, end, old_val, new_val): 将[beg, end)范围内所有的old_val都替换成new_val
// replace_if(beg, end, pred, new_val): 将[beg, end)所有使一元谓词pred返回true的都替换成new_val
// replace_copy(beg, end, dest, old_val, new_val): 将[beg, end)中的元素都复制到dest指向的容器中，其中所有old_val用new_val复制
// replace_copy_if(beg, end, dest, pred, new_val): 将[beg, end)中的元素都复制到dest指向的容器中，其中所有使pred返回true的都用new_val复制

void exercise_10_42()
{
    list<string> slst;
    Input(cin, slst);
    elimDups(slst);
}

int main(int argc, char *argv[])
{
    // exercise_10_1(argc, argv);
    // exercise_10_2();
    // exercise_10_4();
    // exercise_10_5();
    // exercise_10_6();
    // exercise_10_7();
    // exercise_10_9();
    // exercise_10_12();
    // exercise_10_13();
    // exercise_10_14();
    // exercise_10_15(argc, argv);
    // exercise_10_20();
    // exercise_10_21();
    // exercise_10_22();=
    // exercise_10_24();
    // exercise_10_27();
    // exercise_10_28();
    // exercise_10_29();
    // exercise_10_30();
    // exercise_10_32();
    // exercise_10_33(argc, argv);
    // exercise_10_34_35();
    // exercise_10_36();
    exercise_10_37();
    // exercise_10_42();

    return 0;
}