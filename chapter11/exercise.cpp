#include "exercise.hpp"

void openinfile(ifstream &ifs, const string &dir)
{
    ifs.open(dir);
    if(!ifs)
    {
        cerr << "Sorry, " << dir << " cannot being open." << endl;
        return;
    }
}

void openoutfile(ofstream &ofs, const string &dir)
{
    ofs.open(dir, ios::app | ios::out);
    if(!ofs)
    {
        cerr << "Sorry,  " << dir << " cannot being open." << endl;
        return;
    }
}

void elimSymbol_Upper(std::string &word)
{
    for(auto iter = word.begin(); iter != word.end(); )
    {
        if(ispunct(*iter))
            iter = word.erase(iter);
        else if(isupper(*iter))
        {
            *iter = tolower(*iter);
            ++iter;
        }
        else
            ++iter;
    }
}

void textConvert(istream &ruleFile, istream &textFile, ostream &os)
{
    // 根据规则文件将文本文件进行单词转换
    // TODO: Word transform regulation map
    // TODO: rely on map to convert text to integrity text
    map<string, string> wordTransRules;
    buildTransRules(ruleFile, wordTransRules);
    transText(textFile, os, wordTransRules);
}

void buildTransRules(istream &ruleFile, map<string, string> &transRules)
{
    // every line is a pair of key and value
    string oldword, newStr;
    while (ruleFile >> oldword && getline(ruleFile, newStr))
    {
        // must check has transRule
        auto pos = newStr.find_first_not_of(' ');
        if(pos > 0 && pos != string::npos)  // 永远要记住下标范围[0, str.size()) because str.size() - 1 is '\0'
            transRules[oldword] = newStr.substr(pos);    // 说明存在有效的转换规则
            // transRules.insert({oldword, newStr.substr(pos)});
        else
        {
            // 经过实验说明，若一行中只有一个空格，getline放入string中的只会是一个空格，不会添加'\0'
            cout << "error pos is " << pos << endl
                 << "newStr's size is " << newStr.size() << endl;
            throw runtime_error("Please check ruleFile to modify wrong rule for " + oldword);
        }
    }
}

void transText(istream &textFile, ostream &os, map<string, string> &transRules)
{
    // 需要一行一行的读取并进行转换
    string line;
    while (getline(textFile, line))
    {
        istringstream iss(line);
        bool firstWord = true;
        string word;
        while (iss >> word)
        {
            if(firstWord)
                firstWord = false;
            else
                os << " ";

            auto iter = transRules.find(word);
            if(iter != transRules.end())
                os << iter->second;
            else
                os << word;

            // auto res = transRules[word];
            // os << res;
        }
        os << endl;
    }   
}

void wordConvertUnordered(istream &ruleFile, istream &textFile, ostream &os)
{
    unordered_map<string, string> transRules;
    buildTransRules(ruleFile, transRules);

    string line;
    while (getline(textFile, line))
    {
        istringstream iss(line);
        string word;
        bool first = true;
        while (iss >> word)
        {
            if(first)
                first = false;
            else
                os << " ";

            os << transform(word, transRules);    
        }
        os << endl;
    }
}

void buildTransRules(istream &ruleFile, unordered_map<string, string> &transRules)
{
    string oldword, newStr;
    while (ruleFile >> oldword && getline(ruleFile, newStr))
    {
        auto pos = newStr.find_first_not_of(' ');
        if(pos > 0 && pos != string::npos)
            transRules[oldword] = newStr.substr(pos);
        else
            throw runtime_error("Go to ruleFile to modify error with " + oldword);    
    }
}

const string &transform(const string &word, const unordered_map<string, string> &transRules)
{
    auto iter = transRules.find(word);
    if(iter != transRules.end())
        return iter->second;
    else
        return word;
}
