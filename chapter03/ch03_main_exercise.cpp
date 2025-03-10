#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <vector>
#include <iterator>
#include <cstring>
#include <limits>
#include <ctime>
#include <cstdlib>
using std::cout, std::cin, std::endl, std::cerr;
using std::string;
using std::vector;

void exercise_3_1()
{
    int sum = 0;
    for(int cur = 50; cur <= 100; ++cur)
        sum += cur;
    
    cout << "from 50 to 100 inclusive is " << sum << endl;

    for (int i = 10; i >= 0; --i)
        cout << i << " ";
    cout << endl;

    cout << "Please enter two integer, print range of them: ";
    int beg, end;
    cin >> beg >> end;
    while (beg <= end)
    {
        cout << beg++ << " ";
    }
}

void exercise_3_2()
{
    // one time read one line
    string line;
    // 你个傻子，这是一次读取一个词，读取一行必须使用getline
    while (std::getline(cin, line))
    {
        if(!line.empty())
            cout << line << endl;    
    }

    // string word;
    // int cnt = 0;
    // while (cin >> word)
    //         cout << word << (++cnt % 10? " " : "\n");
    // cout << endl;
}

void exercise_3_3()
{
    // string的输入运算符是以空白字符为分隔符，若输入流中开始时有空白字符（space，包含空格、制表符、\n等），会自动跳过
    // 只有遇到有效字符才会输入到字符串中，直到读到空白字符停止输入，因此读入的字符串对象中不可能存在空白字符，都是有效字符;
    // getline函数是以\n为分隔符，因此是一行一行的读取，即使输入流中开始是空白字符，也会读取到字符串中，直到遇到换行符才会停止读取
    // 但是换行符不会读取到字符串对象中，因此字符串变量可能是一个空串，可能包含多个空白字符
    cout << "Please choice which way to input: 1 by word    2 by line:" << endl;
    char ch;
    cin >> ch;
    cout << "please input string:  Welcome to C++ family!  " << endl;
    string str;
    if(ch == '1')
    {
        cin >> str;
        cout << "read by word: " << str << endl;
        return;
    }

    // 清空输入缓冲区，目的是可以恢复继续使用输入缓冲区
    cin.clear();
    // cin.sync();  // 这两句仍然让getline() get '\n', is empty string
    // clearerr(stdin);
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // have effective
    // cin.ignore();    // effective

    if (ch == '2')
    {
        std::getline(cin, str);
        cout << "read by line: " << str << endl;
        return;
    }
    cout << "Oops, input has problem!!!" << endl;
    exit(0);
}

void exercise_3_3_cin_get()
{
    // char ch;
    // while (ch = cin.get())
    // {
    //     cout << ch << endl;
    // }
    // char a[20];
    // cin.get(a, 20);
    // cout << a << endl;
    // char b[20];
    // cin.get(b,20);
    // cout << b << endl;
    // char c[20];
    // cin.get();
    // cin.get(c, 20);
    // cout << c << endl;

    char d[10];
    cin.getline(d, 5);
    cout << d << endl;
    // char ch = cin.get();    // 果然会出问题
    cin.get(d, 5);
    cout << d << endl;
}

void exercise_3_4()
{
    // 输出较大的字符串对象
    string str1, str2;
    // cout << "Please input two string: ";
    // cin >> str1 >> str2;
    // if(str1 != str2)
    //     cout << "bigger string is " << (str1 > str2 ? str1 : str2) << endl;
    // else
    //     cout << "two string object is equal: " << str1 << endl;

    cout << "Please input two string again: ";
    cin >> str1 >> str2;
    if(str1.length() == str2.length())
        cout << "these string have same length." << endl;
    else
        cout << "longer string is " << (str1.length() > str2.length() ? str1 : str2)
             << endl;
}

void exercise_3_5()
{
    string word, line;
    cout << "Please input a seris of string: ";
    while (cin >> word)
    {
        line = line + ' ' + word;
    }
    
    cout << "finally the result string is " << line << endl;
}

