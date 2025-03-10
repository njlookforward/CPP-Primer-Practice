#include "std_forward.hpp"
#include "exercise.hpp"
#include "Sales_data.hpp"
#include "BlobPtr.hpp"
#include "TextQuery.hpp"
#include <vector>
#include <memory>
#include <unordered_set>
using namespace std;

void prog1_forward()
{
    int i = 24;
    auto uqptr1 = make_unique1<A>(i);
    auto uqptr2 = make_unique1<A>(25);

    cout << "B\n";
    auto uqptr3 = make_unique2<B>(i, 26, 42);
}

void prog2_template()
{
    cout << compare(1, 0) << endl
         << compare<4, 4>("nan", "nan") << endl // Bug1:重载函数发生二义性，两种模版函数都可以，因此显示实例化解决冲突
         << compare(1.2, 3.56) << endl;
    vector<int> vec1{1, 2, 3}, vec2{4, 5, 6};
    cout << compare(vec1, vec2) << endl;
    cout << compare("hi", "mom") << endl;
    // compare对模板类型参数是有要求的，必须定义operator<
    // Sales_data data1("0-201-70353-X", 4, 50), 
    //            data2("0-201-82470-1", 4, 45.39);
    // cout << compare(data1, data2) << endl; // Bug2: 由于Sales_data定义了类型转换运算符，所以隐式的进行了类型转换
    // 我认为这是在编译期进行判断，而不是运行期，我的猜测是正确的
    
}

void prog3_Blob(int argc, char **argv)
{
    Blob<int> squares = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    // BlobPtr<int> first(squares, 0),
    //              last(squares, squares.size());
    // for(; first != last; first++)
    // {
    //     *first = (*first) * (*first);
    //     cout << *first << " ";
    // }
    // cout << endl;

    for(auto bgit = squares.begin(); bgit != squares.end(); ++bgit)
    {
        *bgit *= *bgit;
        cout << *bgit << " ";
    }
    cout << endl;

    Blob<string> words;
    checkArgs(argc, 2);
    ifstream infile;
    OpenInputFile(infile, argv[1]);

    string word;
    while (infile >> word)
    {
        words.push_back(word);
    }

    for(std::size_t i = 0; i < words.size(); ++i)
    {
        words[i] += "s";
        cout << words[i] << " ";
    }
    
    words.pop_back();

    infile.close();

}

void prog4_template_alias()
{
    typedef Blob<string> strBlob;
    
    Twin<int> win_loss;
    Twin<double> area;
    Twin<string> authors;
    partNo<string> books;

    Foo<int> fi;
    auto ct = Foo<int>::count();
    ct = fi.count();
}

void prog5_template_parameter(int argc, char **argv)
{
    checkArgs(argc, 2);
    ifstream infile;
    OpenInputFile(infile, argv[1]);
    shared_ptr<ifstream> pfile(&infile, [](ifstream *pf){   pf->close();    });

    vector<int> ivec;
    cout << "before input, top is " << top(ivec) << endl;
    ReadIntoContainer(infile, ivec);
    cout << "after input, top is " << top(ivec) << endl;

    cout << compare_v2(ivec[0], ivec[1]) << endl
         << compare_v2(ivec[0], ivec[2]) << endl
         << compare_v2(ivec[7], ivec[9]) << endl;
    Sales_data item1(cin), item2(cin);
    cout << compare_v2(item1, item2, compareIsbn) << endl;

    Numbers<> average_precision(25);    // 空的模板参数说明我们想要使用默认模板参数
    Numbers<long double> precision(3.1425);
}

void prog6_member_template()
{
    auto pi = new int(24);
    DebugDelete deleter;
    deleter(pi);
    auto ps = new string("nanjiang");
    deleter(ps);
    auto pd = new double(3.1415);
    DebugDelete()(pd);

    // because DebugDelete can free pointer, so DebugDelete can as unique_ptr's Deleter
    // 对于unique_ptr, 第二个模板参数是删除器的类型，因此定义对象时的构造函数应该传入一个删除器类型的对象
    // 不管是临时对象也好，还是局部对象也好，用来赋值给构造函数的形参，就像一般的内置类型参数一样，不要迷茫
    // DebugDelete只是函数对象而已，慢慢习惯就好
    unique_ptr<string, DebugDelete> upstr(new string("nan"), DebugDelete(cout));
    // 而且此时成员模板是在unique_ptr调用析构函数时，才会进行实例化函数调用运算符

    const char* carr[] = {"hello", "world", "hi", "now", "how"};
    Blob<string> words(begin(carr), end(carr));
    BlobPtr<string> bg(words), ed(words, words.size());
    for(; bg != ed; ++bg)
        cout << *bg << " ";
    cout << endl;
}

void prog7_textquery(int argc, char *argv[])
{
    checkArgs(argc, 2);
    ifstream inputfile;
    OpenInputFile(inputfile, argv[1]);
    shared_ptr<ifstream> pf(&inputfile, [](ifstream *pf) {  pf->close();    });

    TextQuery tq(inputfile);
    while (true)
    {
        cout << "Please input a word which you want to query in the text or 'q' to exit this name: ";
        string word;
        if(!(cin >> word) || word == "q")
            break;
        QueryResult qr = tq.query(word);
        cout << qr << endl;
    }
}

