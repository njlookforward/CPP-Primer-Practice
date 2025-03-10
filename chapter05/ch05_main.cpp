#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cctype>
#include <stdexcept>
#include "Sales_item.hpp"

using namespace std;

int get_num()
{
    srand(static_cast<unsigned>(time(NULL)));   // product rand seed
    return rand() % 100;
}

void prog1_statement_scope()
{
    while(int num = get_num())  // statement scope, in the condition being created, while} current iteration end, num is destroyed
    {
        cout << num << endl;
        auto start_clock = clock();
        while ((clock() - start_clock) / CLOCKS_PER_SEC < 1);   // to suspend one second, notice use null statement
        if(num <= 24)
            break;
    }
}

void prog2_if_else()
{
    vector<string> scores{"F", "D", "C", "B", "A", "A++"};
    vector<unsigned> vecscores;
    unsigned grade;
    while (cin >> grade && grade >=0 && grade <= 100)
    {
        vecscores.push_back(grade);
    }

    string lettergrade;
    for (auto &&grade : vecscores)
    {
        if(grade < 60)
            lettergrade = scores[0];
        else
        {
            lettergrade = scores[(grade - 50) / 10];
            if(grade != 100)
            {
                if(grade % 10 > 7)
                    lettergrade += "+";
                else if (grade % 10 < 3)
                {
                    lettergrade += "-";
                }
            }
        }
        cout << grade << " : " << lettergrade << endl;
    }
}

void prog3_switch()
{
    unsigned aCnt = 0, eCnt = 0, iCnt = 0, oCnt = 0, uCnt = 0, otherCnt = 0;
    char ch;
    int ival = 42;
    while (cin >> ch)
    {
        switch (ch)
        {
        case 'a': case 'A':
            ++aCnt;
            break;  // don't forget break;
        case 'e': case 'E':
            ++eCnt;
            break;
        case 'i': case 'I':
            ++iCnt;
            break;
        case 'o': case 'O':
            ++oCnt;
            break;
        case 'u': case 'U':
            ++uCnt;
            break;
        // case label must be a integer constexpression
        default:
            ++otherCnt;
            break;
        }
    }

    cout << "ch05_main.cpp vowel letter statistic is:" << endl
         << "Number of vowel a: " << aCnt << endl
         << "Number of vowel e: " << eCnt << endl
         << "Number of vowel i: " << iCnt << endl
         << "Number of vowel o: " << oCnt << endl
         << "Number of vowel u: " << uCnt << endl
         << "Number of novowel: " << otherCnt << endl;
}

void prog4_switch_inner_variable()
{
    bool status = true;
    switch(status)
    {
        // case true:
        //     string file_name;   // error, implict initialization
        //     int ival = 0;       // error, explict initialization
        //     int jval;           // right, no initialization
        //     break;
        // case false:
        //     jval = 2;   // right, no initialization, just assignment
        //     break;
        case true:{
            string file_name("nanjiang");
            int ival = 0;
        }
            break;
        case false:{
            int jval = 2;
        }
            break;
    }
}

void prog5_while()
{
    // 当不知道具体的循环次数时，使用while循环
    vector<int> ivec;
    int num;
    while (cin >> num)
    {
        ivec.push_back(num);
    }
    
    auto iter = ivec.cbegin();
    while (iter != ivec.cend() && *iter >= 0)
    {
        ++iter;
    }
    if (iter == ivec.cend())
    {
        cout << "these integer vector all is unsigned" << endl;
    }
    else
    {
        cout << "these integer vector is normal integer" << endl;
    }
}

void prog6_for()
{
    string line;
    getline(cin, line); // never forget function parmeter
    for(decltype(line.size()) index = 0; index != line.size() && !isspace(line[index]); ++index)
        line[index] = toupper(line[index]);
    
    cout << "after toupper the first word, line is as follow: " << endl
         << line << endl;
    
    // for steatement head can have multiple initialization
    // duplicate line
    line.push_back(' ');
    for (decltype(line.size()) index = 0, sz = line.size();
        index < sz; ++index)
        line.push_back(line[index]);
    cout << "after duplication line is as follow: " << endl
         << line << endl;
    
    // for statement head init-statement, condition, expression all can be ignored
    vector<int> ivec;
    for (int i; cin >> i; /* expression is empty*/)
        ivec.push_back(i);
    
    auto iter = ivec.cbegin();
    for (/*init-statement is empty*/; iter != ivec.cend() && *iter >= 0; ++iter)
        /*statement can be empty*/;
    if(iter == ivec.cend())
        cout << "these integer vector all is unsigned" << endl;
    else
        cout << "these integer vector is normal integer" << endl;
}

void prog7_range_for()
{
    vector<int> ivec{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (auto &&i : ivec)
    {
        cout << i << " ";
    }
    cout << endl;
    for (auto &i : ivec)
    {
        i *= 2;
        cout << i << " ";
    }
    cout << endl;
}

void prog8_do_while()
{
    // notification: don't define variable in the condition and use ; to end do_while
    // add program
    string rsp;
    do
    {
        // 先执行循环体，在判断条件
        int ival1, ival2;
        cout << "Please input two integer to add: ";
        cin >> ival1 >> ival2;
        cout << ival1 << " + " << ival2
             << " = " << ival1 + ival2 << endl;
        cout << "would you want to continue? yes or no: ";
        cin >> rsp;
    } while (!rsp.empty() && rsp[0] == 'y');    // must write ;
    cout << "see you next, bye!!" << endl;
}

void prog9_goto()
{
begin:
    int num = get_num();
    if(num > 24)
        goto begin; // goto is not only forward, but also backward
    cout << "ultimately num is " << num << endl;

    clock_t start_clock = clock();
    while((clock() - start_clock) / CLOCKS_PER_SEC < 1);    // 暂停一秒
    // 能不用goto就不用goto，使用while循环可以替代
    int tmp;
    while ((tmp = get_num()) > 24);
    cout << endl << "ultimately tmp is " << tmp << endl;   
}

void prog10_try()
{
    Sales_item item1, item2;
    // continually read into two item, if same output add, otherwise output exception
    while (cin >> item1 >> item2)
    {
        try {
            // try and catch to capture thrown exception
            if(item1.isbn() != item2.isbn())
                throw runtime_error("Data must refer to same isbn");

            cout << "item1: " << item1 << endl
                 << "item2: " << item2 << endl
                 << "sum is " << item1 + item2 << endl << endl; 
        } catch (const runtime_error &err)
        {
            cerr << err.what() << endl
                 << "Would you want to try again? Enter y or n: ";
            char rsp;
            cin >> rsp;
            if(!cin || rsp == 'n')
                break;
        }
    }
}

int main()
{
    // prog1_statement_scope();
    // prog2_if_else();
    // prog3_switch();
    // prog4_switch_inner_variable();
    // prog5_while();
    // prog6_for();
    // prog7_range_for();
    // prog8_do_while();
    // prog9_goto();
    // prog10_try();

    return 0;
}