void exercise_3_5_answer()
{
    // 1. directly catch
    char cont('y');
    string result, word;
    cout << "Please input a series of string: " << endl;
    while (cin >> word)
    {
        // result += word;  // 1. direct catch
        if(!result.size())
            result += word;
        else
            result = result + " " + word;
        cout << "continue input string or not? (y or n): ";
        cin >> cont;
        if(cont == 'y' || cont == 'Y')
            cout << "Please input next string: ";
        else
            break;    
    }
    cout << "finally the result after a series catching: " << result << endl;
}

void exercise_3_6()
{
    string str("hello world!");
    cout << str << " has " << str.length() << " characters." << endl;
    for (auto &c : str)
        c = 'X';
    cout << str << " has " << str.length() << " characters." << endl;
}

void exercise_3_8()
{
    string str("Hello, World!");
    cout << str << endl;
    // use normal for to change string
    // for (decltype(str.size()) index = 0; index < str.size(); index++)
    // {
    //     str[index] = 'X';
    // }

    // use while to change string
    decltype(str.size()) index = 0;
    while (index < str.size())
    {
        str[index] = 'X';
        ++index;
    }
    cout << str << endl << "use while";
    
    // 通过实际编程对比，还是range for statement is more convenient, just specify what is element and what is container
    // but normal for need to initialise chushizhi and end condition and ++
    // while has common question, need to sepcify initial value and must don't forget to self-increment
}

void exercise_3_8_answer()
{
    // use this example illustrate string also use '\0' as string's end
    cout << "Please input a string, which can include space:" << endl;
    string str;
    std::getline(cin, str);
    decltype(str.size()) index = 0;
    while (str[index] != '\0')
    {
        str[index] = 'X';
        index++;    // 又忘记increment
    }
    cout << str << endl;

    cout << "Please input a string again: " << endl;
    string line;
    std::getline(cin, line);
    for (size_t i = 0; i < line.size(); i++)
    {
        line[i] = 'X';
    }
    cout << line << endl;
}

void exercise_3_9()
{
    // string s; s[0]这种形式是非法的，因为字符串对象s是用default constructor definite, so it's a empty string, has no character
    // s[0] assum at least it has one character, 这是未定义的非法操作
}

void exercise_3_10()
{
    string line;
    while (std::getline(cin, line))
    {
        if(!line.empty())
        {
            string::iterator puncit;
            while ((puncit = std::find_if(line.begin(), line.end(), ispunct))   // 神来之笔，说明在find_if内部，传入ispunct()函数内部是字符而不是迭代器
                           != line.end())
                line.erase(puncit);
            cout << line << endl;
        }
    }
}

// 傻不傻，直接使用range for statement is more convenient
template<typename Iterator>
void print(Iterator first, Iterator last)
{
    size_t cnt = 0;
    while (first != last)
    {
        cout << *first++ << (++cnt % 10 ? " " : "\n");
    }
    cout << endl;
}

void exercise_3_14()
{
    vector<int> ivec;
    int tmp;
    while (cin >> tmp)
    {
        ivec.push_back(tmp);
    }
    print(ivec.begin(), ivec.end());
}

void exercise_3_15()
{
    vector<string> svec;
    string word;
    while (cin >> word)
    {
        svec.push_back(word);
    }
    print(svec.begin(), svec.end());
}

template<typename T>
void display_capacity_content(const vector<T> &vec)
{
    if(!vec.empty())
    {
        cout << vec.size() << ":\t";
        for (auto &&elem : vec)
        {
            cout << elem << " ";
        }
        cout << endl;
    }
    else
        cerr << "this vector is empty" << endl;
}

void exercise_3_16()
{
    vector<int> v1;
    vector<int> v2(10);
    vector<int> v3(10, 42);
    vector<int> v4{10};
    vector<int> v5{10, 42};
    vector<string> v6{10};
    vector<string> v7{10, "hi"};

    display_capacity_content(v1);
    display_capacity_content(v2);
    display_capacity_content(v3);
    display_capacity_content(v4);
    display_capacity_content(v5);
    display_capacity_content(v6);
    display_capacity_content(v7);
}