void prog8_argument_deduction()
{
    string s1("a value");
    const string s2("another value");

    auto res = fobj(s1, s2);
    auto res2 = fref(s1, s2);

    int a[10] = {}, b[42] = {};
    auto res3 = fobj(a, b);
    // auto res4 = fref(a, b);

    long lng = 1024;
    cout << compare<long>(lng, 1024);

    vector<int> ivec{1, 2, 3, 4, 5};
    Blob<string> svec = {"hi", "bye"};

    cout << fcn2(ivec.begin(), ivec.end()) << endl
         << fcn2(svec.begin(), svec.end()) << endl;

    int (*pf1)(const int&, const int&) = compare;
    cout << pf1(12, 45) << endl;

    func(compare<string>);
}

void prog9_move()
{
    string s1("hi!"), s2;
    s2 = std::move(string("bye!"));
    cout << s2 << endl;
    s2 = std::move(s1);
    cout << s1 << " " << s2 << endl;

    int j = 24;
    flip(f, j, 42);
    flip(g, j, 42);
}

void prog10_template_overload()
{
    string s("hi!");
    cout << debug_rep(s) << endl
         << debug_rep(&s) << endl;
    // Bug: 没有发生任何问题，但是很有意思的是，在指针参数的函数模板中调用string&参数的debug_rep
    // 竟然使用的模板函数的debug_rep, 而不是非模板函数，我认为可能是调用的是debug_rep<string>(const string&)
    
    const string *csp = &s;
    cout << debug_rep(csp) << endl;

    const double cd = 3.14234;
    cout << debug_rep(cd) << endl
         << debug_rep(&cd) << endl;

    // 两个模板函数都是精确匹配，但是对于数组来说，指针类型更加特例化，因此会选择指针类型参数的函数
    // 我认为数组类型作为参数传入到函数形参中，会直接进行类型转换，因此指针类型数组更加特例化
    // 记住这个特性就好，没有什么特别的
    cout << debug_rep("hi world!") << endl;
    char carr[] = "abcd";
    cout << debug_rep(carr) << endl;
    // 在非模板函数中调用同名重载函数，会优先调用非模板函数
}

void prog11_variadic_template()
{
    int i = 24;
    float f = 1234.454;
    double d = 3.14345565;
    string s = "how now brown cow";
    foo(i, s, 42, d);
    foo(s, 42, "hi");
    foo(d, s);
    foo("hi");

    print(cout, i, f, d, s, 42) << endl;
    print(cout, s, 42, "hi") << endl;
    print(cout, d, s) << endl;
    print(cout, "hi") << endl;

    errorMsg(cout, i, f, d, s, 42);
}

void prog12_template_specialization(int argc, char **argv)
{
    checkArgs(argc, 2);
    ifstream infile;
    OpenInputFile(infile, argv[1]);
    shared_ptr<ifstream> pfile(&infile, [](ifstream *pf) { pf->close(); });

    const char *p1 = "hi", *p2 = "mom";
    cout << compare(p1, p2);

    unordered_multiset<Sales_data> SDset;
    Sales_data item;
    while (infile >> item)
    {
        SDset.insert(item);
    }
    for (const auto &v : SDset)
    {
        cout << v << endl;
    }

    int i = 24;
    my_remove_reference<decltype(42)>::type a;
    my_remove_reference<decltype((i))>::type b;
    my_remove_reference<decltype(std::move(i))>::type c;

    // 同样可以特例化类模板中的成员
}

int main(int argc, char **argv)
{
    // prog1_forward();
    // prog2_template();
    // prog3_Blob(argc, argv);
    // prog4_template_alias();
    // prog5_template_parameter(argc, argv);
    // prog6_member_template();
    // prog7_textquery(argc, argv);
    // prog8_argument_deduction();
    // prog9_move();
    prog10_template_overload();
    // prog11_variadic_template();
    // prog12_template_specialization(argc, argv);

    return 0;
}

// Bug1:重载函数发生二义性，两种模版函数都可以，因此显示实例化解决冲突
// ****Bug2: 由于Sales_data定义了类型转换运算符，所以隐式的进行了类型转换，调试过程中发现是compare(double, double)
// Sales_data转换成了double，仅此尽管Sales_data没有定义operator<，仍然可以使用compare
// 这次的错误出现的很好，说明不能轻易地定义类型转换运算符，否则有时候会出现意想不到的问题，要定义也要定义显示类型转换运算符
// 内置类型的转换优先级高于类类型。因为内置类型的小于运算符是编译器的原生支持比较操作；而类类型string的比较操作
// 需要调用用户定义的operator<，会引入额外的函数调用开销
// Bug3: 竟然没有给iter赋值，又犯马虎了
// Bug4：又是逻辑问题，竟然把exit单独放在if的外面，这不是永远结束进程吗，可恶啊，这种失误浪费了太多的时间

// Bug5:因为定义iarr[ivec.size()]，定义数组大小应该用常量表达式，这样在编译期就能知道数组的大小
// 但是我采用的是ivec.size()，这是到运行期才能知道数组的大小，然而函数模板是在编译期进行实例化
// 因此编译器在编译期阶段无法自行推断传入的数组参数的大小，因此就无法实例化，因此报错
// Bug6:模板函数的定义必须放在头文件中，包括定义类模板的类型别名也要放在头文件中
// Bug7: template<typename> class C，这是模板；但是一旦定义template<typename> class C<T>这就不是模板了，
// 只要一加上<T>就是一个类类型，因此模板与类类型要分清楚   
// Bug8：要与实例化的函数模板一对一友元，需要特别指出函数模板实例化
// Bug9: 不要重定义自定义类型，class DebugDelete
// Bug: 出现链接错误，凡是定义在头文件中的函数，必须定义为inline，否则的话会出现重定义问题，而函数模板是默认inline函数的