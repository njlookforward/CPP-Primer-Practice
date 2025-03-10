#include "Exercise.hpp"
using namespace std;

void exercise_8_2()
{
    read(cin);
    if(!cin.fail())
        cout << "stream is effective" << endl;
}

// exercise_8_3
// 1. 当遇到文件结束标识时    2. 当读取的字符串与目标类型不匹配时,发生类型不匹配的可修复错误
// 3. 遇到了IO流错误
// while loop will end

void exercise_8_4()
{
    vector<string> svec;
    read("data\\book_sales", svec);
    for (auto &line : svec)
    {
        cout << "#" << line << endl;
    }
}

// exercise_8_6 and exercise_8_7 exercise_8_8 is prog3_fstream

void exercise_8_9()
{
    // 这个程序有些问题
    ifstream ifs("data\\sstream");
    // 之所以使用CMake找不到问题所在，就是因为文件路径不对，因此必须要有文件是否成功打开的判断，不能偷懒
    if (!ifs)
    {
        cout << "Sorry, cannot open this file." << endl;
    }
    
    string line;
    while (getline(ifs, line))
    {
        istringstream iss(line);
        read(iss);
        // while (is >> str, !is.eof()) 这行代码导致程序出现问题，例如向iss传递一行为"drew 9735550130"
        // 由于第二次读入字符串后来到了字符串末尾，所以跳出循环，没有执行循环内部代码，所以逻辑出现问题
        // 已经到了字符串流的末尾，换一个新流
        string newContents("Succeed");
        string word;
        iss.str(newContents);
        iss >> word;    // 实验说明是完完全全的更新
        if(!word.empty())
            cout << word << endl;
    }
    ifs.close();
}

void exercise_8_10()
{
    ifstream ifs("data\\sstream");
    if(!ifs)
    {
        cerr << "Sorry, cannot open this file" << endl;
        return;
    }

    vector<string> text;
    string line;
    while (getline(ifs, line))
    {
        text.push_back(line);
    }
    ifs.close();    // 不要忘记关闭文件

    unsigned order = 1;
    for (const auto &entry : text)
    {
        istringstream iss(entry);
        cout << order << ":";
        string word;
        while (iss >> word)
        {
            cout << " " << word;
        }
        cout << endl;
        ++order;
    }
}

// exercise_8_11  exercise_8_13 is prog6_sstream
// exercise_8_12 
// 根据需求，使用隐式的默认初始化是足够的，没必要显示初始化

// exercise_8_14
// enter是自定义类型PersonInfo, nums is 标准库类型string, 使用常量引用避免拷贝开销，提高效率
// 只用读操作，不需要写操作，因此使用常量引用

int main()
{
    // exercise_8_2();
    // exercise_8_4();
    // exercise_8_9();
    exercise_8_10();

    return 0;
}