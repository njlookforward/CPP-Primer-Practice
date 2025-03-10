#include <fstream>
#include <cstring>
#include <cctype>
#include "strBlob.hpp"
#include "exercise.hpp"
#include "TextQuery.hpp"
#include "QueryResult.hpp"   

using namespace std;

void exercise_12_1()
{
    // 最后b1 and b2 have 4 elements
    strBlob b1;
    {
        strBlob b2{"a", "an", "the"};
        b1 = b2;
        b2.push_back("about");
        cout << b1.size() << endl
             << "b2.size = " << b2.size() << endl;
    }

    const strBlob cb1{"nanjiang", "tianjin"};
    cout << cb1 << endl;
    // auto &fir = cb1.front();    // 因为用引用赋值会过滤掉引用运算符
    // fir = "NanJiang";
    cout << cb1 << endl;
}

// exercise_12_2 is strBlob.hpp and strBlob.cpp
// exercise_12_3
// StrBlob doesn't need const-edition pop_back() and push_back(string) because pop_back and push_back
// will change vector, const-edition's aim is to only read data not write data.

// exercise_12_4
// i是作为下标索引，因此有效值的范围是[0, size()), 因此此时的检查条件已经够用了，i肯定小于size
// check是私有成员函数，因此只会被成员函数调用，可以保证传递给他的参数符合要求

// exercise_12_5
// 单个参数的构造函数是一种隐式类型转换，有时会造成干扰，因此定义为显式构造函数，只有明确调用单个参数的构造函数时
// 才能创建对象
// 采用隐式类型转换构造函数的优点是方便书写，尤其是使用赋值运算符，缺点是不清晰，可能造成不经意的类型转换
// 没有定义一个接受列表参数的显示构造函数，说明可以进行列表参数向strBlob的隐式转换，意味着在需要strBlob参数的地方（如函数参数，返回值） 
// 可以用列表替代，可以用拷贝形式进行初始化（赋值），程序的编写更加简单方便；但是隐式类类型转换也有不方便之处，如列表中存在不合法参数
// 用列表参数传递给函数strBlob参数，会创建临时strBlob对象，函数结束后，strBlob被销毁，丢失数据，这时采用显式构造函数能够避免这类问题

void exercise_12_6()
{
    auto pv = allocVec();
    readToVec(cin, pv);
    display(cout, pv) << endl;

    // 直接动态内存管理要求谁申请动态内存谁就负责释放，此时是主函数应该负责
    delete pv;
    pv = nullptr;
}

void exercise_12_7()
{
    auto pv = allocSmart();
    readToVec(cin, pv);
    display(cout, pv) << endl;
}

// exercise_12_8
// 肯定是有问题的，情况一：中间过程处理了动态分配的指针p，p = nullptr, return false
// circumstance two: process dynamic pointer, but p isn't assigned nullptr, return true
// circumstance three: don't process dynamic pointer, return true, but lose pointer cause memory leak
// circumstance four: new fail, throw exception bad_alloc

void exercise_12_9()
{
    int *q = new int(42), *r = new int(100);
    r = q;
    // result memory leak, r's original pointer lose
    auto q2 = make_shared<int>(42), r2 = make_shared<int>(100);
    r2 = q2;
    // all is right, r2 automatically free memory, and then point q2's address
}

// exercise_12_10
// shared_ptr<int> p(new int(42));
// process(shared_ptr<int>(p)); // 这是一个临时的拷贝构造函数
// invoke process is right because using shared_ptr not a normal pointer

// exercise_12_11
// process(shared_ptr<int>(p.get()));
// when process come to end will free p's normal pointer, p will become a dangling pointer

// exercise_12_12
// auto p = new int();
// auto sp = make_shared<int>();
// (a) process(sp); process sp's duplication, is right
// (b) process(new int());  conversion from int* to shared_ptr<int> is error
// (c) process(p); conversion from int* to shared_ptr is error
// (d) process(shared_ptr<int>(p)); is error because normal pointer is the first time to bind to smart pointer
// when process come to end will destory p point space, p will become a dangling pointer

// exercise_12_13
// sp will become a dangling pointer. so don't mangle using smart pointer and normal pointer