void Toupper(string &word)
{
    for (auto &&c : word)
        c = toupper(c);
}

void exercise_3_17()
{
    vector<string> svec;
    string word;
    while(cin >> word)
        svec.push_back(word);
    
    for (auto &&word : svec)
    {
        Toupper(word);
        cout << word << endl;
    }
}

void exercise_3_20()
{
    vector<int> ivec;
    int tmp;
    while(cin >> tmp)
        ivec.push_back(tmp);
    
    // use two different ways: [] and iterator
    for (decltype(ivec.size()) index = 1; index < ivec.size(); index++)
    {
        cout << ivec[index-1] + ivec[index] << " ";
    }
    cout << endl;

    decltype(ivec.size()) last = ivec.size() - 1,
                          bit = 0;
    while (bit <= last)
    {
        if(bit != last)
            cout << ivec[bit] + ivec[last] << " ";  // 不要忘记索引不是对象
        else
            cout << ivec[bit];
        ++bit;
        --last;
    }
    cout << endl;

    vector<int>::const_iterator first = ivec.begin() + 1,
                                endit = ivec.end();
    while (first != endit)
    {
        cout << *(first - 1) + *first << " ";
        ++first;    // 不要忘记变更条件
    }
    cout << endl;

    first = ivec.begin();
    endit = ivec.end() - 1;
    while (first <= endit)
    {
        if(first != endit)
            cout << *first + *endit << " ";
        else
            cout << *first;
        ++first;
        --endit;
    }
    cout << endl;
    // 通过对比，还是使用iterator会更简便一些
}

void exercise_3_22()
{
    vector<string> text;
    string line;
    while (std::getline(cin, line))
        text.push_back(line);

    for (auto bit = text.begin(); bit != text.end() && !bit->empty(); bit++)
    {
        for (auto chbit = bit->begin(); chbit != bit->end(); chbit++)
        {
            if (isalpha(*chbit))
                *chbit = toupper(*chbit);
        }
        cout << *bit << endl;
    }
}

void exercise_3_23()
{
    vector<int> ivec{345, 42, 5, 34, 8, -20, 16, 35, 100, 200}; // list initialization
    for (auto &&i : ivec)
    {
        cout << i << " ";
    }
    cout << endl;

    for(auto bit = ivec.begin(); bit != ivec.end(); ++bit)
        *bit *= 2;
    for (auto &&i : ivec)
    {
        cout << i << " ";
    }
    cout << endl;
}

void exercise_3_23_answer()
{
    // 需要程序自己随机生成10个整数
    srand((unsigned)time(NULL));    // 随机数种子
    vector<int> ivec;
    for(int i=0; i<10; ++i)
        ivec.push_back(rand() % 1000);
    
    cout << "original vector is: " << endl;
    for(auto cit = ivec.cbegin(); cit != ivec.cend(); ++cit)
        cout << *cit << " ";
    cout << endl;

    cout << "after self-multiply vector is: " << endl;
    for(auto it = ivec.begin(); it != ivec.end(); ++it)
    {
        *it *= 2;
        cout << *it << " ";
    }
    cout << endl;
}

void exercise_3_24_answer()
{
    cout << "Please input a series of numbers to process: " << endl;
    vector<int> ivec;
    int num;
    while (cin >> num)
        ivec.push_back(num);
    
    cout << "finally ivector is as follow: " << endl;
    for (auto &&i : ivec)
    {
        cout << i << " ";
    }
    cout << endl;

    cout << "add adjacent elements:" << endl;
    for(auto iter = ivec.cbegin(); iter < ivec.cend() - 1; ++iter)  // 当不更改容器内容的时候，应该用cbegin and cend
    {
        cout << *iter + *++iter << " ";
    }
    if(ivec.size() % 2 != 0)
        cout << *(ivec.cend() - 1) << endl;  // 奇数不要忘记末尾元素
    else
        cout << endl;
    
    cout << "add the first and the last element and move into middle:" << endl;
    for(auto iter = ivec.cbegin(); iter < ivec.cbegin() + ivec.size() / 2; ++iter)
        cout << *iter + *(ivec.cbegin() + (ivec.cend() - iter - 1)) << " ";   // 必须加上（）确定优先级，否则就是非法的两个迭代器相加
    if(ivec.size() % 2 != 0)
        cout << *(ivec.cbegin() + ivec.size() / 2) << endl;
    else
        cout << endl;
}

