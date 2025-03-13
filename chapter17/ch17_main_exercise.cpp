#include <tuple>
#include <iostream>
#include <utility>
#include <vector>
#include <memory>
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

int main(int argc, char **argv)
{
    // exercise_17_1();
    exercise_17_3(argc, argv);

    return 0;
}