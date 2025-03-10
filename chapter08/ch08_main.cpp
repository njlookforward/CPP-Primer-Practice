#include "Exercise.hpp"
#include "Sales_data.hpp"
using namespace std;

void prog1_iostream()
{
    int ival;
    while (cin >> ival);
    auto old_iostate = cin.rdstate();   // 记录目前的条件状态
    if(cin.eof() && cin.fail())
    {
        cin.clear();    // 将cin所有状态复位
        // cin.setstate(old_iostate & ~cin.eofbit & ~cin.failbit); // setstate() cannot replace clear()
        cout << "cin recovery" << endl;
    }
    cin >> ival;
    cout << ival * 2 << endl;
    cin.setstate(old_iostate);  // 恢复成原来的条件状态
}

void prog2_io_buf()
{
    cout << "hi!" << endl;
        //  << "I'm nanjiang" << ends
        //  << "Nice to meet you." << flush;
    cout << "NanJiang" << flush
         << "C++" << ends
         << "World" << endl;
    cout << endl << unitbuf;    // 所有输出操作后都会立即刷新输出缓冲区
    cout << "Nice to meet you, "
         << "IO standard Library.\n";
    cout << nounitbuf;  // 回到正常的缓冲方式

    cin.tie(&cout);
    ostream *old_tie = cin.tie();
    auto old_tie_2 = cin.tie(nullptr);  // cin与其他流不再关联
    if(old_tie == old_tie_2)
        cin.tie(&cerr);
    cin.tie(old_tie);
}

void prog3_fstream(int argc, char **argv)
{
    // 派生类对象可以传递给基类指针或引用的形参
    // ifstream infile(string("data\\book_sales"));
    ifstream infile(argv[1]);
    ofstream outfile;
    // outfile.open(string("data\\book_sales")+".out", ios_base::out | ios_base::app);
    outfile.open(argv[2], ios_base::out | ios_base::app);
    if(!infile || !outfile)
    {
        cerr << "Sorry, file cannot being open normally." << endl;
        return;
    }
    Sales_data total;
    if(read(infile, total))
    {
        Sales_data trans;
        while (read(infile, trans))
        {
            if(total.isbn() == trans.isbn())
                total.combine(trans);
            else
            {
                print(outfile, total) << endl << endl;
                total = trans;
            }    
        }
        print(outfile, total) << endl << endl;
    }
    else
        cerr << "No data?" << endl;
    // 虽然函数结束后，会自动调用fstream.close(), 但还是自己显示调用比较好
    infile.close(); // 是关闭与输入文件流相关联的文件，而不是流
    infile.open("data\\add_item");
    Sales_data data1, data2;
    read(read(infile, data1), data2);
    print(outfile, Add(data1, data2)) << endl;

    infile.close();
    outfile.close();
}

void prog4_fstream(int argc, char **argv)
{
    for(auto p = argv + 1; p != argv + argc; ++p)
    {
        ifstream infile(*p);
        if(infile)
            process_fstream(infile);
        else
            cerr << "Sorry, cannot open " << *p << endl;
    }
}

void prog5_file_mode()
{
    string file("data\\book_sales.out");
    ofstream out1(file);
    out1 << "Hello C++ World!" << endl;

    ofstream out2(file, ios_base::out);
    out2 << "I'm NanJiang" << endl;

    ofstream out3(file, ios_base::out | ios_base::trunc);
    out3 << "I want to research C++ deeply" << endl;

    ofstream out4(file, ios_base::app);
    out4 << "I can persist" << endl;

    ofstream out5(file, ios_base::out | ios_base::app);
    out5 << "I will beat any difficult question" << endl;

    ofstream out;
    out.open(file);
    out << "I believe myself, " << endl;
    out.close();
    out.open(file, ios_base::app);
    out << "I can control you." << endl;
}

void prog6_sstream()
{
    string file("..\\..\\..\\data\\sstream");
    // string file("data\\sstream");
    ifstream infile(file);
    ofstream outfile(file + ".out", ios_base::app);
    if(!infile || !outfile)
    {
        cerr << "Sorry, cannot open " << "data\\sstream." << endl;
        return;
    }

    string line;
    vector<PersonInfo> people;
    istringstream iss;
    while (getline(infile, line))
    {
        // iss.str(line);
        // istringstream iss(line);
        auto psbuf = iss.rdbuf();
        psbuf->str(line);
        MakeAddressList(iss, people);
    }
    
    for (const auto &entry : people)
    {
        // 由于名字后面可能没有号码，过滤掉所有没有号码的无效数据
        // 将格式化的号码存到一起
        ostringstream formatted;
        unsigned order = 1;
        for(const auto &num : entry._phones)
        {
            string word;
            switch (order)
            {
            case 1:
                word = "#home";
                break;
            case 2:
                word = "#work";
                break;
            case 3:
                word = "#mobility";
                break;

            default:
                break;
            }
            ++order;
            formatted << " " << word << "-" << num;
        }

        if(!formatted.str().empty())
        {
            outfile << entry._name << formatted.str() << endl;
        }
    }

    infile.close();
    outfile.close();
}

int main(int argc, char *argv[])
{
    // prog1_iostream();
    // prog2_io_buf();
    // prog3_fstream(argc, argv);
    // prog4_fstream(argc, argv);
    // prog5_file_mode();
    prog6_sstream(); 

    return 0;
}