void exercise_3_25()
{
    vector<unsigned> scores(11);
    vector<unsigned>::iterator iter = scores.begin();
    unsigned grade;
    while (cin >> grade)
    {
        if(grade >= 0 && grade <= 100)
            ++*(iter + grade / 10);
    }
    for (auto &&i : scores)
    {
        cout << i << " ";
    }
    cout << endl;
}

void exercise_3_26()
{
    // 首先end-beg得到的是一个有符号整数，是两个迭代器之间的距离，而beg+这个距离得到的仍然是迭代器
    // 迭代器没有operator+操作数的两侧都是迭代器的操作符
}

string sa[10];
int ia[10];
void exercise_3_28()
{
    string sa2[10];
    int ia2[10];
}

void exercise_3_29()
{
    // 数组的缺点：数组大小是固定的，一旦初始化完成，数组大小无法改变
}

void exercise_3_31()
{
    int iarr[10] = {};  // default initialization
    for (size_t i = 0; i < 10; i++)
    {
        iarr[i] = i;
    }
    for (auto &&i : iarr)
    {
        cout << i << " ";
    }
    cout << endl;
    
    // copy iarr to iarr2
    int iarr2[10];
    for (size_t i = 0; i < 10; i++)
    {
        iarr2[i] = iarr[i];
    }
    cout << "after copy array:" << endl;
    for (auto &&i : iarr2)
    {
        cout << i << " ";
    }
    cout << endl;

    vector<int> ivec(10);
    for (size_t i = 0; i < 10; i++)
    {
        ivec[i] = i;
    }
    vector<int> ivec2(ivec);
    cout << endl << "after vector copy:" << endl;
    for (auto &&i : ivec2)
    {
        cout << i << " ";
    }
    cout << endl;   
}

void exercise_3_35()
{
    int iarr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int *p1 = iarr + 4;
    int *p2 = iarr + 8;
    cout << "before: *p1: " << *p1
         << " *p2: " << *p2 << endl;
    p1 += p2 - p1;
    cout << "after: *p1: " << *p1
         << " *p2: " << *p2 << endl;
    
    auto first = std::begin(iarr),
         last  = std::end(iarr);
    while (first != last)
    {
        *first = 0;
        cout << *first << " ";
        ++first;
    }
    cout << endl;
}

void exercise_3_36_array()
{
    int iarr1[] = {1, 1, 2, 3, 5, 8, 13};
    int iarr2[] = {1, 1, 2, 3, 5, 8, 13, 21};
    auto beg1 = std::begin(iarr1), end1 = std::end(iarr1),
         beg2 = std::begin(iarr2), end2 = std::end(iarr2);
    
    if( end1 - beg1 == end2 - beg2 )
    {
        while (beg1 != end1 && beg2 != end2)
        {
            if(*beg1 != *beg2)
            {
                cout << "Sorry, these two array is unequal because some element." << endl;
                break;
            }
            else
            {
                ++beg1;
                ++beg2;
            }
        }
        if (beg1 == end1)
        {
            cout << "Good for you, these two array is EQUAL." << endl;
        }
    }
    else
        cout << "Sorry, these two array is unequal because size." << endl;
}

