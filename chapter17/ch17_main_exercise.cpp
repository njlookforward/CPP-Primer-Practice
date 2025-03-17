#include <tuple>
#include <iostream>
#include <utility>
#include <vector>
#include <memory>
#include <bitset>
#include <random>
#include <iomanip>
#include <cmath>
#include "exercise.hpp"
#include "TextQuery_tuple.hpp"

using namespace std;

void exercise_17_1()
{
    tuple<int, int, int> threeInt{10, 20, 30};
    cout << get<0>(threeInt) << " "
         << get<1>(threeInt) << " "
         << get<2>(threeInt) << endl;
}

void exercise_17_2()
{
    tuple<string, vector<string>, pair<string, int>>
    compSet{"nanjiang", {"how", "now", "brown"}, {"nanjiang", 25}};
}

void exercise_17_3(int argc, char **argv)
{
    checkArgs(argc, 2);
    ifstream infile;
    openInputFile(infile, argv[1]);
    shared_ptr<ifstream> pfile(&infile, [](ifstream *pf) { pf->close(); });

    TextQuery queryprog(infile);
    while(true)
    {
        cout << "Please input what word you want to query or q to quit: ";
        string word;
        cin >> word;
        if(!cin || word == "q") break;
        cout << queryprog.query(word) << endl;
    }
// 我认为tuple的设计会更好，代码更精简，逻辑也是相同的，即使要将文本查询程序扩展成面向对象设计版本
// 针对tuple类型的结果，也可以直接得到string，set的begin and end, text->size()等等
// 思考的过程永远都不要复杂化，针对谁进行思考，就从谁为原点进行思考，不要舍近求远
}

// exercise_17_4 in the exercise.hpp and prog2
// exercise_17_5_6 in the exercise.hpp
// exercies_17_7
// 我还是更倾向于使用tuple版本，原因就是简单，足够满足我的需求，尽管我可以自定义struct类实现同样的功能
// 但是还需要定义数据成员和至少要有构造函数，因此相比于tuple，更麻烦一些

// exercise_17_8
// 如果将Sales_data()作为accumulate的第三个参数的话，也会进行正常的累加，但是在输出时，是没有isbn的书号的

void exercise_17_9()
{
    bitset<64> bitvec(32);  // 000000000000000100000
    bitset<32> bv(1010101); // 000000000011110110100110110101
    // string bstr;
    cout << "Please input a 8 bits number with 0 and 1: ";
    // cin >> bstr;
    // bitset<8> bv2(bstr);
    bitset<8> bv2;
    cin >> bv2;
    cout << bitvec.to_string() << endl
         << bv.to_string() << endl
         << bv2 << endl;
}

// exercise_17_10 说实话，我没理解是什么意思
void exercise_17_10()
{
    // 一定要分清十进制表示的具体的数和二进制表示的位运算，都是一个数，只是进制的表示方式不同
    bitset<22> bv = (1UL << 1) | (1UL << 2) | (1UL << 3) |
                    (1UL << 5) | (1UL << 8) | (1UL << 13) | (1UL << 21);
    cout << bv << endl;
    bitset<22> bv2;
    bv2.set(13);
    bv2[19] = 1;
    cout << bv2 << endl;
}

void exercise_17_11_12_13_ten()
{
    bitset<11> bv("10111001011");
    int answer = bv.to_ulong();
    cout << "answer is " << answer << " with" << endl
         << bv << endl;
    
    TenBitsAnswer answerSet(answer);
    int index;
    while (true)
    {
        cout << "Please input which question's answer you want to know or 0 to quit: ";
        cin >> index;
        if(!cin || index == 0) break;
        cout << "No." << index << "\'s answer is " << boolalpha 
             << answerSet.getAnswer(index) << noboolalpha << endl; 
    }
}

void exercise_17_11_12_13_hundred()
{
    unsigned long long ullnum = 47183724891345892;
    bitset<101> answer(ullnum);
    cout << ullnum << " with" << endl
         << answer << endl;
    HundredBitsAnswer answerSet(ullnum);
    int index;
    while (true)
    {
        cout << "Please input which question's answer you want to know or 0 to quit: ";
        cin >> index;
        if(!cin || index == 0) break;
        cout << "No." << index << "\'s answer is " << boolalpha 
             << answerSet.getAnswer(index) << noboolalpha << endl; 
    } 
}

// exercise_17_14 in the prog7
// exercise_17_15_16 in the prog6
// exercise_17_17_18 in the prog8 我不知道怎么修改正则表达式，只能修改程序逻辑了

// exercise_17_19
// 因为如果m[4]没有匹配，则m[4].str()返回空串，仍然能够用于判断
// exercise_17_20 in the prog9
void exercise_17_21(int argc, char **argv)
{
    checkArgs(argc, 2);
    ifstream infile;
    openInputFile(infile, argv[1]);
    shared_ptr<ifstream> pfile(&infile, [](ifstream *pf) { pf->close(); });

    vector<peopleinfo> phones;
    AddressBook(phones, infile);
    printPhones(cout, phones);
}

