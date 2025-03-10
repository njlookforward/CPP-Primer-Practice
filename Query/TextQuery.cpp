#include "TextQuery.hpp"
#include <cctype>
using namespace std;

// exercise_15_42, 按照句子进行存储，而是按照每一行
TextQuery::TextQuery(ifstream &inputfile) : _ptext(new vector<string>())
{
    // // 需要按行存储
    // string line;
    // while (getline(inputfile, line))
    // {
    //     _ptext->push_back(line);
    //     istringstream iss(line);
    //     line_no lineNum = _ptext->size() - 1;
    //     string word;
    //     while (iss >> word)
    //     {
    //         auto &occurSet = _wordMap[cleanup_str(word)];
    //         if(!occurSet)
    //             occurSet.reset(new set<line_no>());   // shared_ptr的reset只能接受内置指针类型，不能传递shared_ptr
    //         occurSet->insert(lineNum);
    //     }
    // }

    // 需要按句子进行存储，如果遇到集合中的空白字符，需要跳过，以结束标点符号为标志作为一个句子
    set<char> whiteSpace = {'\n', '\t', '\v', '\f', '\r'};
    set<char> EndOfSentence = {'.', '?', '!'};
    string sentence;
    char ch;

    while (inputfile.get(ch))
    {
        if(!whiteSpace.count(ch))
            sentence += ch;
        else
            sentence += " ";
        if(EndOfSentence.count(ch))
        {
            _ptext->push_back(sentence);
            istringstream iss(sentence);
            string word;
            line_no line = _ptext->size() - 1;
            while (iss >> word)
            {
                auto &wordsets = _wordMap[cleanup_str(word)];
                if(!wordsets)
                    wordsets.reset(new set<line_no>());
                wordsets->insert(line);    
            }

            sentence.assign("");    // 句子必须重新变成空串
        }    
    }
}

QueryResult TextQuery::query(const string &word) const
{
    static shared_ptr<set<line_no>> nullset(new set<line_no>());

    auto setIter = _wordMap.find(word);
    if(setIter != _wordMap.end())
        return QueryResult(word, setIter->second, _ptext);
    else
        return QueryResult(word, nullset, _ptext);
}

void TextQuery::display_map() const
{
    auto wm_bgit = _wordMap.begin(),
         wm_edit = _wordMap.end();
    
    while (wm_bgit != wm_edit)
    {
        cout << "\t" << wm_bgit->first << ": {";
        for(auto loc_it = wm_bgit->second->begin(),
                 loc_end = wm_bgit->second->end(); loc_it != loc_end;)
        {
            cout << *loc_it;
            if(++loc_it != loc_end)
                cout << ", ";
        }
        cout << "}" << endl;

        ++wm_bgit;
    }
}

string TextQuery::cleanup_str(const string &word)
{
    string ret;
    for(auto iter = word.begin(); iter != word.end(); ++iter)
    {
        // 需要过滤所有的标点，将大写字母变成小写进行统一
        if(ispunct(*iter))
            continue;
        
        ret += tolower(*iter);
    }

    return ret;
}