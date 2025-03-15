#include <tuple>
#include <cstddef>
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include <bitset>
#include <regex>
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
    // bool is_set = bitvec.any();         // true
    // bool is_not_set = bitvec.none();    // false
    // bool is_all_set = bitvec.all();     // false
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
    // 查找不在c之后的非法"ei"子串
    string pattern("[^c]ei");
    // regular expression include integral word including substr
    pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";    // *表示0个或多个
    regex r(pattern, regex::icase);
    string test_string("receipt freind theif receive");
    smatch results;
    if(regex_search(test_string, results, r))
        cout << results.str() << endl;
    for(sregex_iterator bgit(test_string.cbegin(), test_string.cend(), r), edit;
        bgit != edit; ++bgit)
        cout << bgit->str() << endl;
}

void prog7_regex_icase(int argc, char **argv)
{
    checkArgs(argc, 2);
    ifstream infile;
    openInputFile(infile, argv[1]);
    shared_ptr<ifstream> pfile(&infile, [](ifstream *pf) { pf->close(); });
    
    try{
        // 注意输入序列是输入序列，不要与正则表达式的字符串表达弄混
        regex re("([[:alnum:]]+)\\.(cpp|cxx|cc)$", regex::icase); // $是表示子表达式的意思吗
        smatch results;
        string filename;
        while (infile >> filename)
        {
            if(regex_search(filename, results, re))
                cout << results.str(0) << " " << results.str(1) << endl;
        }

        cmatch cres;
        if(regex_search("myfile.cc", cres, re))
            cout << cres.str() << endl;
    } catch(regex_error e)
    {   cerr << e.what() << "\ncode: " << e.code() << endl; }
}

void prog8_regex_ssubmatch(int argc, char **argv)
{
    checkArgs(argc, 2);
    ifstream infile;
    openInputFile(infile, argv[1]);
    shared_ptr<ifstream> pfile(&infile, [](ifstream *pf) { pf->close(); });

    string file;
    char ch;
    while (infile.get(ch))
    {
        file.push_back(ch);
    }
    
    string pattern("[^c]ei");
    pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
    regex re(pattern, regex::icase);
    for(sregex_iterator bgit(file.begin(), file.end(), re), edit;
        bgit != edit; ++bgit)
    {
        if(bgit->str() == "albeit" || bgit->str() == "neighbor")
            continue;

        auto pos = bgit->prefix().length();
        pos = pos > 40 ? (pos - 40) : 0;
        cout << bgit->prefix().str().substr(pos)
             << "\n\t\t>>> " << bgit->str() << " <<<\n"
             << bgit->suffix().str().substr(0, 40)
             << endl;
    }
}

void prog9_regex_submatch(int argc, char **argv)
{
    checkArgs(argc, 2);
    ifstream infile;
    openInputFile(infile, argv[1]);
    shared_ptr<ifstream> pfile(&infile, [](ifstream *pf) { pf->close(); });

    string phone("(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ])?(\\d{4})");
    regex re(phone);
    smatch results;
    string phoneMsgSet;
    char ch;
    while (infile.get(ch))
    {
        phoneMsgSet.push_back(ch);
    }
    for(sregex_iterator bgit(phoneMsgSet.begin(), phoneMsgSet.end(), re), edit;
        bgit != edit; ++bgit)
    {
        if(phoneValid(*bgit))
        {
            cout << bgit->str() << endl;
        } else {
            cout << "this is an invalid phone number: "
                 << bgit->str() << endl;
        }
    }
}

void prog10_regex_replace()
{
    string phone("(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ])?(\\d{4})");
    regex re(phone);

    string fmt("$2.$5.$7");
    string number("(908) 555-1800");
    cout << regex_replace(number, re, fmt) << endl;
}

void prog11_regex_replace(int argc, char **argv)
{
    checkArgs(argc, 2);
    // fstream file("..\\..\\..\\data\\phones", ios::ate | ios::in | ios::out);
    fstream file(argv[1], ios::in | ios::out | ios::ate);
    if(!file)
    {
        cerr << "Sorry, cannot open " << argv[1] << endl;
        exit(-1);
    }
    shared_ptr<fstream> pfile(&file, [](fstream *pf) { pf->close(); });

    string phone("(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ])?(\\d{4})");
    regex re(phone);

    string fmt("$2.$5.$7");
    string fmt2("$2.$5.$7 ");
    string line;
    file.seekg(0, ios::beg);
    while (getline(file, line))
    {
        cout << regex_replace(line, re, fmt2, regex_constants::format_no_copy) << endl;
    }
    
    // 我一次性读取所有的内容，然后再追加到文件的末尾不就得了
    // Bug: 的确应该一次性读取整个文件的内容，然后进行处理，处理结束后再追加到文件末尾
    // 如果是一行一行的处理，刚开始时origin_end = 97,不断追加之后读取完第三行, curpos = 99，永远会陷入死循环
    // iostream的底层操作的确是很容易发生错误，尽量一次性进行处理，一次性处理是最优选择，可以保留文本中的所有换行符
    // string contents;
    // contents.resize(file.tellg());
    // file.seekg(0, fstream::beg);
    // file.read(&contents[0], contents.size());

    // file.seekp(0, fstream::end);
    // file << regex_replace(contents, re, fmt);

    // 我再次尝试一下，是不是跟我每次使用endl有关系啊，不加endl会不会成功呢,只要加上换行就会进入死循环
    // 因此不能使用getline，应该使用file.get()，读取文件本身自己的换行符
    // Bug: line是空串，传入他的第一个元素的指针是错误的，因此必须先为line申请内存空间
    // string line;
    // auto origin_end = file.tellg();
    // file.seekg(0, ios::beg);
    // auto curpos = file.tellg();
    // while (curpos != origin_end && getline(file, line))
    // {
    //     // 因为geiline会丢掉'\n'，因此不会换行的
    //     // line.push_back('\n');
    //     // 要是对流进行无格式操作，那么中间尽量不能有自己的格式操作，尤其是'\n'，我认为应该跟windowsOS有关系
    //     // Bug: 最后的我放弃自己加'\n'的操作了，应该是除了'\n'字符以外，添加其他字符像空格是没有问题的
    //     curpos = file.tellg();
    //     file.seekp(0, ios::end);
    //     // Bug: 只要加入换行，就会进入死循环
    //     file << regex_replace(line, re, fmt);
    //     file.seekg(curpos);
    // }
}

int main(int argc, char **argv)
{
    // prog1_tuple();
    // prog2_tuple_bookstores(argc, argv);
    // prog3_bitset();
    // prog4_bitset_operation();
    // prog5_bitset_quiz();
    // prog6_regex();
    // prog7_regex_icase(argc, argv);
    // prog8_regex_ssubmatch(argc, argv);
    // prog9_regex_submatch(argc, argv);
    // prog10_regex_replace();
    prog11_regex_replace(argc, argv);

    return 0;
}