#include "Exercise.hpp"
using namespace std;

istream &read(istream &is)
{
    // int val;
    string str;
    while (is >> str, !is.eof())    // 只有发生eof error才会结束循环，这种利用comma operator作为循环变量的操作第一次使用
    {
        if(is.bad())
            throw runtime_error("IO stream occur error which is sysytem error can't being mended.");
        else if(is.fail())
        {
            // read characters have format-error, ignore these erros
            cerr << "input data have format_error, must be number, please try again." << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        cout << "(" << str << ")" << endl;
    }
    is.clear();
    return is;
}

void process_fstream(std::ifstream &ifs)
{
    string line;
    getline(ifs, line);
    cout << line << endl << endl;
}

void read(const std::string &file, std::vector<string> &svec)
{
    ifstream ifs(file);
    if(!ifs)
    {
        cerr << "Sorry, cannot open " << file << endl;
        return;
    }

    string line;
    while (getline(ifs, line))
    {
        svec.push_back(line);
    }

    // string word;
    // while (ifs >> word)
    // {
    //     svec.push_back(word);
    // }

    ifs.close();
}

void MakeAddressList(std::istream &is, std::vector<PersonInfo> &people)
{
    PersonInfo entry;   // 一条记录
    is >> entry._name;
    string num;
    while (is >> num)
    {
        entry._phones.push_back(num);
    }
    // istringstream eofbit 被置位了，因此需要复位才能继续使用同一个istringstream
    is.clear();
    people.push_back(entry);
}