// exercise_12_14_15 is prog5_shared_ptr_delete

// exercise_12_16
// if copy or assign unique_ptr, compiler will give error information as follow:
// std::unqiue_ptr<>(const unique_ptr<> &) = delete;
// unique_ptr<> &operator=(const unique_ptr<> &) = delete;

// exercise_12_17
// int ix = 1024, *pi = &ix, *pi2 = new int(2048);
// typedef unique_ptr<int> IntP;
// (a) IntP p0(ix); // error, ix is a local variable not a pointer
// (b) IntP p1(pi); // error, pi don't point free space
// (c) IntP p2(pi2); // right
// (d) IntP p3(&ix); // error, 不是new产生的
// (e) IntP p4(new int(2048));  // right
// (f) IntP p5(p2.get());   // error, 不能用get()返回的指针构造新的智能指针对象，应该是IntP p5(p2.release());

// exercise_12_18
// unique_ptr是独享所绑定的动态内存，所以通过使用release将堆空间的指针的控制权转移给其他的智能指针
// 而shared_ptr是共享所绑定的动态内存指针，一旦交出控制权，这个控制权不是唯一的，若用这个指针重新构造智能指针的对象
// 会和其他的共享shared_ptr发生冲突，即使自己管理这个指针，同样在发生冲突，因为控制权都不是唯一的
// shared_ptr是共享资源，只需要进行简单地拷贝或复制，不需要转移控制权

void exercise_12_19()
{
    strBlob sb{"nanjiang", "is", "practising", "C++", "smart", "pointers"};
    for(strBlobPtr bgit = sb.begin(); BlobNoEqual(bgit, sb.end()); ++bgit)
        cout << *bgit << " ";
    cout << endl;
}

void exercise_12_20(int argc, char *argv[])
{
    checkargc(argc, 2);
    ifstream infile;
    openinfile(infile, argv[1]);
    // 智能指针的作用，可以将任何需要进行资源管理的对象的指针交给智能指针进行保管
    shared_ptr<ifstream> pfs(&infile, [](ifstream *pfs) {   pfs->close(); });

    strBlob fileContent;
    string line;
    while (getline(*pfs, line))
    {
        fileContent.push_back(line);
    }
    
    strBlobPtr psb = fileContent.begin();
    for (size_t i = 0; i < fileContent.size(); i++)
    {
        cout << *psb << endl;
        ++psb;
    }
    cout << endl;
}

// exercise_12_21
// std::string &operator*()
// {    return (*check("dereference past end."))[_pos]; }
// 我认为还是分开写比较好，都是一个逻辑，分开的话更清晰，更易阅读， 而不是为了炫技

void exercise_12_22()
{
    const strBlob sb{"nanjiang", "is", "practising", "C++", "smart", "pointers"};
    strBlobPtr psb(sb, 3);
    strBlob sb2{"Beijing", "Tianjin"};
    strBlobPtr psb2(sb2, 1);

    ConstStrBlobPtr csb(sb, 3);
    cout << *csb << " " << *++csb << endl;
}

void exercise_12_23(int argc, char *argv[])
{
    checkargc(argc, 3);
    char *ps = new char[50]();
    strcpy(ps, argv[1]);
    strcat(ps, argv[2]);

    cout << argv[1] << " + " << argv[2]
         << " = " << ps << endl;
    delete [] ps;

    cout << "catch two string: " << endl;
    string s1 = argv[1], s2 = argv[2];
    string *pstr = new string();
    *pstr += s1;
    *pstr += s2;
    cout << s1 << " + " << s2
         << " = " << *pstr << endl;
}

void exercise_12_24()
{
    // 问题：我不确定能否使用cin >> char*, 编写代码尝试一下
    // 逻辑是：需要读取一个字符串，然后放入动态申请的字符数组中，可以根据输入的字符串长度变长数组
    // 初期：一个固定数组 -- get（）一个字符一个字符的读取-》一旦超出 重新申请
    // 首先，我目前的问题是，要用' ' or '\n' as delim, 先用'\n'吧，更清晰一些
    int len = 10;
    char *pca = new char[len]();
    cin.get(pca, len);
    while (cin.peek() != '\n' && cin.peek() != char_traits<char>::eof())
    {
        // 说明仍然还有字符需要读取
        pca = increTwice(pca, len);
        cin.get((pca + len / 2 - 1), len / 2 + 1);
    }
    cout << "Eventually, the result is: " << endl
         << pca << endl;
    
    delete [] pca;  // 的确是太容易忘记回收内存了
}

