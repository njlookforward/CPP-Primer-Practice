#include "Chapter6.hpp"

int fact(int val)
{
    int ret = 1;
    while (val > 1)
    {
        ret *= val--;
    }
    return ret;
}

void prog1_function()
{
    int res = fact(5);
    cout << "5! = " << res << endl;
    
    // res = fact("hello");    // error
    // fact();
    // fact(42,0,0);
    res = fact(3.14);
}

size_t count_calls()
{
    static int ctr; // if local static object not being initialised, execute value initialization, int = 0
    return ++ctr;
}

void prog2_local_static_object()
{
    for (size_t i = 0; i < 10; ++i)
    {
        cout << count_calls() << " ";
    }
    cout << endl;
}

void prog3_pass_paremeter()
{
    srand(static_cast<unsigned>(time(NULL)));   // 生成随机数种子
    int ival = rand() % 20;
    cout << "before reset, ival = " << ival
         << "   &ival = " << &ival << endl;
    reset(&ival);
    cout << " after reset, ival = " << ival
         << "    &ival = " << &ival << endl;
    
    ival = rand() % 100;
    cout << endl << "pass by reference" << endl
         << "before reset, ival = " << ival
         << "   &ival = " << &ival << endl;
    reset(ival);
    cout << " after reset, ival = " << ival
         << "    &ival = " << &ival << endl;
    
    int cnt = 0;
    auto index = find_char("nanjiang", 'a', cnt);   // parameter is const string& 的好处, can pass literal
    cout << "a in the string nanjiang occurs " << cnt << " times."
         << " the first occurrence is " << index << endl;
}

void prog4_array_parameter()
{
    print("nanjiang");
    int arr[] = {1, 1, 2, 3, 5, 8, 13, 21};
    cout << "use begin and end: " << endl;
    print(begin(arr), end(arr));
    cout << "use array and size: " << endl;
    print(arr, end(arr) - begin(arr));
    cout << "use reference to array:" << endl;
    print(arr);

    int multiArr[][4] = {
        1, 1, 2, 3,
        5, 8, 13, 21,
        34, 55, 89, 144
    };
    cout << endl << "print multiply array: " << endl;
    print(multiArr, end(multiArr) - begin(multiArr));
}

void prog5_initializer_list()
{
    error_msg({"nanjiang", "is", "practising", "C++", "programs"});
    cout << endl << "change parameter numbers:" << endl;
    error_msg({"nanjiang", "love", "C++", "World"});
    cout << endl << "parameter number is only one:" << endl;
    error_msg({"nanjiang"});
}

void prog6_return()
{
    string str1 = "nanjiang", str2 = "jiang";
    if(str_subrange(str1, str2))
        cout << str1 << " and " << str2
             << " have inclusive relationship" << endl;
    else
        cout << "Sorry, " << str1 << " and " << str2
             << " don't have any relationship" << endl;
    
    // str1 = manip();
    auto sz = shorterString(str1, str2).size();
    // shorterString(str1, str2) = "X";    // error, 左操作数是常量

    cout << "before change: " << str1 << endl;
    get_val(str1, 0) = 'N'; // 说明返回类型可以是左值，因此可以作为赋值操作符的左操作数
    cout << " after change: " << str1 << endl;

    vector<string> svec = process();
    cout << endl;
    if(!svec.empty())
        for (auto &&i : svec)
        {
            cout << i << " ";
        }
    else
        cout << "Sorry, empty";
    cout << endl;
}

void prog7_default_argument()
{
    cout << screen() << endl
         << screen(66) << endl
         << screen(66, 256) << endl
         << screen(66, 256, '#') << endl;
    
    string window;
    // window = screen(, , '?');
    def = '$';
    sz wd = 256;
    cout << "after change: " << screen() << endl;
}

void prog8_constexpr_func()
{
    constexpr int foo = new_sz();
    int arr[scale(2)];
    int i = 3;
    int arr2[scale(i)] = {};
}

void prog9_assert_ndebug()
{
    string word;
    cout << "Please input a string exceed 4 words: ";
    cin >> word;
    constexpr int threshold = 4;
    // assert(word.size() > threshold);
    if(word.size() <= threshold)
    {
        cout << "Error: " << __FILE__ << " in the function "
             << __func__ << " at the line " << __LINE__ << endl
             << "       Complied on the " << __DATE__
             << " at " << __TIME__ << endl
             << "       Word read \"" << word << "\""
             << ": Length is too short." << endl;
    }

    int iarr[] = {1, 1, 2, 3, 5, 8, 13, 21};
    print(iarr, end(iarr) - begin(iarr));
}

void prog10_pointer_function()
{
    bool (*pf)(const string&, const string &) = isShorter;
    decltype(pf) pf_1 = &isShorter;
    auto pf_2 = isShorter;
    bool b1 = pf("hello", "goodbye"),
         b2 = pf_1("hello", "goodbye"),
         b3 = pf_2("hello", "goodbye"),
         b4 = (*pf)("hello", "goodbye");
        
    int iarr[] = {1, 1, 2, 3, 5, 8, 13, 21};
    void (*pf_3) (const int*, const int*) = print;
    pf_3(begin(iarr), end(iarr));
}

// array parameter is used to pass to main function
int main(int argc, char **argv)
{
    // prog1_function();
    // prog2_local_static_object();
    // prog3_pass_paremeter();
    // prog4_array_parameter();
    // for(int i = 0; i < argc; ++i)
    // {
    //     cout << argv[i] << endl;
    // }
    // cout << endl;

    // prog5_initializer_list();
    // prog6_return();
    // prog7_default_argument();
    // prog8_constexpr_func();
    // prog9_assert_ndebug();
    prog10_pointer_function();
    
    bool some_failure = false;;
    if(some_failure)
        return EXIT_FAILURE;
    else
        return EXIT_SUCCESS;
}