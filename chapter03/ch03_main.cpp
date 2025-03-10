#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <algorithm>
#include <limits>
#include <iterator>
#include <cstring>
using std::cin, std::cout, std::endl;
using std::string;
using std::vector;

void prog1_using()
{
    cout << "Enter two numbers: ";
    int v1, v2;
    cin >> v1 >> v2;

    cout << "The sum of " << v1 << " and " << v2
         << " is " << v1 + v2 << endl;
}

void prog2_string()
{
    // initialise string's some ways
    string s1;  // empty string, default constructor
    string s2("value"); // constructor
    string s3 = "three";    // first init empty string, and copy assignment operator
    string s4(s2);  // copy constructor
    string s5 = s3; // init empty string and copy assignment operator
    string s6(10, 'c');
    string s7 = string("Seven");    // 让人愤怒的写法: string tmp("Seven"), s7 = tmp;

    /*******for string object operator**********/
    // cin >> s1 >> s2;
    // cout << "test input and output: " << s1 << s2 << endl;

    // read unkown numbers string object
    // while (cin >> s1)
        // cout << s1 << endl;
    
    string line;
    while (std::getline(cin, line))
    {
        if(!line.empty() && line.size() > 80)
        {
            auto len = line.size();
            cout << len << ": " << line << endl;
        }
    }

    /********string definitely can compare in dictionary sequence*********/
    string str("Hello");
    string phrase("Hello World");
    string slang("Hiya");
    cout << (str < phrase) << endl;
    cout << (slang > phrase) << endl;

    /***********string has assignment and add with string and add with literal operator**************/
    s1 = str;
    s2 = "World";   // string assignment definitely can use literal
    string res = s1 + s2;
    cout << "s1+s2: " << res << endl;
    string res2 = s1 + ", " + s2 + '\n';
    cout << "compound add operator's result: " << res2;
    // s1 += s2;
    // cout << "s1 += s2: " << s1 << endl;

    // operator+ must have one operand is string
    // s3 = "hello" + ", ";
    s4 = s1 + ", " + "world!";
    // s5 = ("hello" + ", ") + s2;     // two literal string cannot add
}

void prog3_char_process()
{
    string str("some string");
    // range for is efficient, 遍历一个容器或者数组最好用range for statement
    for (auto c : str)
        cout << c;
    cout << endl;

    // if(!str.empty())
        // str[0] = toupper(str[0]);
    // 需求：将字符串中的第一个词改为大写
    for (decltype(str.size()) index = 0;
         index != str.size() && !isspace(str[index]); index++)
    {
        str[index] = toupper(str[index]);
    }
    cout << str << endl;

    string str2("Hello World!!!");
    decltype(str2.size()) punc_cnt = 0;
    for(auto c : str2)
        if(ispunct(c))
            ++punc_cnt;
    cout << punc_cnt
         << " punctuation characters in " << str2 << endl;

    for (auto &c : str2)
        if(isalpha(c))
            c = toupper(c);
  
    cout << "after toupper: " << str2 << endl;

    /*******将一系列的数字由十进制转换成十六进制********/
    const string hexdigits("0123456789ABCDEF");
    cout << "Please input a series of numbers"
         << " separated with space and hit ENTER to end input." << endl;
    
    string hexConvertRes;
    string::size_type num;  // why variable type is string::size_type because num one to compare with string's size
    // two is to being used to array index, so must string::size_type
    while (cin >> num)
    {
        if(num < hexdigits.size())  // 确保输入的数字合法，且过滤掉不合法的数字
            hexConvertRes += hexdigits[num];    
    }
    cout << "after hexconvertion: " << hexConvertRes << endl;
}

void prog4_vector()
{
    vector<int> ivec(10, -1);
    vector<int> ivec2(10);    // direct initialization, copy constructor
    vector<int> ivec3 = ivec2;  // copy initialization, default constructor --> copy assignment operator
    vector<string> svec(10);
    // in C++11 can list initialization, no need array
    vector<string> articles{"a", "an", "the"};  // list constructor
    vector<string> v1 = {"a", "nan", "jiang"};
    vector<string> v2(10, "hi!");    // error, must is {}
    vector<int> v3(10, 1);
    vector<int> v4{10, 1};
    vector<int> v5{10};
    // vector<string> v6("hi"); // error
    vector<string> v7{10};
    vector<string> v8{10, "hi"};
}

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

void prog5_push_back()
{
    vector<int> ivec;
    for (int i = 0; i != 100; i++)
    {
        ivec.push_back(i);
    }
    print(ivec.begin(), ivec.end());

    vector<string> text;
    string word;
    while (cin >> word)
    {
        text.push_back(word);
    }
    print(text.begin(), text.end());
}

