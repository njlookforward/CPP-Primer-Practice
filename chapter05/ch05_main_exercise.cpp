#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <stdexcept>
#include "MaxCntWord.hpp"

using namespace std;

void exercise_5_1()
{
    // 空语句是 ; 当语法上要求有statement，但逻辑要不需要书写statement时需要使用;或者一个{}空块
}

void exercise_5_2()
{
    // 块是用花括号包围起来的0条及以上的复合语句；
    // 语法上要求只能有一条statement，但实际的逻辑需要多条语句时，使用块组合成复合语句，一个块相当于一行语句
    // 有时为了是逻辑更加清晰，将一组语句结合起来作为一个模块时，使用块
    // 为了添加局部作用域时，添加块作用域
}

void exercise_5_3()
{
    int sum = 0, val = 1;
    while (val <= 10)
        sum += val, ++val;  // 我认为可读性是降低了，放在一起不太容易梳理逻辑
    
    cout << "from 1 to 10 inclusive is " << sum
         << endl;
}

// exercise_5_5 == prog2_if_else()
void exercsie_5_6()
{
    vector<unsigned> vecscores;
    unsigned grade;
    while (cin >> grade && grade >= 0 && grade <= 100)
    {
        vecscores.push_back(grade);
    }
    
    // convert number_score into letter_score
    vector<string> scores{"F", "D", "C", "B", "A", "A++"};
    string letterscore;
    for (auto &&grade : vecscores)
    {
        letterscore = grade < 60 ? scores[0]
                                 : scores[(grade - 50) / 10];
        if (grade >= 60 && grade != 100)
        {
            letterscore += grade % 10 > 7 ? "+"
                                          : grade % 10 < 3 ? "-"
                                                           : "";
        }
        cout << grade << " -> " << letterscore << endl; 
    }
}

void exercise_5_8()
{
    // 悬垂else:当if分支的数量大于else分支时，每个else分支应该与哪个if分支配对问题成为悬垂else
    // C++中采取就近原则，else分支是与离他最近的if分支配对的
}

void exercise_5_9()
{
    unsigned aCnt = 0, eCnt = 0, iCnt = 0, oCnt = 0, uCnt = 0, otherCnt = 0;
    char ch;
    while (cin >> ch)
    {
        if (ch == 'a' || ch == 'A')
            ++aCnt;
        else if (ch == 'e' || ch == 'E')
            ++eCnt;
        else if (ch == 'i' || ch == 'I')
            ++iCnt;
        else if (ch == 'o' || ch == 'O')
            ++oCnt;
        else if (ch == 'u' || ch == 'U')
            ++uCnt;
        else
            ++otherCnt;
    }
    
    cout << "ch05_main.cpp vowel letter statistic is:" << endl
         << "Number of vowel a: " << aCnt << endl
         << "Number of vowel e: " << eCnt << endl
         << "Number of vowel i: " << iCnt << endl
         << "Number of vowel o: " << oCnt << endl
         << "Number of vowel u: " << uCnt << endl
         << "Number of novowel: " << otherCnt << endl;
}

void exercise_5_11()
{
    unsigned aCnt = 0, eCnt = 0, iCnt = 0, oCnt = 0, uCnt = 0, otherCnt = 0,
             spaceCnt = 0, tableCnt = 0, nextlineCnt = 0;
    char ch;
    while (cin.get(ch)) // 可以逐个读取每一个字符，包括空白字符
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
        // why read space table \n all is zero beacuse cin will skip kongbaizifu,so 空白字符被丢弃了
        // need to use getchar() to read kongbaizifu
        case ' ':
            ++spaceCnt;
            break;
        case '\t':  // ‘\t’应该便成了‘ ’
            ++tableCnt;
            break;
        case '\n':
            ++nextlineCnt;
            break;
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
         << "Number of space  : " << spaceCnt << endl
         << "Number of table  : " << tableCnt << endl
         << "Number of nextline: " << nextlineCnt << endl
         << "Number of novowel: " << otherCnt << endl;
}