void exercise_3_36_vector()
{
    vector<int> ivec1{1, 1, 2, 3, 5, 8, 13};
    vector<int> ivec2{1, 1, 2, 3, 5, 18, 13, 21};

    if(ivec1.size() == ivec2.size())
    {
        auto beg1 = ivec1.cbegin(), end1 = ivec1.cend(),
             beg2 = ivec2.cbegin();
        while (beg1 != end1)
        {
            if(*beg1 != *beg2)
            {
                cout << "Sorry, these two vector is unequal because some element." << endl;
                break;
            }
            else
            {
                ++beg1;
                ++beg2;
            }
        }
        if(beg1 == end1)
            cout << "Good for you, these two vector is EQUAL." << endl;
    }
    else
        cout << "These two vector is unequal because size." << endl;
}

void exercise_3_36_array_answer()
{
    // 类似于一个彩票游戏，假设数组的维度一定相同
    constexpr int sz = 5;
    int a[sz], b[sz];
    srand((unsigned)time(NULL));    // 生成随机数种子
    for(int i = 0; i < sz; ++i)
        a[i] = rand() % 10;
    cout << "system datas heve been generated as follow: " << endl;
    for (auto &&i : a)
    {
        cout << i << " ";
    }
    cout << endl;
    
    cout << "Please input 5 numbers in range of 0-9: ";
    for (size_t i = 0; i < sz; i++)
        cin >> b[i];
    
    cout << "user input datas are as follow: " << endl;
    for (auto &&i : b)
    {
        cout << i << " ";
    }
    cout << endl;
    
    auto beg1 = std::begin(a), beg2 = std::begin(b);
    while (beg1 != std::end(a) && beg2 != std::end(b))
    {
        if(*beg1 != *beg2)
        {
            cout << "system datas and user datas are different." << endl;
            break;
        }
        ++beg1;
        ++beg2;
    }
    if(beg1 == std::end(a))
        cout << "Congratulations! system array and user array are same." << endl;
}

void exercise_3_36_vector_answer()
{
    constexpr int sz = 5;
    vector<int> sysvec, usrvec;
    srand((unsigned)time(NULL));    // 生成随机数种子
    for (size_t i = 0; i < sz; i++)
    {
        sysvec.push_back(rand() % 10);
    }
    cout << "system vector is as follow: " << endl;
    for (auto &&i : sysvec)
    {
        cout << i << " ";
    }
    cout << endl;
    
    cout << "Please input five numbers in range of 0-9: ";
    int usrnum;
    for (size_t i = 0; i < sz; i++)
    {
        cin >> usrnum;
        usrvec.push_back(usrnum);
    }
    cout << "user vector is as follow: " << endl;
    for (auto &&i : usrvec)
    {
        cout << i << " ";
    }
    cout << endl;
    auto bit1 = sysvec.cbegin(), bit2 = usrvec.cbegin();
    while (bit1 != sysvec.cend() && bit2 != usrvec.cend())
    {
        if(*bit1 != *bit2)
        {
            cout << "Sorry, system vector are different from user vector." << endl;
            break;
        }
        ++bit1;
        ++bit2;
    }
    if(bit1 == sysvec.cend())
        cout << "Congratulations, system vector is same with user vector." << endl; 
}

void exercise_3_38()
{
    // 指针加上或减去一个无符号整数，目的是在同一数组中前进或后退，若两个指针相加，首先会是一个非常大的数，没有意义，而且可能已经远远超出同一数组的范围
}

void exercise_3_39()
{
    string str1("nanjiang");
    string str2("nanjiangshuai");
    if(str1 < str2)
        cout << str1 << "  <  " << str2 << endl;
    else
        cout << str1 << "  >  " << str2 << endl;
    
    char chstr1[80], chstr2[80];
    cout << "Please input two C_style string: ";
    cin >> chstr1 >> chstr2;
    auto result = strcmp(chstr1, chstr2);
    switch (result)
    {
    case 1:
        cout << "the first string is bigger than the second." << endl;
        break;
    case -1:
        cout << "the first string is less than the second." << endl;
        break;
    case 0:
        cout << "the two string is equal." << endl;
        break;
    
    default:
        cout << "No definition result." << endl;
        break;
    }
}