void exercise_12_24_answer()
{
    // when delim is '\n', use cin.get(char*, count) is better,
    // but when delim is ' ', use cin.get(char*, count, ' '), need to use cin.ignore(1) to eliminate ' '
    // use cin.get(char) is better
    int len = 10;
    char *pc = new char[len]();
    int curLen = 0;
    char tmp;
    while(cin.get(tmp))
    {
        if(isspace(tmp))
        {
            // 读取的字符是空白字符，' ' '\t' '\n' and so on
            break;
        }

        pc[curLen++] = tmp;
        if(curLen == len - 1)
        {
            // come to end of dynamic array, need judge the next character in the io is space character or eof
            auto nextChar = cin.peek();
            if(isspace(nextChar) || nextChar == char_traits<char>::eof())
            {
                // next character is space character or eof
                break;
            }
            pc = increTwice(pc, len);
        }
    }
    pc[curLen] = '\0';

    cout << "Eventually, the result is " << endl
         << pc << endl;

    delete [] pc;
}

// exercise_12_25
// delete [] pa;

void exercise_12_26()
{
    allocator<string> allocStr;
    auto const ps = allocStr.allocate(8);
    auto qs = ps;
    string stmp;
    while(cin >> stmp && qs != ps + 8)
    {
        allocStr.construct(qs++, stmp);
    }

    size_t size = qs - ps;
    for (size_t i = 0; i < size; i++)
    {
        cout << ps[i] << " ";
    }
    cout << endl;

    while (qs != ps)
    {
        allocStr.destroy(--qs);
    }
    allocStr.deallocate(ps, 8);
}

// exercise_12_27 编写自己版本的TextQuery and QueryResult
// exercise_12_28 不用设计类，而是通过各种函数来设计文本查询程序

void exercise_12_29(int argc, char *argv[])
{
    checkargc(argc, 2);
    ifstream infile;
    openinfile(infile, argv[1]);
    shared_ptr<ifstream> pf(&infile, [] (ifstream *pf) {    pf->close();    });

    TextQuery tq(infile);
    do {
        cout << "Please input a word to query or 'q' to exit: ";
        string word;
        if(!(cin >> word) || word == "q")
            break;
        
        cout << tq.query(word) << endl;
    } while(true);
    // 我不倾向于使用哪个版本，while 和 do_while都挺好用的，只不过while使用的次数更多一些
    // 而且do_while是先进行一次循环再去判断，两者的逻辑有一些不同，因此还是按照逻辑进行选择
}

// exercise_12_30 is prog10_textquery

// exercise_12_31
// 如果用vector代替set保存出现的行号，会出现差别。首先因为扫描文本是从上往下逐行提取字符串，因此添加行号的操作在vector
// 中只需用push_back就可以保证行号的有序；但是vector无法从数据结构上自行保证行号无重复，需要程序员自己判断保证行号的唯一
// 其他的使用行号集合的操作，vector和set是一样的
// 我更倾向于使用set，因为set在底层数据结构上保证了添加的行号的有序和唯一，更加便捷
// 讨论性能上的优异应该从时间复杂度和空间复杂度的角度去考虑，set的底层实现是红黑树，时间复杂度是log2n
// vector的时间复杂度是常量，因此vector的性能更优

int main(int argc, char *argv[])
{
    // exercise_12_1();
    // exercise_12_6();
    // exercise_12_7();
    // exercise_12_9();
    exercise_12_19();
    // exercise_12_20(argc, argv);
    // exercise_12_22();
    // exercise_12_23(argc, argv);
    // exercise_12_24();
    // exercise_12_24_answer();
    // exercise_12_26();
    // exercise_12_29(argc, argv);

    return 0;
}