void exercise_5_12()
{
    unsigned ffCnt = 0, flCnt = 0, fiCnt = 0;
    char last, curr;
    string str;
    cin >> last;
    while (cin >> curr)
    {
        str.clear();
        str += last;
        str += curr;
        if (str == "ff")
            ++ffCnt;
        else if (str == "fl")
            ++flCnt;
        else if (str == "fi")
            ++fiCnt;
        
        last = curr;
    }
    cout << "ch05_main_exercsie.cpp string statistic: " << endl
         << "ff occur " << ffCnt << endl
         << "fl occur " << flCnt << endl
         << "fi occur " << fiCnt << endl;
}

void exercise_5_12_answer()
{
    // still count character sequence ff fl fi occurrence times, but every character only belong to one sequence, can't simultaneous two sequence
    unsigned ffCnt = 0, flCnt = 0, fiCnt = 0;
    char cur, prech = '\0';
    while (cin >> cur)
    {
        bool reset = false;
        if (prech == 'f')
        {
            switch (cur)
            {
            case 'f':
                ++ffCnt;
                reset = true;
                break;
            case 'l':
                ++flCnt;
                break;
            case 'i':
                ++fiCnt;
                break;
            default:
                break;
            }
        }
        // 判断完序列后，需要alter character XXXXfflfffiXXX
        if(reset)
            prech = '\0';
        else
            prech = cur;
    }
    cout << "ff occurs " << ffCnt << " times" << endl
         << "fl occurs " << flCnt << " times" << endl
         << "fi occurs " << fiCnt << " times" << endl;
}

void exercise_5_14()
{
    vector<string> svec;
    string word;
    while (cin >> word)
    {
        if(!word.empty())
            svec.push_back(word);    
    }
    
    int curOccur = 1;
    MaxCntWord maxWord;
    auto first = svec.cbegin(), second = first + 1;
    while (second != svec.cend())
    {
        if (*first == *second)
        {
            ++curOccur;
        }
        else
        {
            if(curOccur > maxWord.occur())
                maxWord.upgrade(*first, curOccur);
            else
                curOccur = 1;
        }
        ++first, ++second;
    }

    if(maxWord.isValid())
        cout << maxWord.word() << " occurs " << maxWord.occur() << " times." << endl;
    else
        cout << "these word sequence don't have reduplicate word, everyone is unique." << endl;
}

void exercise_5_14_answer()
{
    // compare pre and cur, at the beginning, pre can be '\0' or ""等空字符
    string curString, preString, maxString; // at the beginning, three kind string is all null string ""
    unsigned curCnt = 1, maxCnt = 0;
    while (cin >> curString)
    {
        if (curString == preString)
        {
            ++curCnt;
            if(curCnt > maxCnt)
            {
                maxString = curString;
                maxCnt = curCnt;
            }
        }
        else
            curCnt = 1;
        
        preString = curString;
    }
    if(maxCnt > 1)
        cout << "the most occurence string is " << maxString
             << ", occurs " << maxCnt << " times" << endl;
    else
        cout << "every string is unique" << endl; 
}

void exercise_5_16()
{
    // to compare while and for
    vector<int> ivec;
    int num;
    while (cin >> num)
    {
        ivec.push_back(num);
    }
    cout << "while input and for display:" << endl;
    for (size_t i = 0; i < ivec.size(); ++i)
    {
        cout << ivec[i] << " ";
    }
    cout << endl;

    ivec.clear();
    cin.clear();
    cin.sync(); // the goal is to recovery cin
    for (int num; cin >> num; /*null expression*/)  // Because cin is mistake, so for is over in the beginning
    {
        ivec.push_back(num);
    }
    cout << "for input and while display:" << endl;
    size_t index = 0;
    while (index != ivec.size())
    {
        cout << ivec[index++] << " ";
    }
    cout << endl;
    // 虽然两种方法都可以实现目的，但还是用while来进行循环读取，用for遍历数组或容器等序列比较好
    // 无论是书写还是逻辑上更自洽一些
}

