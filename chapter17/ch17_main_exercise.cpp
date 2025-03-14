#include <tuple>
#include <iostream>
#include <utility>
#include <vector>
#include <memory>
#include <bitset>
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

int main(int argc, char **argv)
{
    // exercise_17_1();
    // exercise_17_3(argc, argv);
    // exercise_17_9();
    // exercise_17_10();
    // exercise_17_11_12_13_ten();
    exercise_17_11_12_13_hundred();

    return 0;
}