void exercise_3_40()
{
    const char str1[] = "nanjiang loves ";
    const char str2[] = "cplusplus";
    char sumstr[strlen(str1) + strlen(str2) + 1];
    std::strcpy(sumstr, str1);
    // std::strcat(sumstr, " ");
    std::strcat(sumstr, str2);
    cout << str1 << " : " << strlen(str1) << endl;
    cout << str2 << " : " << strlen(str2) << endl;
    cout << sumstr << " : " << strlen(sumstr) << endl;
}

void exercise_3_41()
{
    int iarr[] = {1, 1, 2, 3, 5, 8, 13, 21};
    vector<int> ivec(std::begin(iarr), std::end(iarr));
    for (auto &&i : ivec)
    {
        cout << i << " ";
    }
    cout << endl;
}

void exercise_3_42()
{
    vector<int> ivec{1, 1, 2, 3, 5, 8, 13, 21};
    int iarr[10] = {};
    for (size_t i = 0; i < ivec.size(); i++)
    {
        iarr[i] = ivec[i];
    }
    for (auto &&i : iarr)
    {
        cout << i << " ";
    }
    cout << endl;
}

void exercise_3_43()
{
    constexpr size_t rowCnt = 3, colCnt = 4;
    int ia[rowCnt][colCnt];
    int cnt = 0;
    for (auto &row : ia)
        for (auto &col : row)
            col = ++cnt;
    
    cout << "use three different program to print multiarray's element:" << endl;
    cout << endl << "range for: " << endl; 
    for (const int (&row)[4] : ia)
    {
        for (const int &col : row)
        {
            cout << col << " ";
        }
        cout << endl;
    }

    cout << endl << "using type alias with range for" << endl;
    using int_array = int[4];
    for ( const int_array &row : ia)
    {
        for (int col : row)
        {
            cout << col << " ";
        }
        cout << endl;
    }
    
    cout << endl << "using auto with range for" << endl;
    for (const auto &row : ia)
    {
        for (auto &col : row)
        {
            cout << col << " ";
        }
        cout << endl;
    }
    

    cout << endl << "normal for with subscript:" << endl;
    for (size_t i = 0; i < rowCnt; i++)
    {
        for (size_t j = 0; j < colCnt; j++)
        {
            cout << ia[i][j] << " ";
        }
        cout << endl;
    }
    
    cout << endl << "normal for with pointer" << endl;
    for(int (*p)[4] = ia; p != ia+rowCnt; ++p)  // notice: int** != int (*)[4]
    {
        for(int *q = *p; q != *p + colCnt; ++q)
            cout << *q << " ";
        cout << endl;
    }

    cout << endl << "using type alias with normal for with pointer" << endl;
    for (int_array *p = ia; p != ia + rowCnt; p++)
    {
        for (int *q = *p; q < *p + colCnt; q++)
        {
            cout << *q << " ";
        }
        cout << endl;
    }

    cout << endl << "using auto with pointer and normal for" << endl;
    for (auto p = ia; p < ia + rowCnt; p++)
    {
        for (auto q = *p; q < *p + colCnt; q++)
        {
            cout << *q << " ";
        }
        cout << endl;
    }
}

int main()
{
    // exercise_3_1();
    // exercise_3_2();
    // exercise_3_3();
    // exercise_3_3_cin_get();
    // exercise_3_4();
    // exercise_3_5();
    // exercise_3_5_answer();
    // exercise_3_6();
    // exercise_3_8();
    // exercise_3_8_answer();
    // exercise_3_10();
    // exercise_3_14();
    // exercise_3_15();
    // exercise_3_16();
    // exercise_3_17();
    // exercise_3_20();
    // exercise_3_22();
    // exercise_3_23();
    // exercise_3_23_answer();
    // exercise_3_24_answer();
    // exercise_3_25();
    // exercise_3_28();
    // exercise_3_31();
    // exercise_3_35();
    // exercise_3_36_array();
    // exercise_3_36_array_answer();
    // exercise_3_36_vector_answer();
    // exercise_3_36_vector();
    // exercise_3_39();
    // exercise_3_40();
    // exercise_3_41();
    // exercise_3_42();
    // exercise_3_43();

    return 0;
}