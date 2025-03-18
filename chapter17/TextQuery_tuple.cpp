#include "TextQuery_tuple.hpp"
using namespace std;

TextQuery::TextQuery(ifstream &inputfile) : _ptext(new vector<string>())
{
    // 需要按行存储
    string line;
    while (getline(inputfile, line))
    {
        _ptext->push_back(line);
        istringstream iss(line);
        line_no lineNum = _ptext->size() - 1;
        string word;
        while (iss >> word)
        {
            auto &occurSet = _wordMap[cleanup_str(word)];
            if(!occurSet)
                occurSet.reset(new set<line_no>());   // shared_ptr的reset只能接受内置指针类型，不能传递shared_ptr
            occurSet->insert(lineNum);
        }
    }

    // display_map();
}

TextQuery::ResultTuple TextQuery::query(const string &word) const
{
    static shared_ptr<set<line_no>> empty(new set<line_no>());
    auto findit = _wordMap.find(word);
    if(findit != _wordMap.cend())
        return ResultTuple{word, findit->second, _ptext};
    else
        return ResultTuple{word, empty, _ptext};
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

ostream &operator<<(ostream &os, const TextQuery::ResultTuple &rhs)
{
    auto word = get<0>(rhs);
    auto occurset = get<1>(rhs);
    auto text = get<2>(rhs);

    os << word << " occurs " << occurset->size()
       << " " << make_plural(occurset->size(), "time") << endl; 
    for(auto bgit = occurset->begin(); bgit != occurset->end(); ++bgit)
    {
        if(bgit != occurset->begin())
            os << endl;
        os << "\t(line " << *bgit + 1 << ") " << (*text)[*bgit];
    }
    return os;
}