// exercise_17_22
// string phone("(\\()?(\\d{3})(\\))?([ ]*)(\\d{3})([ ]*)(\\d{4})");
// 我认为就是修改正则表达式

// exercise_17_23
// (\\d{5})([-])?(\\d{4})?

// exercise_17_24 is prog11

// void exercise_17_25(int argc, char **argv)
// {
//     checkArgs(argc, 2);
//     ifstream infile;
//     openInputFile(infile, argv[1]);
//     shared_ptr<ifstream> pfile(&infile, [](ifstream *pf) { pf->close(); });

//     string phone("(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ])?(\\d{4})");
//     regex re(phone);

//     string fmt("$2.$5.$7");
//     smatch results;
//     string line;
//     while (getline(infile, line))
//     {
//         if(regex_search(line, results, re))
//         {
//             cout << results.prefix().str() << results.format(fmt) << endl;
//         }    
//     }
// }

// void exercise_17_26(int argc, char **argv)
// {
//     checkArgs(argc, 2);
//     ifstream infile;
//     openInputFile(infile, argv[1]);
//     shared_ptr<ifstream> pfile(&infile, [](ifstream *pf) { pf->close(); });

//     string phone("(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ])?(\\d{4})");
//     regex re(phone);

//     string fmt("$2.$5.$7");
//     string line;
//     while (getline(infile, line))
//     {
//         sregex_iterator iter(line.begin(), line.end(), re), edit;
//         string name;
//         if (iter != edit)
//         {
//             name.assign(iter->prefix().str());
//         }
//         if(++iter != edit) {
//             cout << name;
//         }
//         for(; iter != edit; ++iter)
//         {
//             cout << iter->format(fmt) << " ";
//         }
//         cout << endl;
//     }
// }

// void exercise_17_27()
// {
//     string post("(\\d{5})([-])?(\\d{4})");
//     regex re(post);

//     string fmt("$1-$3");
//     string stampnum;
//     while (cin >> stampnum && stampnum != "q")
//     {
//         cout << regex_replace(stampnum, re, fmt) << endl;
//     }
// }

void exercise_17_28_29()
{
    // BUg: 总是出现问题，是我的测试方法有问题，必须修改一次然后继续才行，否则一直都是0000000000
    // 对于随机数发生器，设置一次种子之后，要进行连续地生成才可以，不能设置一次生成一次，这样都是00000
    for(int i = 0; i < 10; ++i)
        // cout << randomNum_v1() << " ";
        cout << randomNum_v2() << " ";
    cout << endl;

    // Bug: 现在终于发现为什么一直打印一串000000000000000000了
    // 因为我在循环中不断地更改随机数引擎对象的种子，每次循环都在更新，都在原地踏步，因此是一串相同的0
    // 必须在循环外面进行更新，在里面生成新的随机数
    cout << randomNum_v2(0) << " ";
    for(int i = 0; i < 9; ++i)
        // cout << randomNum_v1() << " ";
        cout << randomNum_v2() << " ";
    cout << endl;

    cout << randomNum_v2(19743) << " ";
    for(int i = 0; i < 9; ++i)
        // cout << randomNum_v1() << " ";
        cout << randomNum_v2() << " ";
    cout << endl;
}

void exercise_17_30()
{
    for(int i = 0; i < 10; ++i)
        cout << randomNum_v3() << " ";
    cout << endl;

    cout << randomNum_v3(0) << " ";
    for (size_t i = 0; i < 9; i++)
    {
        cout << randomNum_v3() << " ";
    }
    cout << endl;

    cout << randomNum_v3(19743, 0, 9) << " ";
    for (size_t i = 0; i < 9; i++)
    {
        cout << randomNum_v3() << " ";
    }
    cout << endl;
}

// exercise_17_31
// 对于本节中的游戏，如果将engine and distribution定义在do_while循环内，那么每次循环随机数发生器都被重新生成
// 因此每次循环产生的随机数都是一样的，不会发生任何变化，因此游戏结果都是一样的，没有任何变化。如果非要定义在循环内
// 那么可以将engine and dsitribution定义为static

// exercise_17_32
// 如果将resp定义在循环内，那么在while的条件表达式中，resp已经出了它的作用域，resp是非法的无定义的
// 因此无法向resp输入数据，会编译错误