void exercise_5_17()
{
    vector<int> ivec1, ivec2;
    int num;
    cout << "Please input a series of numbers to the first vector:" << endl;
    while (cin >> num)
    {
        ivec1.push_back(num);
    }

    cin.clear();
    clearerr(stdin);
    cout << "Please continue to input a series of numbers to the second vector:" << endl;
    while (cin >> num)
    {
        ivec2.push_back(num);
    }
    
    vector<int> &shorter = ivec1.size() < ivec2.size() ? ivec1 : ivec2,
                &longer  = ivec1.size() > ivec2.size() ? ivec1 : ivec2;
    bool isEqual = true;
    for (size_t i = 0; i < shorter.size(); ++i)
    {
        if(shorter[i] != longer[i])
        {
            isEqual = false;
            break;
        }
    }
    if(isEqual)
        cout << "one vector is the prefix of another vector." << endl;
    else
        cout << "the two vector don't have any association." << endl;
    
    // definitely can use while to deal with
    auto it1 = ivec1.cbegin(),
         it2 = ivec2.cbegin();
    while (it1 != ivec1.cend() && it2 != ivec2.cend())
    {
        if(*it1 != *it2)
            break;

        ++it1, ++it2;
    }
    cout << endl << "use while to compare:" << endl;
    if(it1 == ivec1.cend())
        cout << "the first vector is the prefix of the second vector" << endl;
    else if(it2 == ivec2.cend())
        cout << "the second vector is the prefix of the first vector" << endl;
    else
        cout << "two integer don't have any association" << endl;
}

void exercise_5_19()
{
    string str1, str2, rsp;
    do
    {
        cout << "Please input two string object to compare length: ";
        cin >> str1 >> str2;
        cout << "the shorter string is: " << (str1.length() < str2.length() ? str1 : str2)
             << endl;
        // string rsp;  // 这肯定是不对的，do{}定义在其中的变量，当来到}就已经结束生命了，在condition中肯定看不见
        cout << "would you want to try again? yes or no: ";
        cin >> rsp;
    } while (!rsp.empty() && rsp[0] != 'n');
    cout << "see you next, good bye!" << endl;
}

void exercise_5_20()
{
    vector<string> svec;
    string curStr;
    while (cin >> curStr)
    {
        if (svec.empty())
        {
            svec.push_back(curStr);
        }
        else
        {
            auto last = svec.cend() - 1;
            if(*last == curStr && isupper(curStr[0]))
            {
                svec.push_back(curStr);
                break;
            }
            else
                svec.push_back(curStr);
        }
    }
    if(cin)
        cout << "input reduplicate string: " << curStr << endl;
    else
        cout << "any string is unique!" << endl;
    for (auto &&str : svec)
    {
        cout << str << " ";
    }
    cout << endl;
}

void exercise_5_21()
{
    string curString, preString;
    bool bl = true; // unique
    while (cin >> curString)
    {
        if(!isupper(curString[0]))
            continue;
        if(curString == preString)
        {
            bl = false;
            cout << "reduplicate string is " << curString << endl;
            break;
        }
        preString = curString;
    }
    if(bl)
        cout << "in the sequence, every string is unique" << endl;
}

void exercise_5_23()
{
    int ival1, ival2;
    bool isAgain = true;
    while (isAgain)
    {
        try {
            cout << "Please input two integer to divide: ";
            cin >> ival1 >> ival2;
            if(ival2)
                cout << ival1 << " / " << ival2 << " = "
                     << ival1 / ival2 << endl;
            else
            {
                // cout << "Sorry, the second integer must be a non-zero, please input again" << endl;
                // continue;
                throw logic_error("the second integer must be a non-zero");
            }
        } catch (const logic_error &err) {
            cerr << err.what() << endl;
        }

        char rsp;
        cout << "Would you want to try again? y or n: ";
        cin >> rsp;
        if(rsp == 'n' || rsp == 'N')
        {
            cout << "see you next, good bye!" << endl;
            isAgain = false;
        }
    }
}

int main()
{
    // exercise_5_3();
    // exercsie_5_6();
    // exercise_5_9();
    // exercise_5_11();
    // exercise_5_12();
    // exercise_5_12_answer();
    // exercise_5_14();
    // exercise_5_14_answer();
    // exercise_5_16();
    // exercise_5_17();
    // exercise_5_19();
    // exercise_5_20();
    // exercise_5_21();
    // exercise_5_23();

    return 0;
}