void prog6_vector_mf()
{
    vector<int> ivec{1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (auto &i : ivec)
        i *= i;
    
    for (auto i : ivec)
        cout << i << " ";
    cout << endl;

    vector<unsigned> scores(11);
    unsigned score;
    while (cin >> score)
    {
        if(score <= 100)
            ++scores[score/10];    
    }
    for (auto i : scores)
    {
        cout << i << " ";
    }
    cout << endl;

    ivec.clear();
    for (decltype(ivec.size()) i = 0; i < 10; i++)
    {
        ivec.push_back(i);
    }
    for (auto &&i : ivec)
    {
        cout << i << " ";
    }
    cout << endl;
}

void prog7_iterator()
{
    string str("some string");
    // if(str.begin() != str.end())
    // {
    //     auto bg = str.begin();
    //     (*bg) = toupper(*bg);
    // }
    // cout << "after upper:\t" << str << endl;
    for (auto bit = str.begin(); bit != str.end() && !isspace(*bit); bit++)
        *bit = toupper(*bit);
    cout << "after toupper: " << str << endl;

    vector<string> text;
    string line;
    while (std::getline(cin, line))
    {
        text.push_back(line);
    }
    auto cbit = text.cbegin(), cendit = text.cend();
    while (cbit != cendit)
    {
        if(!cbit->empty())
            cout << *cbit << endl;
        ++cbit;
    }
}

void prog8_iterator_operator()
{
    // 二分搜索，利用左闭右开原则
    vector<string> svec;
    string word;
    while (cin >> word)
    {
        svec.push_back(word);
    }
    std::sort(svec.begin(), svec.end());
    
    cin.clear();    // 需要清空，重新输入
    // cin.ignore(std::numeric_limits<std::streamsize>::max());
    // cin.sync();
    clearerr(stdin);
    string sought;
    cout << "Please input what word you want to seek: ";

    cin >> sought;
    auto beg = svec.begin(), end = svec.end(),
         mid = beg + (end - beg) / 2;
    while (mid != end && *mid != sought)
    {
        if(*mid < sought)
            beg = mid + 1;
        else
            end = mid;
        mid = beg + (end - beg) / 2;
    }
    if(mid != end)
        cout << "in the " << mid - svec.begin() + 1
             << " position find " << sought << endl;
    else
        cout << "Sorry, " << sought
             << " isn't in the vector" << endl;
}

void prog9_array()
{
    unsigned cnt = 42;  // 不是常量表达式
    constexpr unsigned int sz = 3; // 数组的维度需要使用常量表达式
    int arr[10];
    int *parr[sz];  // 整形指针的数组
    string bad[cnt];
    int ia1[sz] = {0, 1, 2};
    int a2[] = {0, 1, 2};
    int a3[5] = {0, 1, 2};
    string a4[3] = {"hi", "bye"};

    char a5[] = {'C', '+', '+'};
    char a6[] = {'C', '+', '+', '\0'};
    char a7[] = "C++";
    const char a8[] = "Daniel";
    cout << a6 << endl
         << a7 << endl
         << a8 << endl;

    int *ptrs[10];  // array include 10 int* element
    // 不允许有引用的数组
    // int arr[10];
    int (*Parray)[10] = &arr;   // 指向10个整形元素数组的指针
    int (&arrRef)[10] = arr;    // 绑定10个整形元素数组的引用
    int *(&refarr)[10] = ptrs;

    unsigned scores[11] = {};   // 可以执行默认初始化
    unsigned grade;
    while (cin >> grade)
    {
        if(grade <= 100)
            ++scores[grade / 10];    
    }
    for (auto &&i : scores)
    {
        cout << i << " ";
    }
    cout << endl;
}

void prog10_pointer_array()
{
    string nums[] = {"one", "two", "three"};
    string *p = &nums[0];
    string *p2 = nums;
    if(p == p2)
        cout << "array name is the pointer to the first element of array." << endl;
    
    int ia[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto ia2(ia);   // auto get int*
    cout << *ia2 << endl;

    decltype(ia) ia3{10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
    ia3[3] = 23;
    int *e = &ia3[10];
    for (int* b = ia3; b < e; b++)
    {
        cout << *b << " ";
    }
    cout << endl;

    // std begin and end
    int *pbeg = std::begin(ia3), *pend = std::end(ia3);
    while (pbeg != pend)
    {
        cout << *pbeg << " ";
        ++pbeg;
    }
    cout << endl;
}

void prog11_pointer_operator()
{
    constexpr size_t sz = 5;
    int arr[sz] = {1, 2, 3, 4, 5};
    int *ip = arr;
    int *ip2 = ip + 4;
    cout << *ip << " -- " << *ip2 << endl;
    ip2 = ip + sz;  // 指向数组尾元素的后一位置，只是作为边界，不能解引用
    // int *ip3 = ip + 10; // error, 不能超过数组尾元素的后一元素

    auto arrSize = std::end(arr) - std::begin(arr);
    cout << "array's size is " << arrSize << endl;

    int *b= arr, *e = arr + arrSize;
    while (b != e)
    {
        cout << *b << " ";
        ++b;
    }
    cout << endl;

    int last = *(arr + 4);
    cout << "array's last element is " << last << endl;
    last = *arr + 10; // 11
    cout << "array's first element increment is " << last << endl;

    int *p = &arr[2];   // 3
    int j = p[1];   // 4
    int k = p[-2];  // 1
    cout << *p << " +1 " << j << " -2 " << k << endl;
}

void prog12_C_style_string()
{
    char ca[] = {'C', '+', '+', '\0'};
    cout << std::strlen(ca) << endl;

    const char ca1[] = "A string example";
    const char ca2[] = "A different string";
    if(std::strcmp(ca1, ca2))
        cout << ca1 << " -->-- " << ca2 << endl;
    else
        cout << ca1 << " --<-- " << ca2 << endl;
    
    char largeStr[50] = {};
    std::strcpy(largeStr, ca1);
    std::strcat(largeStr, " ");
    std::strcat(largeStr, ca2);
    cout << "after copy and catch: " << largeStr << endl;
}

void prog13_c_str()
{
    string s("Hello World");
    const char *str = s.c_str();
    cout << "string:  " << s << endl
         << "c_style: " << str << endl;
    
    // 使用数组初始化vector
    int int_arr[] = {0, 1, 2, 3, 4, 5};
    vector<int> ivec(std::begin(int_arr), std::end(int_arr));
    vector<int> subivec(int_arr+1, int_arr+4);
    for (auto &&i : ivec)
    {
        cout << i << " ";
    }
    cout << endl;
    cout << "subivec: ";
    for (auto &&i : subivec)
    {
        cout << i << " ";
    }
    cout << endl;
}

void prog14_multiarray()
{
    int ia1[3][4] = {};
    int ia2[10][20][30] = {};
    int ia3[3][4] = {
        {0, 1, 2, 3},
        {4, 5, 6, 7},
        {8, 9, 10 ,11}
    };  // 逐行初始化
    int ia4[3][4] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; // 逐值初始化
    int ia5[3][4] = {{0}, {4}, {8}};    // 每行的第一个元素初始化
    int ia6[3][4] = {0, 1, 2, 3};   // 第一行初始化

    // subscript and reference
    ia3[2][3] = ia2[0][0][0];
    int (&row)[4] = ia3[1];

    constexpr size_t rowCnt = 3, colCnt = 4;
    int ia7[rowCnt][colCnt];
    for (size_t i = 0; i < rowCnt; i++)
        for (size_t j = 0; j < colCnt; j++)
            ia7[i][j] = i * colCnt + j; // bu subscript assign array's element
    for (const auto &row : ia7)
    {
        for (auto &col : row)
        {
            cout << col << " ";
        }
        cout << endl;
    }

    cout << endl;
    int ia8[rowCnt][colCnt];
    int cnt = 0;
    for (auto &row : ia8)
    {
        for (auto &col : row)
        {
            col = ++cnt;
        }
    }
    for (const auto &row : ia8)
    {
        for (auto col : row)
        {
            cout << col << " ";
        }
        cout << endl;
    }

    cout << endl << "learn multiarray and pointer" << endl;
    int (*p1)[4] = ia8;
    p1 = &(ia8[2]);

    // 用常规for语句遍历多维数组
    for(auto p = ia8; p != ia8 + rowCnt; ++p)
    {
        for(auto q = *p; q != *p + colCnt; ++q)
            cout << *q << " ";
        cout << endl;
    }
    cout << "use std::begin and std::end look well" << endl;
    for(auto p = std::begin(ia8); p != std::end(ia8); ++p)
    {
        for(auto q = std::begin(*p); q != std::end(*p); ++q)
            cout << *q << " ";
        cout << endl;
    }

    // using type alias
    cout << "using alias" << endl << endl;
    using int_array = int[4];
    for(int_array *p = ia8; p != ia8 + rowCnt; ++p)
    {
        for(int *q = *p; q != *p + colCnt; ++q)
            cout << *q << " ";
        cout << endl;
    }
}

int main()
{
    // prog1_using();
    // prog2_string();
    // prog3_char_process();
    // prog4_vector();
    // prog5_push_back();
    // prog6_vector_mf();
    // prog7_iterator();
    // prog8_iterator_operator();
    // prog9_array();
    // prog10_pointer_array();
    // prog11_pointer_operator();
    // prog12_C_style_string();
    // prog13_c_str();
    prog14_multiarray();

    return 0;
}