void exercise_17_33(int argc, char **argv)
{
    checkArgs(argc, 4);
    ifstream map_file, infile;
    openInputFile(map_file, argv[1]);
    openInputFile(infile, argv[2]);
    // 以追加模式定位到文件的末尾，应该是app，我记错了
    ofstream outfile(argv[3], ios::app | ios::out);
    if(!outfile)
    {
        cerr << "sorry, cannot open " << argv[3] << endl;
        exit(-1);
    }
    shared_ptr<ifstream> pf1(&map_file, [](ifstream *pf) { pf->close(); });
    shared_ptr<ifstream> pf2(&infile, [](ifstream *pf) { pf->close(); });
    shared_ptr<ofstream> pf3(&outfile, [](ofstream *pf) { pf->close(); });

    word_tansform(map_file, infile, outfile);
    // word_tansform(map_file, infile);
}

// exercise_17_34 is prog17 and prog18
void exercise_17_35()
{
    cout << uppercase << "hexadecimal: "
         << hexfloat << sqrt(2.0)
         << nouppercase << defaultfloat << endl;
}

void exercise_17_36()
{
    // 按列进行打印
    cout << setw(12) << 100 * sqrt(2.0) << "defaultfloat\n"
         << scientific
         << setw(12) << 100 * sqrt(2.0) << "scientific\n"
         << fixed
         << setw(12) << 100 * sqrt(2.0) << "fixed float\n"
         << hexfloat
         << setw(12) << 100 * sqrt(2.0) << "hexadecimal\n"
         << defaultfloat
         << setw(12) << 100 * sqrt(2.0) << "default float\n";
}

void exercise_17_37(int argc, char **argv)
{
    checkArgs(argc, 2);
    ifstream infile;
    // ifstream infile("..\\..\\..\\data\\storyDataFile");
    openInputFile(infile, argv[1]);
    shared_ptr<ifstream> pf(&infile, [](ifstream *p){ p->close(); });

    string line(50, '\0');
    // Bug：经过试验，如果数组长度小于文件输入行的长度，那么读取失败，直接跳出循环
    while (infile.getline(&line[0], 50, '\n'))
    { 
        cout << &line[0] << endl;
        // 目前通过实验，如果使用string进行输出，那么未被覆盖的部分会被输出
        // 而通过使用char*风格字符串进行输出，就是正常的格式了，说明，getline会在行的末尾添加'\0'
        // 同时说明string是把有效字符全部逐个输出出去
        // line.assign(50, '\0');
    }
    // 空行可以正常读取，但是文件中输入行长度大于数组长度时，会读取失败，直接跳出循环
}

void exercise_17_37_answer(int argc, char **argv)
{
    checkArgs(argc, 2);
    ifstream infile;
    openInputFile(infile, argv[1]);
    shared_ptr<ifstream> pf(&infile, [](ifstream *p){ p->close(); });

    char text[30];
    // 又学到了一种读取文件的方法，只观察文件末尾标识符
    while (!infile.eof())   // 需要一直读到文件末尾
    {
        infile.getline(text, 30);
        cout << text << endl;
        if(infile.fail())   // 说明输入行的字符长度大于30
        {
            if(infile.gcount() == 29)
                infile.clear();
            else
                break;        
        }
    }
}

void exercise_17_38_answer(int argc, char **argv)
{
    checkArgs(argc, 2);
    ifstream infile;
    openInputFile(infile, argv[1]);
    shared_ptr<ifstream> pf(&infile, [](ifstream *p){ p->close(); });

    char text[30];
    while (!infile.eof())   // 需要一直读到文件末尾
    {
        infile.getline(text, 30);
        cout << text;
        if(infile.fail())   // 说明输入行的字符长度大于30
        {
            if(infile.gcount() == 29)
                infile.clear();
            else
                break;        
        } else
            cout << endl;
    }
}

void exercise_17_38(int argc, char **argv)
{
    // 不会，需要看答案
    checkArgs(argc, 2);
    fstream file(argv[1], ios::in | ios::out);
    if(!file)
    {
        cerr << "sorry, cannot open " << argv[1] << endl;
        exit(-1);
    }
    shared_ptr<fstream> pf(&file, [](fstream *p){ p->close(); });

    string line(30, '\0');
    while (file.getline(&line[0], 30, '\n'))
    { 
        file.seekg(-1, ios::cur);
        file << &line[0];
        file.seekg(1, ios::cur);
    }
}

// exercise_17_39 is prog20

int main(int argc, char **argv)
{
    // exercise_17_1();
    // exercise_17_3(argc, argv);
    // exercise_17_9();
    // exercise_17_10();
    // exercise_17_11_12_13_ten();
    // exercise_17_11_12_13_hundred();
    // exercise_17_21(argc, argv);
    // exercise_17_25(argc, argv);
    // exercise_17_26(argc, argv);
    // exercise_17_27();
    // exercise_17_28_29();
    // exercise_17_30();
    // exercise_17_33(argc, argv);
    // exercise_17_35();
    // exercise_17_36();
    // exercise_17_37(argc, argv);
    // exercise_17_37_answer(argc, argv);
    // exercise_17_38(argc, argv);
    exercise_17_38_answer(argc, argv);

    return 0;
}