#include "exercise.hpp"
#include "mydate.hpp"
#include <limits>

void exercise_9_1()
{
/* (a) 要按照字典序进行插入操作，最好使用list，由于是固定数量，如果后面要进行多次访问，可以在拷贝到一个vector中；
    或者在一开始时总是插入到vector的末尾，单词全部插入后，在按照字典序进行排序
 * (b) 在末尾插入，在头部删除，最好用是deque
 * (c) 可以使用vector或者deque。因为都可以总在末尾插入新的整数，最后进行排序。
*/
}

void exercise_9_2()
{
    list<deque<int> > deqList;
    // 这个容器如何使用呢，按照元素类型来一点点拆解，再一点点组装，元素类型是deque
    deque<int> ideqTmp;
    int cnt = 0, threshold = 10;
    for (size_t i = 0; i < 5; i++)
    {
        for (; cnt < threshold; ++cnt)
        {
            ideqTmp.push_back(cnt);
        }
        deqList.push_back(ideqTmp);
        ideqTmp.clear();
        threshold += 10;
    }
    for (const auto &deq : deqList)
    {
        for (const auto &elem : deq)
        {
            cout << elem << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// exercise_9_3
// 构成迭代器范围的迭代器必须是同一容器范围内的元素，包括尾后迭代器，其他范围内是非法的
// 而且对begin进行递增操作可以到达end，即end不能在begin之前

void exercise_9_4()
{
    vector<int> ivec;
    srand(static_cast<unsigned>(time(NULL)));   // 生成随机数种子
    for (size_t i = 0; i < 10; ++i)
    {
        ivec.push_back(rand() % 20);
    }
    for (auto &&i : ivec)
    {
        cout << i << " ";
    }
    cout << endl
         << "Please input a number to guess any element in the ivector: ";
    int elem;
    cin >> elem;
    cout << elem << (find_v1(ivec.cbegin(), ivec.cend(), elem) ? " is " : " is not ")
         << "the element of vector." << endl;

    auto aimIter = find_v2(ivec.cbegin(), ivec.cend(), elem);
    cout << endl << elem
         << (aimIter != ivec.cend() ? " is " : " is not ")
         << "the element of vector." << endl;
}

// exercise_9_6
// 程序的问题应该是while (iter1 < iter2), 但是具体问题我不确定，我认为可能是容器类型是list
// 注意容器是容器，容器的迭代器是迭代器，不要混淆，与vector和deque不同，list的迭代器不支持<运算符
// list的迭代器只支持++ -- == !=，因为可以把迭代器类比成指针，不同容器的底层数据结构实现不同
// vector与deque是连续存储，而list是随机存储，用指针相连，因此vector与deque的迭代器通过地址可以比较得到大小关系
// 但是list的迭代器就没有大小关系了

// exercise_9_7
// 为了索引vector中的元素，应该使用vector<int>::size_type,作为下标索引
// 或者使用vector<int>::iterator迭代器进行索引
// exercise_9_8
// 若是读取list<string>中的元素，应该使用list<string>::value_type类型
// 要是写入list，应该使用list<string>::reference类型
// exercise_9_9
// begin()是重载成员函数，仅当调用对象是const时返回的是const_iterator，否则返回的是iterator
// cbegin()无论调用对象是否为const，都返回const_iterator
// exercise_9_10
// it1 -> vector<int>::iterator     it2 -> vector<int>::const_iterator
// it3 it4 -> vector<int>::const_iterator

void exercise_9_11()
{
    // 有6种创建和初始化顺序容器的方法，每一种给出一种实例
    vector<int> ivec1;  // 容器为空
    vector<int> ivec2{1, 1, 2, 3, 5, 8, 13, 21};    // 列表初始化
    vector<int> ivec3(ivec2);   // copy constructor
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7};
    vector<int> ivec4(begin(arr), end(arr));    // 不要忘记标准库算法求array
    // 迭代器范围进行初始化

    vector<int> ivec5(10);
    vector<int> ivec6(4, 100);
}

// exercise_9_12
// 对于接受一个容器创建其拷贝的构造函数要求初始值与对象的容器类型和元素类型都必须保持一致才能成功拷贝
// 对于接受一个迭代器范围创建其拷贝的构造函数的限制会更宽松一些，只要求初始值的元素类型能够与对象的元素类型相容就可以完成拷贝

void exercise_9_13()
{
    // 由于容器类型和元素类型不匹配，因此采用一对迭代器范围的方式进行初始化
    list<int> ilst{1, 1, 2, 3, 5, 8, 13, 21};
    vector<double> dvec(ilst.begin(), ilst.end());
    vector<int> ivec{0, 1, 2, 3, 4, 5, 6, 7};
    vector<double> dvec2(ivec.begin(), ivec.end());

    for (auto &&i : dvec)
    {
        cout << i << " ";
    }
    cout << endl;

    for (auto &&i : dvec2)
    {
        cout << i << " ";
    }
    cout << endl;
}

void exercise_9_14()
{
    // 注意不是拷贝初始化，而是拷贝赋值操作，使用assign
    list<const char*> words{"a", "an", "the"};
    vector<string> svec = {"Milton", "Shakespeare", "Austen"};
    svec.assign(words.cbegin(), words.cend());
    for (auto &&i : svec)
    {
        cout << i << " ";
    }
    cout << endl;
}

void exercise_9_15()
{
   vector<int> v1 = {1, 3, 5, 7, 9, 12};
   vector<int> v2 = {1, 3, 5, 9};
   vector<int> v3 = {1, 3, 5, 7};
   vector<int> v4 = {1, 3, 5, 7, 9, 12};
   cout << "v1 " << (isEqual(v1, v2) ? "==" : "!=")
        << " v2" << endl
        << "v1 " << (isEqual(v1, v3) ? "==" : "!=")
        << " v3" << endl
        << "v1 " << (isEqual(v1, v4) ? "==" : "!=")
        << " v4" << endl;
}

void exercise_9_16()
{
   list<int> lst = {1, 3, 5, 7, 9, 12};
   vector<int> v2 = {1, 3, 5, 9};
   vector<int> v3 = {1, 3, 5, 7};
   vector<int> v4 = {1, 3, 5, 7, 9, 12};
    cout << "lst " << (isEqual(lst, v2) ? "==" : "!=")
         << " v2" << endl
         << "lst " << (isEqual(lst, v3) ? "==" : "!=")
         << " v3" << endl
         << "lst " << (isEqual(lst, v4) ? "==" : "!=")
         << " v4" << endl;
}

// exercise_9_17
// if(c1 < c2)，两个容器能够相互比较的前提 一是两者的容器类型和元素类型都相同，如果是array的话还要加上所含元素数量相同
// 二是容器中所包含的元素必须提供对应的比较操作，否则容器不能进行比较

void exercise_9_18()
{
    deque<string> sdeq;
    string word;
    while (cin >> word)
    {
        sdeq.push_back(word);
    }
    for (auto iter = sdeq.cbegin(); iter != sdeq.cend(); ++iter)
    {
        cout << *iter << " ";
    }
    cout << endl;
}

void exercise_9_19()
{
    // 因为采用迭代器进行泛型编程，因此只需要改变容器类型和对象名称即可，逻辑整体没有任何改变
    list<string> slst;
    string word;
    while (cin >> word)
    {
        slst.push_back(word);
    }
    for (auto iter = slst.cbegin(); iter != slst.cend(); ++iter)
    {
        cout << *iter << " ";
    }
    cout << endl;
}

void exercise_9_20()
{
    srand(static_cast<unsigned>(time(NULL)));
    list<int> ilst;
    for (size_t i = 0; i < 20; ++i)
    {
        ilst.push_back(rand() % 100);
    }
    deque<int> oddeq, evendeq;
    for (auto iter = ilst.cbegin(); iter != ilst.cend(); ++iter)
    {
        // if(*iter % 2)   // 判断奇偶数的条件竟然写错了，真是给自己两个大嘴巴
        if(*iter & 1)   // 位运算是等价的判断奇偶数，1 奇数 0 偶数
            oddeq.push_back(*iter);
        else
            evendeq.push_back(*iter);
    }
    cout << "ilist sequence: ";
    for (auto &&i : ilst)
    {
        cout << i << " ";
    }
    cout << endl << "oddeq sequence: ";
    for (auto &&i : oddeq)
    {
        cout << i << " ";
    }
    cout << endl << "evendeq sequence: ";
    for (auto &&i : evendeq)
    {
        cout << i << " ";
    }
    cout << endl;
}

// exercise_9_21
// 插入到vector中，也是不停地将新元素插入到首元素之前的位置，只不过效率很低

// exercise_9_22
// 循环中一旦出现insert操作，容器中的迭代器、指针和引用就失效，因此需要重置
void exercise_9_22()
{
    vector<int> ivec = {1, 1, 2, 1};

    // 需要一直定位原来的容器中央迭代器
    auto iter = ivec.cbegin();
    vector<int>::size_type originSize = ivec.size(),
                           newCnt = 0;
    while (iter != ivec.cbegin() + originSize/2 + newCnt)
    {
        if (*iter == 1)
        {
            iter = ivec.insert(iter, 2);
            advance(iter, 2);
            ++newCnt;
        } else
            ++iter;
    }
    for (auto &&elem : ivec)
    {
        cout << elem << " ";
    }
    cout << endl;
    
    // 换种思路，因为是要处理容器中的一半元素，因此循环的次数是已经确定的，因此使用循环变量来控制循环次数
    size_t thresh = ivec.size() / 2;    // 循环变量阈值
    iter = ivec.cbegin();
    for (size_t index = 0; index < thresh; ++index)
    {
        if(*iter == 2)
        {
            iter = ivec.insert(iter, 3);
            advance(iter, 2);
        } else
            ++iter;
    }
    for (auto &&elem : ivec)
    {  
       cout << elem << " "; 
    }
    cout << endl;
}

// exercise_9_23
// 四个值会完全一样，都是容器中唯一的那个值

void exercise_9_24()
{
    vector<int> ivec{1,1,2,3,5};
    ivec.clear();
    cout << ivec[0] << endl
         << ivec.front() << endl
         << *ivec.begin() << endl
         << ivec.at(0) << endl;
}

// exercise_9_25
// 对于erase删除一个迭代器范围内的元素，若elem1与elem2相等，那么将不会删除任何元素并返回elem2迭代器
// 如果elem2是off-the-end iterator, 会从给定的起始位置一直删除到末尾，并返回尾后迭代器
// 如果elem1和elem2都是尾后迭代器，那么不会删除任何元素，并返回尾后迭代器

void exercise_9_26()
{
    int ia[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89};
    list<int> ilst(begin(ia), end(ia));
    vector<int> ivec(begin(ia), end(ia));
    auto lstbg = ilst.cbegin();
    while (lstbg != ilst.cend())
    {
        if(*lstbg % 2)
            lstbg = ilst.erase(lstbg);
        else
            ++lstbg;
    }
    auto vecit = ivec.cbegin();
    while (vecit != ivec.cend())
    {
        if(*vecit % 2)
            ++vecit;
        else
            vecit = ivec.erase(vecit);    
    }
    for (auto &&i : ilst)
    {
        cout << i << " ";
    }
    cout << endl;
    for (auto &&i : ivec)
    {
        cout << i << " ";
    }
    cout << endl;
}

// exercise_9_27 is prog5_forward_list

void exercise_9_28()
{
    forward_list<string> sfLst;
    auto iter = sfLst.before_begin();
    string word;
    while (cin >> word)
    {
        iter = sfLst.insert_after(iter, word);
    }
    cin.clear();
    string postr, newstr;
    char rsp;
    bool status = true;
    while (status)
    {
        cout << "Please input word which you want to insert new string after that: ";
        cin >> postr;
        cout << "Please input new string which you want to insert: ";
        cin >> newstr;
        iter = Insert(sfLst, postr, newstr);
        cout << *iter << endl;
        cout << "Would you want to continue add element? y or n: ";
        cin >> rsp;
        if(rsp == 'n' || rsp == 'N')
            status = false;
    }
    for (auto &&i : sfLst)
    {
        cout << i << " ";
    }
    cout << endl;
}

// exercise_9_29
// vec.resize(100)会将vec添加75个元素，且这些元素都进行值初始化为0
// vec.resize(10)会删除vec中的后90个元素
// exercise_9_30
// 接受单个参数的resize版本对容器中的元素要求具有默认构造函数，能够进行值初始化，否则要么利用双参数版本的resize
// 提供初始值，否则的话会出错

void exercise_9_31_list()
{
    // because list and forward_list's iterator don't have operator+
    list<int> ilst{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto iter = ilst.begin();
    while (iter != ilst.end())
    {
        if(*iter % 2)
        {
            iter = ilst.insert(iter, *iter);
            advance(iter, 2);
        }
        else
            iter = ilst.erase(iter);
    }
    for (auto &&i : ilst)
    {
        cout << i << " ";
    }
    cout << endl;
}

void exercise_9_31_forward_list()
{
    forward_list<int> ifLst{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto previt = ifLst.before_begin(),
         curit  = ifLst.begin();
    while (curit != ifLst.end())
    {
        if(*curit % 2)
            curit = ifLst.erase_after(previt);
        else
        {
            curit = ifLst.insert_after(curit, *curit);
            advance(curit, 1);
            advance(previt, 2);
        }
    }
    for (auto &&i : ifLst)
    {
        cout << i << " ";
    }
    cout << endl;
}

// exercise_9_32
// 这是不合法的，因为出现的模糊，到底是先传入iter到形参，还是先将iter递增后再传入形参是模糊的

// exercise_9_33
// begin这个迭代器会失效，发生运行时错误

void exercise_9_34()
{
    // this program is a deadloop
    vector<int> ivec{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto iter = ivec.begin();
    while (iter != ivec.end())
    {
        if(*iter % 2)
        {
            iter = ivec.insert(iter, *iter);
            advance(iter,2);
        }
        else
            ++iter; // 原程序忘记了else，否则迭代器会一直停止不动，陷入死循环
    }
    for (auto &&i : ivec)
    {
        cout << i << " ";
    }
    cout << endl;
}

// exercise_9_35
// vector的capacity是容器的容量大小，能够包含多少个元素数量
// vector的size是容器中实际含有的元素数量
// exercise_9_36
// 一个容器的capacity只会大于等于size
//exercise_9_37
// 因为list和array底层的内存管理策略不同，list是双向链表，每个元素占据一个节点，通过指针相连接
// array是固定大小的容器，不能改变容器的大小，因此两者没有capacity
// vector是先分配出一块内存，当内存不足够存放目前数量的元素时，才会重新分配一块更大的超过目前需要的内存
// 因此导致容器的容量与实际所含元素的数量可能不符合，才出现了capacity()函数
// exercise_9_38 is prog8_vector_space
// vector是成倍数增长来分配新的内存
void exercise_9_38()
{
    vector<int> ivec;
    for (size_t cnt = 0; cnt < 7; ++cnt)
    {
        vector<int>::size_type s, c;
        for(s = ivec.size(), c = ivec.capacity(); s <= c; ++s)
            ivec.push_back(1);
        
        cout << "capacity is " << ivec.capacity()
             << "    size is " << ivec.size() << endl;
    }
}
// exercise_9_39
// 程序先要求系统分配出容量为1024个空串的vector，然后向vector中添加string，
// 最后重设vector的大小为现有元素数量的二分之三
// exercise_9_40
// 这是一个很好的题目，让我真正区分了resize and reserve: resize is modify actual element's numbers
// 若是增大的话会进行值初始化；而reserve是分配多少内存，没有填入元素
// 若读入了256个单词，则resize后vector的capacity可能是1024,若是512个，则是1024；
// 若是1000个，则是2000个；若是1048个，则是2048(insert情况下是2096)个
void exercise_9_40()
{
    vector<string> svec;
    svec.reserve(1024);
    cout << "size is " << svec.size() << "\t\t" 
         << "capacity is " << svec.capacity() << endl; 
    
    vector<string>::size_type num = 256;
    // svec.insert(svec.end(), num, string());
    while (svec.size() != num)
    {
        svec.push_back("NanJiang");
    }
    cout << "size is " << svec.size() << "\t\t" 
         << "capacity is " << svec.capacity() << endl; 

    svec.resize(svec.size() + svec.size() / 2);
    cout << "size is " << svec.size() << "\t\t" 
         << "capacity is " << svec.capacity() << endl;    
}

void exercise_9_41()
{
    vector<char> cvec;
    char ch;
    while (cin.get(ch)) // 取走每一个字符，包括空白字符
    {
        cvec.push_back(ch);
    }
    string str;
    str.reserve(100);
    cout << str.size() << endl
         << str.capacity() << endl;
    // str = Initstr(cvec);
    str = string(cvec.data(), cvec.size());
    cout << "str is " << str << endl
         << str.size() << endl
         << str.capacity() << endl;
}

// exercise_9_42
// 先定义一个空字符串，然后str.reserve(100)要求系统分配100个字符大小内存准备，然后读取每一个字符Push_back到string中
// 这样可以提高程序的性能，减少重新分配string内存大小的次数

void exercise_9_43_44()
{
    string str("tho C++ Primer thru has too many tho knowledge, tho I believe myself thru can go thru it.");
    cout << "before modify: " << endl
         << str << endl;
    // ModifyStr(str, "tho", "though");
    // ModifyStr(str, "thru", "through");
    ModifyStrAns(str, "tho", "though");
    ModifyStrAns(str, "thru", "through");
    // ModifyStr_v2(str, "tho", "though");
    // ModifyStr_v2(str, "thru", "through");  
    cout << "after modifyStrAns: " << endl
         << str << endl;
}

void exercise_9_45_46()
{
    string name("James Bond"),
           pre("Mr."),
           post("II");
    ModifyStr_v3(name, pre, post);
    cout << "after modify_v3: " << endl
         << name << endl;

    string women("M"), prefix("Ms."), postfix("III");
    ModifyStr_v4(women, prefix, postfix);
    cout << "after modify_v4: " << endl
         << women << endl;
}

void exercise_9_47()
{
    string str("ab2c3d7R4E6");
    find_num_alpha(str);
    cout << endl;
    find_num_alpha_v2(str);
}

// exercise_9_48
// return string::npos

void exercise_9_49(int argc, char *argv[])
{
    ifstream ifs(argv[1]);
    if(!ifs)
    {
        cout << "Sorry, cannot open " << argv[1] << endl;
        return;
    }

    string exAscDesWord, word;
    string::size_type length = 0;
    while (ifs >> word)
    {
        if(exclude_ascender_descender(word))
        {
            if(word.size() > length)
            {
                exAscDesWord = word;
                length = word.size();
            }
        }
    }
    cout << "Eventually the longest exclude_ascender_descender word is "
         << exAscDesWord << " with " << exAscDesWord.size()
         << " length." << endl;
    ifs.close();
}

void exercise_9_50()
{
    vector<string> svec;
    string num;
    cout << "Please input a series of integer string: ";
    while (cin >> num)
    {
        svec.push_back(num);
    }
    cout << "integer vector's sum is "
         << calculateStr(svec) << endl;
    
    svec.clear();
    cin.clear();
    // cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // 跳过坏输入
    cout << "Please input a series of double string: ";
    while (cin >> num)
    {
        svec.push_back(num);
    }
    cout << "double vector's sum is "
         << calStr_v2(svec) << endl;
}

void exercise_9_51()
{
    string usrDate;
    bool goit = true;
    while (goit)
    {
        cout << "Please input a date which you want to convert to year-month-day format."
             << endl << "input format can be \"January 1, 1900\" or \"1/1/1900\""
             << " or \"Jan 1 1900\". let's starting!" << endl;
        getline(cin, usrDate);
        Date myDate(usrDate);
        cout << myDate << endl;
        cout << "Would you want to try again? y or n: ";
        char again;
        cin >> again;
        cin.ignore(1);  // 遗留在io流中的\n在作怪，导致下次循环中getline得到的是空串，抛出stoi() invalid_argument exception
        if(again == 'n' || again == 'N')
            goit = false;
    }
}

void exercise_9_51_answer()
{
    string dates[] = {
        "Jan 1,2014", "February 1 2014", "3/1/2014",
        "December 12,2024", "Aug 19 2000", "6/30/2022",
        // "Jcn 1,2014"
        // "Janvary 1,2014"
        // "Jan 32,2014"
        // "Jan 1/2014"
        // "3 1 2014 "
        "13/12/2014"
    };
    try {
        for (const auto &date : dates)
        {
            mydate newDate(date);
            cout << newDate << endl;
        } 
    } catch (const invalid_argument &err)
    {
        cout << err.what() << endl;
    }
}

void exercise_9_52()
{
    string expr;
    bool goit = true;
    while (goit)
    {
        cout << "Please input a expression to calculate: " << endl;
        getline(cin, expr);
        cout << "this expression's result is " << expresolution(expr) << endl;
        char usr;
        cout << "Would you want to try again? y or n: ";
        cin >> usr;
        cin.ignore(1);
        if(usr == 'n' || usr == 'N')
            goit = false;
    }
}

int main(int argc, char **argv)
{
    // exercise_9_2();
    // exercise_9_4();
    // exercise_9_11();
    // exercise_9_13();
    // exercise_9_14();
    // exercise_9_15();
    // exercise_9_16();
    // exercise_9_18();
    // exercise_9_19();
    // exercise_9_20();
    // exercise_9_22();
    // exercise_9_24();
    // exercise_9_26();
    // exercise_9_28();
    // exercise_9_31_list();
    // exercise_9_31_forward_list();
    // exercise_9_34();
    // exercise_9_38();
    // exercise_9_40();
    // exercise_9_41();
    exercise_9_43_44();
    // exercise_9_45_46();
    // exercise_9_47();
    // exercise_9_49(argc, argv);
    // exercise_9_50();
    // exercise_9_51();
    // exercise_9_51_answer();
    // exercise_9_52();

    return 0;
}